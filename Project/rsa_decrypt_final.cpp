#include "rsa_decrypt_final.h"
#include "ui_rsa_decrypt_final.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>

rsa_decrypt_final::rsa_decrypt_final(QWidget *parent, long long int p1, long long int p2, QString file_name) :
    QDialog(parent), p1(p1), p2(p2), file_name(file_name),
    ui(new Ui::rsa_decrypt_final)
{
    ui->setupUi(this);
    this->setFixedSize(400,300);
    this->setWindowTitle("Encryption - RSA");
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    string str;
    str = rsa_dec(file_name.toStdString(), p1, p2);
    QString data = QString::fromStdString(str);
    ui->textBrowser->setText(data);
}

rsa_decrypt_final::~rsa_decrypt_final()
{
    delete ui;
}

void rsa_decrypt_final::on_pushButton_2_clicked()
{
    QString save_dir = QFileDialog::getSaveFileName(this, "Save text as file", QDir::currentPath() + "/message", "Text file(*.txt)");
    QFile file(save_dir);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::critical(this, "Error!", "Error in opening file.\nRun the program as an administrator and try again.");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textBrowser->toPlainText();
    out << text;
    file.flush();
    file.close();
    QMessageBox::information(this, "Success!", "File Saved Successfully!");
}

void rsa_decrypt_final::on_pushButton_clicked()
{
    this->destroy();
    emit showPrev();
}
