#include "encode.h"
#include "ui_encode.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

Encode::Encode(QWidget *parent) :
    QDialog(parent),msg("0"),
    ui(new Ui::Encode)
{
    ui->setupUi(this);
    this->setWindowTitle("Encode - Steganography");
    this->setFixedSize(400,150);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Encode::~Encode()
{
    delete ui;
}

void Encode::on_pushButton_3_clicked()
{
    msg = QFileDialog::getOpenFileName(this, "Select a file", QDir::homePath(),"Text file(*.txt)");
}

void Encode::on_pushButton_clicked()
{
    this->destroy();
    emit showStego();
}

void Encode::on_pushButton_2_clicked()
{
    if(msg == "0"){
        QMessageBox::warning(this,"<!>input_error<!>","You need to choose a message file(.txt) before clicking Encode.");
        return;
    }
    std::string str = target_file.toUtf8().constData();
    int r_val;
    if(str.substr(str.size()-3,str.size()) == "bmp"){
        save_loc = QFileDialog::getSaveFileName(this, "Select new file Save Location", QDir::currentPath()+"/hidden","Image file(*.bmp)");
        r_val = for_encode(target_file.toUtf8().constData(), msg.toUtf8().constData(), save_loc.toUtf8().constData(),2);
    }
    else if(str.substr(str.size()-3,str.size()) == "wav"){
        save_loc = QFileDialog::getSaveFileName(this, "Select new file Save Location", QDir::currentPath()+"/hidden","Sound file(*.wav)");
        r_val = for_encode(target_file.toUtf8().constData(), msg.toUtf8().constData(), save_loc.toUtf8().constData(),1);
    }
    if(r_val==0){
        QMessageBox::information(this,"Success!","Encoded and Saved successfully!");
        this->destroy();
        emit showStego();
    }
    if(r_val == 1){
        QMessageBox::critical(this, "Error!", "Error in opening file.\nRun the program as an administrator and try again.");
        return;
    }
    if(r_val==2){
        QMessageBox::critical(this, "Error!", "Error in storing whole message.\nTarget file size is not big enough.\nTry again with an increased size target file");
        return;
    }
}

void Encode::set_target(QString str) {
    target_file = str;
}
