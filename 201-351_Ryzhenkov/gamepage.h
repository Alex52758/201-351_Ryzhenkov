#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVector>

class GamePage : public QWidget
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);

private slots:
    void revealElement();

private:
    QLabel *scoreLabel;
    QVector<QPushButton*> elementButtons;
    QVector<int> randomNumbers;

    void generateRandomNumbers();
    void updateScore(int points);
};

#endif // GAMEPAGE_H
