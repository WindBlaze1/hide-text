#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QDialog>
#include "rsa_decrypt.h"
#include "rsa_encrypt.h"

namespace Ui {
class encryption;
}

class encryption : public QDialog
{
    Q_OBJECT

public:
    explicit encryption(QWidget *parent = nullptr);
    ~encryption();
    QString text_file;

private:
    Ui::encryption *ui;
    class rsa_decrypt *decrypt;
    class rsa_encrypt *encrypt;

signals:
    void showMain();
private slots:
    void on_pushButton_browse_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_next_clicked();
};

#endif // ENCRYPTION_H
