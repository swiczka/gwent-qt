#ifndef DIFFICULTYDIALOG_H
#define DIFFICULTYDIALOG_H

#include <QDialog>

namespace Ui {
class DifficultyDialog;
}

class DifficultyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DifficultyDialog(QWidget *parent = nullptr);
    int getDifficulty();
    ~DifficultyDialog();

private:
    Ui::DifficultyDialog *ui;
    int difficulty;

signals:
    void difficultySelected(int difficulty);

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
};

#endif // DIFFICULTYDIALOG_H
