#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    QPixmap deck_image;

    void onAddWidget();

    void onRemoveWidget();

private slots:


    void on_addCardButton_clicked();

    void on_startGameButton_clicked();

    void on_stopRoundButton_clicked();

    void on_quitButton_clicked();

    void on_startAnotherRoundButton_clicked();

    void dealerTurn();

    void blackjack();

    void draw();

    void win();

    void lose();

    void round();

    void on_makeBetButton_clicked();

    void displayCard(int card);

    void clearLayouts();

//    void clearLayout(QLayout* layout, bool deleteWidgets = true);

private:
    Ui::MainWindow *ui;
};

void delay();

#endif // MAINWINDOW_H
