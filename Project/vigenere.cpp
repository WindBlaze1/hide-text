#include "vigenere.h"
#include "ui_vigenere.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

Vigenere::Vigenere(QWidget *parent, QString name) :
    QDialog(parent), file_name(name),
    ui(new Ui::Vigenere)
{
    ui->setupUi(this);
    this->setWindowTitle("Cryptography - Vigenère Cipher");
    this->setFixedSize(400,150);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Vigenere::~Vigenere()
{
    delete ui;
}

bool isAllowed(QString str){
    if(str == "")
        return false;
    std::string s = str.toUtf8().constData();
    for(size_t i(0); i<s.size(); i++){
        if(s[i]==' ')
            return false;
    }
    return true;
}

void Vigenere::on_pushButton_clicked()
{
    QMessageBox::information(this,"Vigenère Cipher", "Key should be a word of English language.\nThis is not Case-Sensitive\nIMPORTANT: Word should not contain spaces."
                                                     "\nNOTE: Vigenère Cipher can only encrypt English words.");
}


void Vigenere::on_pushButton_2_clicked()
{
    this->destroy();
    emit showCrypto();
}

void Vigenere::on_pushButton_next_clicked()
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
    if(!isAllowed(ui->lineEdit_key->text())){
        QMessageBox::warning(this, "<!>input_error<!>","The Key is invalid.\nTry Again.");
        return;
    }

    if(ui->radioButton_encrypt->isChecked()) {
        int ret(0);
        QString out = QFileDialog::getSaveFileName(this,"Select Save File location",QDir::homePath() + "/encrypted","Text File(*.txt)");
         ret = for_encrypt(file_name.toStdString(), out.toStdString(), ui->lineEdit_key->text().toStdString(), 2);
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
        dec = new dcrypt(this,file_name,ui->lineEdit_key->text(),2);
        this->hide();
        connect(dec,&dcrypt::showPrev,this,&Vigenere::show);
        dec->show();
    }
}
