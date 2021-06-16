#include "decode.h"
#include "ui_decode.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>

decode::decode(QWidget *parent, QString file) :
    QDialog(parent),
    file_path(file),
    ui(new Ui::decode)
{
    ui->setupUi(this);
    this->setWindowTitle("Decode - Steganography");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setFixedSize(400,500);
    QString text;
    std::string str_text;
    str_text = for_decode(file_path.toUtf8().constData());
    text = QString::fromStdString(str_text);
    ui->textBrowser->setText(text);
}

decode::~decode()
{
    delete ui;
}

void decode::on_pushButton_clicked()
{
    this->destroy();
    emit showStego();
}

void decode::on_pushButton_2_clicked()
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
