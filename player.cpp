#include "player.h"
#include <QDebug>

Player::Player()
{
    lastId = 0;
    sum[0] = 0;
    sum[1] = 0;
    balance = 1000;
    bet = 0;
}

void Player::addCard(int card){
    hand[lastId] = card;
    lastId++;

    if (card % 13 == 0){
        sum[0] += 1;
        sum[1] += 11;
//        qDebug()<<"Ace";
    } else if(card % 13 < 9){
        sum[0] += card % 13 + 1;
        sum[1] += card % 13 + 1;
//        qDebug()<<"number";
    } else {
        sum[0] += 10;
        sum[1] += 10;
//        qDebug()<<"pic";
    }
}

int Player::isBusted(){
    if ((sum[0] > 21) & (sum[1] > 21)) {
        return 1;
    } else {
        return 0;
    }
}

int * Player::getSum(){
    return sum;
}

int Player::getBalance(){
    return balance;
}

void Player::showCards(){
    qDebug()<<"----Player balance:----";
    qDebug()<<getBalance();
    qDebug()<<"----Total Player points:----";
    qDebug()<<showSum();
    qDebug()<<"----Player cards:----";
    for(int i = 0; i < lastId; i++){
        qDebug()<<hand[i];
    }
    qDebug()<<"---------------------";
}

void Player::clearHand(){
    sum[0] = 0;
    sum[1] = 0;
    lastId = 0;
}

void Player::blackjack(){
    balance += bet * 1.5;
}

void Player::win(){
    balance += bet * 2;
}

void Player::draw(){
    balance += bet;
}

void Player::makeBet(int newBet){
    bet = newBet;
    balance -= bet;
}

int Player::getPossibleMax(){
    if (sum[1] < 22){
        return sum[1];
    } else {
        return sum[0];
    }
}

QString Player::showSum(){

    if (sum[0] != sum[1]){
        return QString("%1 or %2").arg(sum[0]).arg(sum[1]);
    } else {
        return QString::number(sum[0]);
    }
}

int Player::isFullHand(){
    if (lastId == 5){
        return 1;
    } else {
        return 0;
    }
}
