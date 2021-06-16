#include "encryption.h"
#include "ui_encryption.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

encryption::encryption(QWidget *parent) :
    QDialog(parent), text_file("0"),
    ui(new Ui::encryption)
{
    ui->setupUi(this);
    this->setFixedSize(400,300);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

encryption::~encryption()
{
    delete ui;
}

void encryption::on_pushButton_browse_clicked()
{
    text_file = QFileDialog::getOpenFileName(this, "Select a file", QDir::homePath(),"Text File(*.txt)");
}

void encryption::on_pushButton_back_clicked()
{
    this->destroy();
    emit showMain();
}

void encryption::on_pushButton_next_clicked()
{
    if(!ui->radioButton_dec->isChecked() && !ui->radioButton_enc->isChecked()){
        QMessageBox::warning(this,"<!>input_error<!>",
                             "Select one of the two options:\nEncrypt\nDecrypt\nbefore clicking Next.");
        return;
    }
    if(text_file == "0"){
        QMessageBox::warning(this,"<!>input_error<!>","Choose a file from your device before clicking Next.");
        return;
    }
    if(ui->radioButton_enc->isChecked()){
        encrypt = new class rsa_encrypt(this, text_file);
        connect(encrypt, &rsa_encrypt::showPrev,this,&encryption::show);
        this->hide();
        encrypt->show();
    }
    if(ui->radioButton_dec->isChecked()){
        decrypt = new class rsa_decrypt(this,text_file);
        connect(decrypt, &rsa_decrypt::showPrev,this,&encryption::show);
        this->hide();
        decrypt->show();
    }
}
