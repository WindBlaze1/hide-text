#ifndef RSA_ENCRYPT_H
#define RSA_ENCRYPT_H

#include <QDialog>
#include "rsa.h"

namespace Ui {
class rsa_encrypt;
}

class rsa_encrypt : public QDialog
{
    Q_OBJECT

public:
    explicit rsa_encrypt(QWidget *parent = nullptr, QString s = "0");
    ~rsa_encrypt();
    QString file_name;

private:
    Ui::rsa_encrypt *ui;
signals:
    void showPrev();
private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_netx_clicked();
};

#endif // RSA_ENCRYPT_H
