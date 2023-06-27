#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class LoginPage : public QWidget {
    Q_OBJECT
public:
    explicit LoginPage(QWidget* parent = nullptr);

signals:
    void loginSuccess();

private slots:
    void login();

private:
    QLineEdit* pinInput;
    QPushButton* loginButton;
};

#endif // LOGINPAGE_H
