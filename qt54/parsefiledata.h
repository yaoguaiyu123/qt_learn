#ifndef PARSEFILEDATA_H
#define PARSEFILEDATA_H

//该类对象作为一个线程用于解析包并对文件做IO

#include <QThread>
class FileClientHandler;
class ParseFileData : public QThread {
    Q_OBJECT
public:
    explicit ParseFileData(QObject* parent = nullptr);

protected:
    void run() override;

private:
    FileClientHandler* _clientHandler;
};

#endif // PARSEFILEDATA_H
