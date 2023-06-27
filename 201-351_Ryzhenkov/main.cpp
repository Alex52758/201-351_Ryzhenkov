#include <QApplication>
#include "loginpage.h"
#include "gamepage.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    LoginPage loginPage;
    GamePage gamePage;

    // Логика перехода со страницы авторизации на страницу игры
    QObject::connect(&loginPage, &LoginPage::loginSuccess, [&]() {
        loginPage.hide();
        gamePage.show();
    });

    loginPage.show();
    return app.exec();
}

