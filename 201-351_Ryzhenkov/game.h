#ifndef GAME_H
#define GAME_H
#include <QDialog>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <windows.h>
#include <QCryptographicHash>

//using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class game; }
QT_END_NAMESPACE


class game : public QDialog
{
    Q_OBJECT

public:
    game(QWidget *parent = nullptr);
    ~game();
    void createUI(const QStringList &headers);
    std::string check_pincode(QString user_code);
    QString mass_dec[12]; //массив, в котором хранятся рандомные числа от 0 до 9999
    int summary; //сумма, выводимая на экран
    int k; //счетчик, позволяющий складывать числа ровно 4 раза

private:
    Ui::game *ui;
    QLineEdit *lineEdit_number;
    void numbers();
    bool eventFilter(QObject* watched, QEvent* event);


signals:
    void ShowMW();//функция для возврата на окно MW

private slots:

};

#endif // GAME_H

