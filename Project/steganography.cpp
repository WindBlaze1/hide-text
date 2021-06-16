#include "steganography.h"
#include "ui_steganography.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QIcon>
#include <QDir>

Steganography::Steganography(QWidget *parent) :
    QDialog(parent),file_name("0"),
    ui(new Ui::Steganography)
{
    ui->setupUi(this);
    this->setFixedSize(400,300);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Steganography::~Steganography()
{
    delete ui;
}

void Steganography::on_pushButton_clicked()
{
    file_name = QFileDialog::getOpenFileName(this, "Select a file", QDir::homePath(),"Audio or Image file(*.wav *.bmp)");
}

void Steganography::on_pushButton_2_clicked()
{
    std::string str = file_name.toUtf8().constData();
    if(!ui->radioButton_decode->isChecked() && !ui->radioButton_encode->isChecked()){
        QMessageBox msg(this);
        msg.setWindowIcon(QIcon(":/img/warning.png"));
        msg.warning(this,"<!>input_error<!>",
                             "Select one of the two options:\nEncode\nDecode\nbefore clicking Next.");
        return;
    }
    if(file_name == "0"){
        QMessageBox::warning(this,"<!>input_error<!>","Choose a file from your device before clicking Next.");
        return;
    }

    if(ui->radioButton_decode->isChecked()){
        dec = new decode(this, file_name);
        connect(dec,&decode::showStego,this,&Steganography::show);
        this->hide();
//        dec->set_path(file_name);
        dec->show();
    }

    if(ui->radioButton_encode->isChecked()){
        enc = new Encode(this);
        connect(enc,&Encode::showStego,this,&Steganography::show);
        this->hide();
        enc->set_target(file_name);
//        QMessageBox::information(this,"Info",file_name);
        enc->show();
    }
}

void Steganography::on_pushButton_3_clicked()
{
    this->destroy();
    emit showMain();
}
