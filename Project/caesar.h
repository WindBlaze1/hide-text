#ifndef CAESAR_H
#define CAESAR_H

#include <QDialog>
#include "dcrypt.h"
#include "crypgraphy.h"

namespace Ui {
class Caesar;
}

class Caesar : public QDialog
{
    Q_OBJECT

public:
    explicit Caesar(QWidget *parent = nullptr, QString name = "0");
    ~Caesar();
    QString file_name;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_next_clicked();

private:
    Ui::Caesar *ui;
    dcrypt *dec;

signals:
    void showCrypto();
};

#endif // CAESAR_H
