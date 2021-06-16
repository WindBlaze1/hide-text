#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <QDialog>
#include "caesar.h"
#include "vigenere.h"

namespace Ui {
class cryptography;
}

class cryptography : public QDialog
{
    Q_OBJECT

public:
    explicit cryptography(QWidget *parent = nullptr);
    ~cryptography();
    QString text_file_name;

private:
    Ui::cryptography *ui;
    Caesar *caesar;
    Vigenere *vig;
signals:
    void showMain();
private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // CRYPTOGRAPHY_H
