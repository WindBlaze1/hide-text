#include "rsa_encrypt.h"
#include "ui_rsa_encrypt.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QClipboard>

rsa_encrypt::rsa_encrypt(QWidget *parent, QString file) :
    QDialog(parent), file_name(file),
    ui(new Ui::rsa_encrypt)
{
    ui->setupUi(this);
    this->setFixedSize(400,300);
    this->setWindowTitle("Encryption - RSA");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

rsa_encrypt::~rsa_encrypt()
{
    delete ui;
}

void rsa_encrypt::on_pushButton_back_clicked()
{
    this->destroy();
    emit showPrev();
}

void rsa_encrypt::on_pushButton_netx_clicked()
{
    if(!ui->radioButton_gen->isChecked() && !ui->radioButton_have->isChecked()){
        QMessageBox::warning(this,"<!>input_error<!>","You need select one of the given options before clicking Encrypt.");
        return;
    }
    if(ui->radioButton_have->isChecked() && (ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "")){
        QMessageBox::warning(this,"<!>input_error<!>","You need to write a key before clicking Encrypt.");
        return;
    }
    QString save_loc = QFileDialog::getSaveFileName(this, "Select new file Save Location", QDir::currentPath()+"/hidden","Text file(*.txt)");
    Keys key = generate_keys();
    int erno = rsa_enc(save_loc.toStdString(), file_name.toStdString(), key.public_key.first, key.public_key.second);
    if(erno){
        QMessageBox::critical(this, "Error!", "Error in opening file.\nRun the program as an administrator and try again.");
        return;
    }
    std::string str = "Encrypted and Saved Successfully!\nKeys Generated:\nPublic Key: "+ std::to_string(key.public_key.first) +":"
                        + std::to_string(key.public_key.second) +"\nPrivate Key: "+ std::to_string(key.private_key.first)
                        +":"+ std::to_string(key.private_key.second) +""
                      "\n\nStore the keys carefully. Only share the Public Key with colleagues. "
                      "Do not share the Private Key. This Private Key will be used for Decrypting the message.";
//    QMessageBox::information(this, "Success!",QString::fromStdString(str));
    QMessageBox msg(this);
    msg.setText(QString::fromStdString(str));
    msg.setWindowTitle("Success!");
    msg.setStandardButtons(QMessageBox::Ok);
    QAbstractButton* copy_button = msg.addButton(tr("Close and Copy Keys to Clipboard"),QMessageBox::AcceptRole);
    msg.exec();
    if(msg.clickedButton() == copy_button){
        str = "Public Key: " + std::to_string(key.public_key.first) + ":" + std::to_string(key.public_key.second)
              + "\nPrivate Key: " + std::to_string(key.private_key.first) + ":" + std::to_string(key.private_key.second);
        QClipboard *c(QGuiApplication::clipboard());
        c->setText(QString::fromStdString(str),QClipboard::Clipboard);
    }
    this->destroy();
    emit showPrev();
}
