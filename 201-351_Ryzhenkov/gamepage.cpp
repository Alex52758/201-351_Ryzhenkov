#include "gamepage.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QRandomGenerator>

GamePage::GamePage(QWidget *parent) : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);

    scoreLabel = new QLabel("Очки: 0", this);

    for (int i = 0; i < 12; ++i)
    {
        QPushButton *elementButton = new QPushButton("?", this);
        elementButton->setFixedSize(100, 100);
        elementButtons.append(elementButton);

        connect(elementButton, &QPushButton::clicked, this, &GamePage::revealElement);
    }

    layout->addWidget(scoreLabel, 0, 0, 1, 2);
    for (int i = 0; i < 12; ++i)
    {
        layout->addWidget(elementButtons[i], (i + 1) / 2, i % 2);
    }

    generateRandomNumbers();
}

void GamePage::revealElement()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton)
    {
        int index = elementButtons.indexOf(clickedButton);
        int number = randomNumbers[index];
        clickedButton->setText(QString::number(number));
        updateScore(number);
        clickedButton->setEnabled(false);
    }
}

void GamePage::generateRandomNumbers()
{
    QRandomGenerator generator;
    randomNumbers.clear();

    for (int i = 0; i < 12; ++i)
    {
        int randomNumber = generator.bounded(10000);
        randomNumbers.append(randomNumber);
    }
}

void GamePage::updateScore(int points)
{
    static int totalScore = 0;
    totalScore += points;
    scoreLabel->setText("Очки: " + QString::number(totalScore));
}
