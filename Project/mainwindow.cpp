#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QApplication::setWindowIcon(QIcon(":/img/data-encryption-14-900101.webp"));
    this->setWindowTitle("Data Structures Project");
//    this->windowIcon().;
    this->setFixedSize(600,500);
    statusBar()->setSizeGripEnabled(false);
    ui->statusbar->hide();
    QPixmap pic(":/img/4.jpg");
//    pic.scaled(227,451);
//    this->setCentralWidget(ui->pic_label);
    ui->pic_label->setPixmap(pic.scaled(227,451,Qt::KeepAspectRatio));
    QMessageBox mb("Made By",
                               "Harit",
                               QMessageBox::NoIcon,
                               QMessageBox::Ok | QMessageBox::Default,
                               QMessageBox::NoButton,
                               QMessageBox::NoButton);
    QPixmap about_us(":/img/information-about-us-icon-16.png");
    about_us = about_us.scaled(100,100);
    mb.setIconPixmap(about_us);
    mb.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    stego = new Steganography(this);
    this->hide();
//    stego->setModal(true);
    stego->setWindowTitle("Steganography");
    connect(stego,&Steganography::showMain,this,&MainWindow::show);
    stego->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    crypto = new cryptography(this);
    this->hide();
    crypto->setWindowTitle("Cryptography");
    connect(crypto,&cryptography::showMain,this,&MainWindow::show);
    crypto->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    encryp = new encryption(this);
    this->hide();
    encryp->setWindowTitle("Encryption - RSA");
    connect(encryp,&encryption::showMain,this,&MainWindow::show);
    encryp->show();
}
