

#include "widget.h"
#include <QAudioDevice>
#include <QAudioSink>
#include <QDebug>
#include <QVBoxLayout>
#include <QtEndian>
#include <QtMath>

Generator::Generator(const QAudioFormat& format, qint64 durationUs, int sampleRate)
{
    if (format.isValid()) {
        generateData(format, durationUs, sampleRate);
    }
}

void Generator::start()
{
    open(QIODevice::ReadOnly);
}

void Generator::stop()
{
    m_pos = 0;
    close();
}

// 生成一个音频
void Generator::generateData(const QAudioFormat& format, qint64 durationUs, int sampleRate)
{
    const int channelBytes = format.bytesPerSample(); // 返回每个通道的字节数
    const int sampleBytes = format.channelCount() * channelBytes; // 计算每个样本的字节总数
    qint64 length = format.bytesForDuration(durationUs); // 返回音频字节数,参数是音频的持续时间
    Q_ASSERT(length % sampleBytes == 0);
    Q_UNUSED(sampleBytes);

    m_buffer.resize(length);
    unsigned char* ptr = reinterpret_cast<unsigned char*>(m_buffer.data());
    int sampleIndex = 0;

    while (length) {
        // 生成一个音频波形，使用sin函数
        const qreal x = qSin(2 * M_PI * sampleRate * qreal(sampleIndex++ % format.sampleRate())
            / format.sampleRate());
        for (int i = 0; i < format.channelCount(); ++i) {
            // 将数据写入到缓冲区
            switch (format.sampleFormat()) {
            case QAudioFormat::UInt8:
                *reinterpret_cast<quint8*>(ptr) = static_cast<quint8>((1.0 + x) / 2 * 255);
                break;
            case QAudioFormat::Int16:
                *reinterpret_cast<qint16*>(ptr) = static_cast<qint16>(x * 32767);
                break;
            case QAudioFormat::Int32:
                *reinterpret_cast<qint32*>(ptr) = static_cast<qint32>(x * std::numeric_limits<qint32>::max());
                break;
            case QAudioFormat::Float:
                *reinterpret_cast<float*>(ptr) = x;
                break;
            default:
                break;
            }

            ptr += channelBytes;
            length -= channelBytes;
        }
    }
}

// 读取音频数据
qint64 Generator::readData(char* data, qint64 len)
{
    qint64 total = 0; // 记录本次已经读取的数据长度
    if (!m_buffer.isEmpty()) {
        while (len - total > 0) {
            const qint64 chunk = qMin((m_buffer.size() - m_pos), len - total);
            memcpy(data + total, m_buffer.constData() + m_pos, chunk);
            m_pos = (m_pos + chunk) % m_buffer.size();
            total += chunk;
        }
    }
    return total;
}

