#ifndef LINEMESSAGE_H
#define LINEMESSAGE_H
#include <QWidget>

// 消息类型
//定义了一个名为MessageUser的枚举类型，它有两个成员
typedef enum {
    MessageUser_Self,
    Message_Counterpart,
} MessageUser;

typedef struct LineMessageData {
    QString message;
    QString headImg;
    int lineCount;
}LineMessageData;

class LineMessage : public QWidget
{
    Q_OBJECT
public:
    explicit LineMessage(const LineMessageData& messageData, MessageUser msgUser = MessageUser_Self, QWidget* parent = nullptr);

private:
    int m_selfHeight;
signals:

};

#endif // LINEMESSAGE_H
