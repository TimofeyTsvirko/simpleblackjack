#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include "deck.h"
#include <QIntValidator>
#include <QHBoxLayout>
#include <QRect>
#include <QPixmap>
#include <QLabel>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->addCardButton->setVisible(false);
    ui->stopRoundButton->setVisible(false);
    ui->startAnotherRoundButton->setVisible(false);
    ui->betLineEdit->setVisible(false);
    ui->makeBetButton->setVisible(false);
    ui->betLabel->setVisible(false);
    ui->curretBetLabel->setVisible(false);
    ui->currentBalanceLabel->setVisible(false);
    ui->balanceLabel->setVisible(false);
    ui->hiddenCardLabel->setVisible(false);
    ui->dealerPointsLabel->setVisible(false);

    deck_image = QPixmap("/home/timofey/QTprojects/SimpleBlackjack/deck.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}

Player player;
Player dealer;
Deck deck;
int player_move = 0;
int w = 92;
int h = 136;

void MainWindow::on_addCardButton_clicked()
{
    int card;

    player.addCard(card = deck.getCard());
    displayCard(card);

    ui->playerPointsLabel->setText(tr("Player points: %1").arg(player.showSum()));

    player.showCards();
    if (player.isBusted()){
        qDebug()<<"Busted";
        ui->addCardButton->setVisible(false);
        ui->stopRoundButton->setVisible(false);
        ui->hiddenCardLabel->setVisible(false);

        ui->dealerPointsLabel->setText(tr("Dealer points: %1").arg(dealer.showSum()));
        ui->dealerPointsLabel->setVisible(true);

        ui->messageLabel->setText(tr("Busted!"));

        player_move = 0;
        lose();
        return;
    }
    if (player.isFullHand()){
        qDebug()<<"Won by full hand!";

        ui->messageLabel->setText(tr("Won by full 5 card hand!"));

        ui->addCardButton->setVisible(false);
        ui->stopRoundButton->setVisible(false);
        ui->hiddenCardLabel->setVisible(false);
        win();
    }
}


void MainWindow::displayCard(int card)
{

    QLayout* lay;
    if (player_move){
        lay = ui->playerCardsFrame->layout();
    } else {
        lay = ui->dealerCardsFrame->layout();
    }
    QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(lay);

    int num = card % 13;
    int suit = card / 13;

    QRect rec(num*w, suit*h, w, h);

    QPixmap card_image = deck_image.copy(rec);

    QFrame* frame;
    if (player_move){
        frame = ui->playerCardsFrame;
    } else {
        frame = ui->dealerCardsFrame;
    }
    QLabel* cardLabel = new QLabel(frame);

    layout->insertWidget(0,cardLabel);

    cardLabel->setPixmap(card_image);


}

void MainWindow::on_startGameButton_clicked()
{
    ui->startGameButton->setVisible(false);
    ui->currentBalanceLabel->setText(QString::number(player.getBalance()));
    ui->currentBalanceLabel->setVisible(true);
    ui->balanceLabel->setVisible(true);
    ui->betLineEdit->setValidator(new QIntValidator(1,player.getBalance(), this));
    ui->betLineEdit->setVisible(true);
    ui->makeBetButton->setVisible(true);
}

void MainWindow::round()
{
    ui->currentBalanceLabel->setText(QString::number(player.getBalance()));

    ui->addCardButton->setVisible(true);
    ui->stopRoundButton->setVisible(true);

    deck.shuffle();

    int card;
    player_move = 0;

    ui->hiddenCardLabel->setVisible(true);
    dealer.addCard(card = deck.getCard());
    displayCard(card);
    dealer.addCard(card = deck.getCard());
    displayCard(card);

    player_move = 1;

    player.addCard(card = deck.getCard());
    displayCard(card);
    player.addCard(card = deck.getCard());
    displayCard(card);

    ui->playerPointsLabel->setText(tr("Player points: %1").arg(player.showSum()));

    player.showCards();

    if ((player.getSum()[1] == 21) & (dealer.getSum()[1] == 21)){

        ui->addCardButton->setVisible(false);
        ui->stopRoundButton->setVisible(false);
        ui->hiddenCardLabel->setVisible(false);
        ui->messageLabel->setText(tr("BLACKJACK draw!"));
        draw();
        qDebug()<<"Blackjack draw!";
    }

    if ((player.getSum()[1] == 21) & (dealer.getSum()[1] != 21)){

        ui->addCardButton->setVisible(false);
        ui->stopRoundButton->setVisible(false);
        ui->hiddenCardLabel->setVisible(false);
        ui->messageLabel->setText(tr("BLACKJACK!"));
        blackjack();
        qDebug()<<"Blackjack win!";
    }

    if ((player.getSum()[1] != 21) & (dealer.getSum()[1] == 21)){

        ui->addCardButton->setVisible(false);
        ui->stopRoundButton->setVisible(false);

        ui->hiddenCardLabel->setVisible(false);
        ui->messageLabel->setText(tr("BLACKJACK lose!"));

        lose();
        qDebug()<<"Blackjack lose!";
    }

}

void MainWindow::on_stopRoundButton_clicked()
{
    ui->addCardButton->setVisible(false);
    ui->stopRoundButton->setVisible(false);
    dealerTurn();
}


void MainWindow::on_quitButton_clicked()
{
    MainWindow::close();
}

void MainWindow::dealerTurn()
{
    qDebug()<<"===========Dealer's turn============";
    //reveal second card
    delay();
    ui->hiddenCardLabel->setVisible(false);
    ui->dealerPointsLabel->setText(tr("Dealer points: %1").arg(dealer.showSum()));
    ui->dealerPointsLabel->setVisible(true);

    int playerMax = player.getPossibleMax();

    if (dealer.getPossibleMax() > playerMax){
        ui->messageLabel->setText("Lose!");
        lose();
        return;
    }

    player_move = 0;
    int card;

    while (dealer.getPossibleMax() < 17){
        //take a while...
        delay();

        dealer.addCard(card = deck.getCard());
        dealer.showCards();

        ui->dealerPointsLabel->setText(tr("Dealer points: %1").arg(dealer.showSum()));

        // display taken cards
        displayCard(card);
    }

    if (dealer.isBusted()){
        ui->messageLabel->setText("Win!");
        win();
        return;
    }

    int dealerMax = dealer.getPossibleMax();

    if (dealerMax > playerMax){
        ui->messageLabel->setText(tr("Lose!"));
        lose();
        return;
    }

    if (dealerMax < playerMax){
        ui->messageLabel->setText(tr("Win!"));
        win();
        return;
    }

    if (dealerMax == playerMax){
        ui->messageLabel->setText(tr("Draw!"));
        draw();
    }
}

void MainWindow::draw()
{
    qDebug()<<"Draw!";
    player.draw();
    ui->startAnotherRoundButton->setVisible(true);
}

void MainWindow::blackjack()
{
    player.blackjack();
    ui->startAnotherRoundButton->setVisible(true);
}

void MainWindow::lose()
{
    qDebug()<<"Player lose!";
    ui->startAnotherRoundButton->setVisible(true);
}

void MainWindow::win()
{
    qDebug()<<"Player win!";
    player.win();
    ui->startAnotherRoundButton->setVisible(true);
}

void MainWindow::on_startAnotherRoundButton_clicked()
{
    qDebug()<<"Starting another round...";
    player.clearHand();
    dealer.clearHand();

    clearLayouts();

    ui->startAnotherRoundButton->setVisible(false);
    ui->dealerPointsLabel->setVisible(false);
    ui->playerPointsLabel->setVisible(false);

    ui->messageLabel->setText(tr(""));

    if(player.getBalance()==0){
        ui->messageLabel->setText(tr("You are broke! Cannot continue the game!"));
        return;
    }

    MainWindow::on_startGameButton_clicked();
}



void MainWindow::on_makeBetButton_clicked()
{
    int bet = ui->betLineEdit->text().toInt();
    if ((bet < player.getBalance()+1) & (bet > 0)){
        ui->makeBetButton->setVisible(false);
        ui->betLineEdit->setVisible(false);
        // make label with bet
        ui->betLabel->setVisible(true);
        ui->curretBetLabel->setText(QString::number(bet));
        ui->curretBetLabel->setVisible(true);

        ui->playerPointsLabel->setVisible(true);

        player.makeBet(bet);
        round();
    }

}

//void MainWindow::clearLayout(QLayout* layout, bool deleteWidgets)
//{
//    while (QLayoutItem* item = layout->takeAt(0))
//    {
//        if (deleteWidgets)
//        {
//            if (QWidget* widget = item->widget())
//                widget->deleteLater();
//        }
//        if (QLayout* childLayout = item->layout())
//            clearLayout(childLayout, deleteWidgets);
//        delete item;
//    }
//}

void MainWindow::clearLayouts(){
    QLayout* dealerLayout = ui->dealerCardsFrame->layout();
    QLayout* playerLayout = ui->playerCardsFrame->layout();

    QLayoutItem* item;

    while ((item = dealerLayout->takeAt(0)) != NULL){
            delete item->widget();
            delete item;
    }
//    delete dealerLayout;

    while ((item = playerLayout->takeAt(0)) != NULL){
            delete item->widget();
            delete item;
    }
//    delete playerLayout;
}

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