qint64 Generator::writeData(const char* data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

qint64 Generator::bytesAvailable() const
{
    return m_buffer.size() + QIODevice::bytesAvailable();
}



Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , m_devices(new QMediaDevices(this))
    , m_pushTimer(new QTimer(this))
{
    initializeWindow();
    initializeAudio(m_devices->defaultAudioOutput());
    resize(560, 200);
}

Widget::~Widget()
{
    m_pushTimer->stop();
}

void Widget::initializeWindow()
{
    QWidget* window = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout;

    m_deviceBox = new QComboBox(this);
    const QAudioDevice& defaultDeviceInfo = m_devices->defaultAudioOutput(); // 默认声音输出设备
    m_deviceBox->addItem(defaultDeviceInfo.description(), QVariant::fromValue(defaultDeviceInfo));
    //将所有声音输出设备加入到deviceBox中
    for (auto& deviceInfo : m_devices->audioOutputs()) {
        if (deviceInfo != defaultDeviceInfo) {
            m_deviceBox->addItem(deviceInfo.description(), QVariant::fromValue(deviceInfo));
        }
    }
    connect(m_deviceBox, QOverload<int>::of(&QComboBox::activated), this,
        &Widget::deviceChanged);
    connect(m_devices, &QMediaDevices::audioOutputsChanged, this, &Widget::updateAudioDevices);
    layout->addWidget(m_deviceBox);

    m_modeButton = new QPushButton(this);
    connect(m_modeButton, &QPushButton::clicked, this, &Widget::toggleMode);
    layout->addWidget(m_modeButton);

    m_suspendResumeButton = new QPushButton(this);
    connect(m_suspendResumeButton, &QPushButton::clicked, this, &Widget::toggleSuspendResume);
    layout->addWidget(m_suspendResumeButton);

    QHBoxLayout *volumeBox = new QHBoxLayout;
    m_volumeLabel = new QLabel;
    m_volumeLabel->setText(tr("Volume:"));
    m_volumeSlider = new QSlider(Qt::Horizontal);
    m_volumeSlider->setMinimum(0);
    m_volumeSlider->setMaximum(100);
    m_volumeSlider->setSingleStep(10);
    connect(m_volumeSlider, &QSlider::valueChanged, this, &Widget::volumeChanged);    //改变音量
    volumeBox->addWidget(m_volumeLabel);
    volumeBox->addWidget(m_volumeSlider);
    layout->addLayout(volumeBox);

    window->setLayout(layout);
    window->setContentsMargins(30,30,30,30);

}

void Widget::initializeAudio(const QAudioDevice &deviceInfo)
{
    //初始化音频，并开始播放
    QAudioFormat format = deviceInfo.preferredFormat();

    const int durationSeconds = 1;
    const int toneSampleRateHz = 600;
    //初始化音频
    m_generator.reset(new Generator(format, durationSeconds * 1000000, toneSampleRateHz));

    m_audioOutput.reset(new QAudioSink(deviceInfo, format));
    m_generator->start();    //打开音频设备相当于

    qreal initialVolume = QAudio::convertVolume(m_audioOutput->volume(), QAudio::LinearVolumeScale,
        QAudio::LogarithmicVolumeScale);
    m_volumeSlider->setValue(qRound(initialVolume * 100));
    toggleMode();    // 在这个函数中将会调用m_audioOutput的start方法正式播放音频
}

void Widget::deviceChanged(int index)
{
    m_generator->stop();
    m_audioOutput->stop();
    m_audioOutput->disconnect(this);
    initializeAudio(m_deviceBox->itemData(index).value<QAudioDevice>());
}

void Widget::volumeChanged(int value)
{
    qreal linearVolume = QAudio::convertVolume(value / qreal(100), QAudio::LogarithmicVolumeScale,
        QAudio::LinearVolumeScale);

    m_audioOutput->setVolume(linearVolume);
}

void Widget::updateAudioDevices()
{
    m_deviceBox->clear();
    const QList<QAudioDevice> devices = m_devices->audioOutputs();
    for (const QAudioDevice &deviceInfo : devices)
        m_deviceBox->addItem(deviceInfo.description(), QVariant::fromValue(deviceInfo));
}

void Widget::toggleMode()
{
    m_pushTimer->stop();
    m_audioOutput->stop();
    toggleSuspendResume();

    if (m_pullMode) {
        // switch to pull mode (QAudioSink pulls from Generator as needed)
        m_modeButton->setText(tr("Enable push mode"));
        m_audioOutput->start(m_generator.data());
    } else {
        // switch to push mode (periodically push to QAudioSink using a timer)
        m_modeButton->setText(tr("Enable pull mode"));
        auto io = m_audioOutput->start();
        m_pushTimer->disconnect();

        connect(m_pushTimer, &QTimer::timeout, [this, io]() {
            if (m_audioOutput->state() == QAudio::StoppedState)
                return;

            int len = m_audioOutput->bytesFree();
            QByteArray buffer(len, 0);
            len = m_generator->read(buffer.data(), len);
            if (len)
                io->write(buffer.data(), len);
        });

        m_pushTimer->start(10);
    }

    m_pullMode = !m_pullMode;
}

void Widget::toggleSuspendResume()
{
    if (m_audioOutput->state() == QAudio::SuspendedState
        || m_audioOutput->state() == QAudio::StoppedState) {
        m_audioOutput->resume();
        m_suspendResumeButton->setText(tr("Suspend playback"));
    } else if (m_audioOutput->state() == QAudio::ActiveState) {
        m_audioOutput->suspend();
        m_suspendResumeButton->setText(tr("Resume playback"));
    } else if (m_audioOutput->state() == QAudio::IdleState) {
        // no-op
    }
}

