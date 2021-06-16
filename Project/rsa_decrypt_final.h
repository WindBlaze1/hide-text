#ifndef RSA_DECRYPT_FINAL_H
#define RSA_DECRYPT_FINAL_H

#include <QDialog>
#include "rsa.h"

namespace Ui {
class rsa_decrypt_final;
}

class rsa_decrypt_final : public QDialog
{
    Q_OBJECT

public:
    explicit rsa_decrypt_final(QWidget *parent = nullptr, long long int p1=0, long long int p2=0, QString file_name="0");
    ~rsa_decrypt_final();
    long long int p1,p2;
    QString file_name;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::rsa_decrypt_final *ui;

signals:
   void showPrev();
};

#endif // RSA_DECRYPT_FINAL_H
