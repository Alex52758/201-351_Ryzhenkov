#include "loginpage.h"
#include <QGridLayout>
#include <QMessageBox>

LoginPage::LoginPage(QWidget* parent) : QWidget(parent) {
    QGridLayout* layout = new QGridLayout(this);

    QLabel* pinLabel = new QLabel("Пин-код:", this);
    pinInput = new QLineEdit(this);
    pinInput->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Вход", this);

    layout->addWidget(pinLabel, 0, 0);
    layout->addWidget(pinInput, 0, 1);
    layout->addWidget(loginButton, 1, 0, 1, 2);

    connect(loginButton, &QPushButton::clicked, this, &LoginPage::login);
}

void LoginPage::login() {
    QString pinCode = "1234"; // Задайте верный пин-код здесь

    if (pinInput->text() == pinCode) {
        emit loginSuccess();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверный пин-код!");
    }
}
