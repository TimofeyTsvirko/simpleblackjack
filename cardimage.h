#ifndef CARDIMAGE_H
#define CARDIMAGE_H

#include <QWidget>
#include <QPixmap>

class CardImage : public QWidget
{
    Q_OBJECT
public:
    explicit CardImage(QWidget *parent = nullptr);

private:
    QString _noImageMessage;
    QPixmap _card;
    int _number;
    int _suit;

signals:

};

#endif // CARDIMAGE_H
