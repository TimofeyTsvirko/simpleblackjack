#ifndef PLAYER_H
#define PLAYER_H
#include <QString>


class Player
{
public:
    Player();
    void addCard(int card);
    int isBusted();
    int * getSum();
    int getBalance();
    void showCards();
    void clearHand();
    void blackjack();
    void win();
    void draw();
    void makeBet(int bet);
    int getPossibleMax();
    QString showSum();
    int isFullHand();
private:
    int balance;
    int sum[2];
    int lastId;
    int hand[5];
    int bet;
};

#endif // PLAYER_H
