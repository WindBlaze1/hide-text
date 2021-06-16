#include "cryptography.h"
#include "ui_cryptography.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

cryptography::cryptography(QWidget *parent) :
    QDialog(parent), text_file_name("0"),
    ui(new Ui::cryptography)
{
    ui->setupUi(this);
    this->setFixedSize(400,300);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

cryptography::~cryptography()
{
    delete ui;
}

void cryptography::on_pushButton_3_clicked()
{
    this->destroy();
    emit showMain();
}

void cryptography::on_pushButton_clicked()
{
    text_file_name = QFileDialog::getOpenFileName(this, "Select a file", QDir::homePath(),"Text File(*.txt)");
}


void cryptography::on_pushButton_2_clicked()
{
    if(!ui->radioButton_caesar->isChecked() && !ui->radioButton_vigenere->isChecked()){
        QMessageBox msg(this);
        msg.setWindowIcon(QIcon(":/img/warning.png"));
        msg.warning(this,"<!>input_error<!>",
                             "Select one of the two options:\nCaesar Cipher\nVigenère Cipher\nbefore clicking Next.");
        return;
    }
    if(text_file_name == "0"){
        QMessageBox::warning(this,"<!>input_error<!>","Choose a file from your device before clicking Next.");
        return;
    }
    if(ui->radioButton_caesar->isChecked()){
        caesar = new Caesar(this,text_file_name);
        connect(caesar,&Caesar::showCrypto,this,&cryptography::show);
        this->hide();
        caesar->show();
    }
    if(ui->radioButton_vigenere->isChecked()){
        vig = new Vigenere(this, text_file_name);
        connect(vig,&Vigenere::showCrypto,this,&cryptography::show);
        this->hide();
        vig->show();
    }
}
