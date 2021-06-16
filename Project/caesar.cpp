#include "caesar.h"
#include "ui_caesar.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

Caesar::Caesar(QWidget *parent, QString name) :
    QDialog(parent), file_name(name),
    ui(new Ui::Caesar)
{
    ui->setupUi(this);
    this->setWindowTitle("Cryptography - Caesar Cipher");
    this->setFixedSize(400,150);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Caesar::~Caesar()
{
    delete ui;
}

void Caesar::on_pushButton_clicked()
{
    QMessageBox::information(this,"Caesar Cipher","The Key Should be a Positive Number.\nNOTE: Caesar Cipher can only encrypt English words.");
}

void Caesar::on_pushButton_2_clicked()
{
    this->destroy();
    emit showCrypto();
}


void Caesar::on_pushButton_next_clicked()
{
    if(!ui->radioButton_decrypt->isChecked() && !ui->radioButton_encrypt->isChecked()){
        QMessageBox msg(this);
        msg.setWindowIcon(QIcon(":/img/warning.png"));
        msg.warning(this,"<!>input_error<!>",
                             "Select one of the two options:\nEncrypt\nDecrypt\nbefore clicking Next.");
        return;
    }
    if(ui->lineEdit_key->text() == ""){
        QMessageBox::warning(this,"<!>input_error<!>","Write a key before clicking Next.\nIf you have no idea about the key, \n Click on the top-right corner(?).");
        return;
    }

    if(ui->radioButton_encrypt->isChecked()) {
        int ret(0);
        QString out = QFileDialog::getSaveFileName(this,"Select Save File location",QDir::homePath() + "/encrypted","Text File(*.txt)");
         ret = for_encrypt(file_name.toStdString(), out.toStdString(), ui->lineEdit_key->text().toStdString(), 1);
        if(!ret){
            QMessageBox::information(this,"Success!","Encoded and Saved successfully!");
            this->destroy();
            emit showCrypto();
        }
        if(ret){
            QMessageBox::critical(this, "Error!", "Error in opening file.\nRun the program as an administrator and try again.");
            return;
        }
    }
    if(ui->radioButton_decrypt->isChecked()) {
        dec = new dcrypt(this,file_name,ui->lineEdit_key->text(),1);
        this->hide();
        connect(dec,&dcrypt::showPrev,this,&Caesar::show);
        dec->show();
    }
}
