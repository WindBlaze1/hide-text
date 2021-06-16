#include "dcrypt.h"
#include "ui_dcrypt.h"
#include "crypgraphy.h"
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

dcrypt::dcrypt(QWidget *parent, QString f, QString kk, int n) :
    QDialog(parent), file(f), key(kk), k(n),
    ui(new Ui::dcrypt)
{
    ui->setupUi(this);
    this->setWindowTitle("Cryptography - Decrypt");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setFixedSize(400,500);
    QString text;
    std::string str_text;
    str_text = for_decrypt(file.toStdString(), key.toStdString(), n, "1.txt");
    text = QString::fromStdString(str_text);
    ui->textBrowser->setText(text);
}

dcrypt::~dcrypt()
{
    delete ui;
}

void dcrypt::on_pushButton_clicked()
{
    this->destroy();
    emit showPrev();
}

void dcrypt::on_pushButton_2_clicked()
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
