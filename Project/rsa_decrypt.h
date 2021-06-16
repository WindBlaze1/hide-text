#ifndef RSA_DECRYPT_H
#define RSA_DECRYPT_H

#include <QDialog>
#include "rsa.h"
#include "rsa_decrypt_final.h"

namespace Ui {
class rsa_decrypt;
}

class rsa_decrypt : public QDialog
{
    Q_OBJECT

public:
    explicit rsa_decrypt(QWidget *parent = nullptr, QString file = "0");
    ~rsa_decrypt();
    QString file_name;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::rsa_decrypt *ui;
    rsa_decrypt_final *d_fin;

signals:
    void showPrev();
};

#endif // RSA_DECRYPT_H
