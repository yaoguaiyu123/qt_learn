#include "iplineedit.h"
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QLabel>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QEvent>
#include <QKeyEvent>

IPLineEdit::IPLineEdit(QWidget* widget)
    : QLineEdit(widget)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(1, 1, 1, 1);
    QRegularExpression rxp("(25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})"); // 正则表达式
    QLabel* labelDot[3];
    for (int i = 0; i < IP_INPUT_SIZE; ++i) {
        m_lineEdits[i] = new QLineEdit(this);
        m_lineEdits[i]->setFrame(false); // 去除边框线条
        m_lineEdits[i]->setMaxLength(3); // 设置输入框的最大长度为3
        m_lineEdits[i]->setAlignment(Qt::AlignCenter); // 居中
        m_lineEdits[i]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); // 保存小部件的默认布局
        m_lineEdits[i]->setValidator(new QRegularExpressionValidator(rxp, this));    //对控件设置设置验证规则
        m_lineEdits[i]->installEventFilter(this);   //安装事件过滤器,这里的this为过滤器对象，由过滤器对象的eventFilter函数处理事件
        layout->addWidget(m_lineEdits[i]);
        if (i < 3) {
            labelDot[i] = new QLabel(this);
            labelDot[i]->setText(".");
            QFont font;
            font.setPointSize(18);
            labelDot[i]->setFont(font);
            labelDot[i]->setFixedWidth(4);
            layout->addWidget(labelDot[i]);
        }
        this->setReadOnly(true);    //todo
    }
    m_lineEdits[0]->setFocus();
}

//当安装了事件过滤器之后，到达QLineEdit的事件会先到达eventFilter函数
bool IPLineEdit::eventFilter(QObject* watched, QEvent* event)
{
    //这里的watched是指事件发生的对象,event是发生的事件信息
    //首先判断是不是发生在IPLineEdit的事件，判断是不是键盘事件
    if (children().contains(watched) && QEvent::KeyPress == event->type()) {
        QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);
        QLineEdit* pCurrentEdit = qobject_cast<QLineEdit*>(watched);

        switch (keyEvent->key()) {
        case Qt::Key_0:
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9: {
            QString str = pCurrentEdit->text();
            if (str.length() <= 3 && str.toInt() * 10 > 255) {
                int index = getIndex(pCurrentEdit);
                if(index != -1 && index != 3){
                    m_lineEdits[index+1]->setFocus();
                    m_lineEdits[index+1]->selectAll();    //选中该QLineEdit中的所有文本
                }
            }
            return QLineEdit::eventFilter(watched, event);
        }
            break;
        case Qt::Key_Left: {
            // cursorPosition函数返回QLineEdit中的光标位置,从0开始计数，没有光标则返回-1
            if (!pCurrentEdit->cursorPosition()) { // 如果光标已经位于当前QLineEdit中的最左边
                int index = getIndex(pCurrentEdit);
                if (index != -1 && index != 0) {
                    m_lineEdits[index - 1]->setFocus();
                    int length = m_lineEdits[index - 1]->text().length();
                    m_lineEdits[index - 1]->setCursorPosition(length); // 往左移动到左边的QLineEdit的末尾
                }
            }
            return QLineEdit::eventFilter(watched, event);
        } break;
        case Qt::Key_Right: {
            if (pCurrentEdit->cursorPosition() == pCurrentEdit->text().length()) { // 如果光标已经位于当前QLineEdit中的最右边
                int index = getIndex(pCurrentEdit);
                if (index != -1 && index != 3) {
                    m_lineEdits[index + 1]->setFocus();
                    m_lineEdits[index + 1]->setCursorPosition(0); // 往右移动到左边的QLineEdit的开头
                }
            }
        } break;
        case Qt::Key_Backspace: {
            // 后退键
            QString str = pCurrentEdit->text();
            if (str.isEmpty()) {
                int index = getIndex(pCurrentEdit);
                if (index != -1 && index != 0) {
                    m_lineEdits[index - 1]->setFocus();
                    int length = m_lineEdits[index - 1]->text().length();
                    m_lineEdits[index - 1]->setCursorPosition(length); // 往左移动到左边的QLineEdit的末尾                }
                }
            }
        } break;
        case Qt::Key_Period: {
            // 点键
            int index = getIndex(pCurrentEdit);
            if (index != -1 && index != 3) {
                m_lineEdits[index + 1]->setFocus();
                m_lineEdits[index + 1]->setCursorPosition(0); // 往右移动到左边的QLineEdit的开头           }
            }
        }
        break;
        default:
            break;
        }
    }
    return QLineEdit::eventFilter(watched, event);
}

int IPLineEdit::getIndex(QLineEdit* pLineEdit){
    //实现该函数
    int index = -1;
    for (int i = 0; i < IP_INPUT_SIZE; ++i) {
        if (pLineEdit == m_lineEdits[i]) {
            index = i;
        }
    }
    return index;
}

QString IPLineEdit::text()
{
    // 获取IP地址
    QString ip;
    for (int i = 0; i < IP_INPUT_SIZE; ++i) {
        ip.append(m_lineEdits[i]->text());
        if (i != 3) {
            ip.append(".");
        }
    }
    return ip;
}


IPLineEdit::~IPLineEdit()
{
    ;
}
