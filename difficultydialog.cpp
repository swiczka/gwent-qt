#include "difficultydialog.h"
#include "ui_difficultydialog.h"

#include "mainwindow.h"

DifficultyDialog::DifficultyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DifficultyDialog)
{
    ui->setupUi(this);
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

