#include "game.h"
#include "ui_game.h"
#include <QDialog>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QItemDelegate>
#include <iostream>
#include <QEvent>
#include <vector>
#include <algorithm>
#include <iterator>
#include <QClipboard>
#include <QString>
#include <ctime>
#include <QMessageBox>


game::game(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::game)
{
    ui->setupUi(this);
}


std::string game::check_pincode(QString user_code){
    QString code = user_code;
    QByteArray hash = QCryptographicHash::hash(code.toUtf8(), QCryptographicHash::Sha256);
    hash = hash.toBase64();
    QString q_hash = QString(hash);
    std::string str_hash = q_hash.toStdString().substr(1,32);
    return str_hash;
}


void game::createUI(const QStringList &headers){
    ui->game_manager->setColumnCount(1); // Указываем число колонок
    //ui->game_manager->setRowCount(12);
    ui->game_manager->setShowGrid(true); // Включаем сетку
    // Разрешаем выделение только одного элемента
    ui->game_manager->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->game_manager->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем заголовки колонок
    ui->game_manager->setHorizontalHeaderLabels(headers);
    // Растягиваем последнюю колонку на всё доступное пространство
    ui->game_manager->horizontalHeader()->setStretchLastSection(true);
    // Скрываем колонку под номером 0
    //ui->game_manager->hideColumn(0);
    ui->game_manager->setEditTriggers(QAbstractItemView::NoEditTriggers);
    numbers();
}


//функция события qlineedit
bool game::eventFilter(QObject* watched, QEvent* event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
            if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(watched))
            {
                Q_FOREACH(const QLineEdit* i, findChildren<QLineEdit*>())
                i->disconnect();

                int row = lineEdit->property("row").toInt();
                if (k != 4) {
                    for (int i = 0; i < 12; i++)
                    {
                        if (i != row){
                            lineEdit_number = new QLineEdit(mass_dec[i]);
                            lineEdit_number->setEchoMode(QLineEdit::Password);
                            lineEdit_number->setProperty("row", i);
                            lineEdit_number->setProperty("column", 0);
                            lineEdit_number->setReadOnly(true);
                            lineEdit_number->installEventFilter(this);

                            ui->game_manager->setCellWidget(i, 0, lineEdit_number);
                            ui->game_manager->setStyleSheet("QLineEdit { border: none }");
                        }
                        else {
                            lineEdit_number = new QLineEdit(mass_dec[i]);
                            lineEdit_number->setEchoMode(QLineEdit::Normal);
                            lineEdit_number->setReadOnly(true);

                            ui->game_manager->setCellWidget(i, 0, lineEdit_number);
                            ui->game_manager->setStyleSheet("QLineEdit { border: none }");

                            k += 1;
                            summary += mass_dec[i].toInt();
                            ui->summ->setText(QString::number(summary));

                            if (k == 4) {
                                QMessageBox msgBox;
                                msgBox.setWindowTitle("Игра закончена");
                                QString text = QString::number(summary);
                                msgBox.setText(text);
                                msgBox.exec();
                                numbers(); //происходит сброс игры
                                ui->summ->setText("");
                            }
                        }
                    }
                }
         }
    }
    return QObject::eventFilter(watched, event);
}



void game::numbers() {
    ui->game_manager->setRowCount(0); //сброс

    srand((int)time(0));

    for (int i = 0; i < 12; i++)
    {
        mass_dec[i] = QString::number((rand() % 9999));
    }

    k = 0; //на этом этапе счетчик обнулен
    summary = 0; //на этом этапе сумма равна 0

    for (int i = 0; i < 12; i++)
    {
                ui->game_manager->insertRow(i);

                lineEdit_number = new QLineEdit(mass_dec[i]);
                lineEdit_number->setEchoMode(QLineEdit::Password);
                lineEdit_number->setProperty("row", i);
                lineEdit_number->setProperty("column", 0);
                lineEdit_number->setReadOnly(true);
                lineEdit_number->installEventFilter(this);

                ui->game_manager->setCellWidget(i, 0, lineEdit_number);
                ui->game_manager->setStyleSheet("QLineEdit { border: none }");
    }
}


game::~game()
{
    delete ui;
}





