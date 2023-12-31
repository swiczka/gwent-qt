#include "difficultydialog.h"
#include "ui_difficultydialog.h"

//#include "mainwindow.h"

DifficultyDialog::DifficultyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DifficultyDialog)
{
    this->setFixedSize(363, 170);
    ui->setupUi(this);
    this->setWindowTitle("Gwent - Difficulty Selection");
}

DifficultyDialog::~DifficultyDialog()
{
    delete ui;
}

int DifficultyDialog::getDifficulty(){
    return difficulty;
}

void DifficultyDialog::on_okButton_clicked()
{
    difficulty = ui->diffComboBox->currentIndex() + 1;
    qDebug() << difficulty;
    this->accept();
}

void DifficultyDialog::on_cancelButton_clicked()
{
    this->close();
}

