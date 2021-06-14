#include "deck.h"
#include <cstdlib>
#include <QDebug>
#include <ctime>

Deck::Deck()
{
    for (int i = 0; i < 52; i++){
        deck[i] = i;
    }
}

void Deck::shuffle(){
    int temp = 0;
    int randomIndex = 0;
    srand(time(NULL));
    for (int i = 0; i < 54; i++){
        randomIndex = rand() % 54;
        temp = deck[i];
        deck[i] = deck[randomIndex];
        deck[randomIndex] = temp;
    }
    lastTakenCardId = 0;
}

int Deck::getCard(){
    return deck[lastTakenCardId++];
}

void Deck::listCards(){
    for(int i = 0; i < 54; i++){
        qDebug()<<deck[i];
    }
}
