#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <QDialog>
#include "encode.h"
#include "decode.h"

namespace Ui {
class Steganography;
}

class Steganography : public QDialog
{
    Q_OBJECT

public:
    explicit Steganography(QWidget *parent = nullptr);
    ~Steganography();
    QString file_name;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Steganography *ui;
    Encode *enc;
    decode *dec;
signals:
    void showMain();
};


#endif // STEGANOGRAPHY_H
