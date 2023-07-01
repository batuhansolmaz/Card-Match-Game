#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>
#include <QDebug>
#include <random>
#include <QThread>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}
QString fruit[30]  = {
    "Apple", "Banana", "Orange", "Grapes", "Strawberry", "Mango",
    "Watermelon", "Pineapple", "Cherry", "Kiwi", "Pear", "Peach",
    "Plum", "Blueberry", "Raspberry" , "Apple", "Banana", "Orange", "Grapes", "Strawberry", "Mango",
    "Watermelon", "Pineapple", "Cherry", "Kiwi", "Pear", "Peach",
    "Plum", "Blueberry", "Raspberry"};
int Score;
double Tries=50;

void MainWindow::handleButtonClicked()
{
    bool flag = false;
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QTextEdit* ScoreText = ui->textEdit_2;
    QTextEdit* TriesText = ui->textEdit_4;
    // if button is checked show text of the button from fruits otherwise show nothing
    if (button->isChecked()) {

        button->setText(fruit[button->property("id").toInt()]);
        qDebug() << "Clicked button with item number:" << button->property("id").toInt();
        button->setDisabled(true);

    }


    if (button->isChecked() == false) {
        button->setText("");
    }

    // check if anny button is checked and if so check if the text of the buttons are the same and if so disable the buttons
    QGridLayout* gridLayout = ui->gridLayout;
    int count = 0;
    for (int i = 0; i < gridLayout->count(); ++i) {
        QPushButton* button = qobject_cast<QPushButton*>(gridLayout->itemAt(i)->widget());
        if (button) {
            if (button->isChecked()) {
                count++;
            }
        }
    }
    if (count == 2) {
        for (int i = 0; i < gridLayout->count(); ++i) {
            QPushButton* button = qobject_cast<QPushButton*>(gridLayout->itemAt(i)->widget());

            if (button->isChecked()) {
                for (int j = 0; j < gridLayout->count(); ++j) {
                    QPushButton* button2 = qobject_cast<QPushButton*>(gridLayout->itemAt(j)->widget());
                    // and button2 should be different from button

                    if (button2->isChecked() && button != button2 ) {

                        qDebug() << "Clicked button with item number:" << button2->property("id").toInt();
                        qDebug() << "Clicked button with item number:" << button->property("id").toInt();
                        if (button->text() == button2->text()) {
                            Score = Score + 1;
                            QString ScoreString = QString::number(Score);
                            ScoreText->setText(ScoreString);
                            if(Score == 15) {
                                QMessageBox::information(this, "Game Over", "You have won the game");

                            }
                            button->setChecked(false);
                            button2->setChecked(false);
                            button->setDisabled(true);
                            button2->setDisabled(true);
                        }
                        else {
                            qDebug() << "Clicked button with item number:" << button->property("id").toInt();
                            Tries = Tries -0.5;
                            qDebug() << "try :" << Tries;
                            QString TriesString = QString::number(Tries);
                            TriesText->setText(TriesString);

                            if(Tries == 0) {
                                flag = true;
                                QMessageBox::information(this, "Game Over", "You have no more tries left");
                                for (int i = 0; i < gridLayout->count(); ++i) {
                                    QPushButton* button = qobject_cast<QPushButton*>(gridLayout->itemAt(i)->widget());
                                    if (button) {
                                        button->setDisabled(true);
                                    }
                                }
                            }


                            QTimer::singleShot(500, [button, button2]() {

                                button->setChecked(false);
                                button2->setChecked(false);
                                button->setText("");
                                button2->setText("");
                            });
                            if(flag == false) {
                                button->setDisabled(false);
                                button2->setDisabled(false);
                            }
                        }
                        break;


                    }


                }
            }

        }
    }

}


void MainWindow::on_PushButton_NewGame_clicked()
{
    // Shuffle the fruit

    Score = 0;
    Tries = 50;
    QString ScoreString = QString::number(Score);
    QTextEdit* ScoreText = ui->textEdit_2;
    ScoreText->setText(ScoreString);

    QString TriesString = QString::number(Tries);
    QTextEdit* TriesText = ui->textEdit_4;
    TriesText->setText(TriesString);


    for (int i = 0; i < 30; i++) {
        int random = rand() % 30;
        QString temp = fruit[i];
        fruit[i] = fruit[random];
        fruit[random] = temp;
    }
    qDebug() << fruit;
    // Set the text of the buttons
    QGridLayout* gridLayout = ui->gridLayout;

    for (int i = 0; i < gridLayout->count(); ++i) {
        qDebug() << fruit[i];
        QPushButton* button = qobject_cast<QPushButton*>(gridLayout->itemAt(i)->widget());
        if (button) {
            disconnect(button, &QPushButton::clicked, this, &MainWindow::handleButtonClicked);
        }
    }
    // Make the buttons checkable and connect the clicked signal to the handleButtonClicked slot

    for (int i = 0; i < gridLayout->count(); ++i) {
        QPushButton* button = qobject_cast<QPushButton*>(gridLayout->itemAt(i)->widget());
        if (button) {
            button->setEnabled(true);
            button->setCheckable(true);
            button->setChecked(false);
            button->setEnabled(true);
            button->setText("");
            button->setProperty("id", i );
            connect(button, &QPushButton::clicked, this, &MainWindow::handleButtonClicked);

        }
    }



}


