#include "rsa_decrypt.h"
#include "ui_rsa_decrypt.h"
#include <QMessageBox>

rsa_decrypt::rsa_decrypt(QWidget *parent, QString file) :
    QDialog(parent), file_name(file),
    ui(new Ui::rsa_decrypt)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle("Encryption - RSA");
    this->setFixedSize(400,150);
}

rsa_decrypt::~rsa_decrypt()
{
    delete ui;
}

void rsa_decrypt::on_pushButton_clicked()
{
    this->destroy();
    emit showPrev();
}

void rsa_decrypt::on_pushButton_3_clicked()
{
    if(ui->lineEdit->text() == "" || ui->lineEdit_2->text() == ""){
        QMessageBox::warning(this,"<!>input_error<!>","You need to write a key before clicking Decrypt.");
        return;
    }
    long long p1,p2;
    p1 = std::stoll(ui->lineEdit->text().toStdString());
    p2 = std::stoll(ui->lineEdit_2->text().toStdString());
    d_fin = new rsa_decrypt_final(this, p1, p2, file_name);
    connect(d_fin,&rsa_decrypt_final::showPrev,this,&rsa_decrypt::show);
    this->hide();
    d_fin->show();
}
