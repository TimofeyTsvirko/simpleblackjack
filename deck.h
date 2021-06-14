#ifndef DECK_H
#define DECK_H


class Deck
{
public:
    Deck();
    void shuffle();
    int getCard();
    void listCards();
private:
    int lastTakenCardId = 0;
    int deck[54];
};

#endif // DECK_H
