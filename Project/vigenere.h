#ifndef VIGENERE_H
#define VIGENERE_H

#include <QDialog>
#include "dcrypt.h"
#include "crypgraphy.h"

namespace Ui {
class Vigenere;
}

class Vigenere : public QDialog
{
    Q_OBJECT

public:
    explicit Vigenere(QWidget *parent = nullptr, QString name = "0");
    ~Vigenere();
    QString file_name;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_next_clicked();

private:
    Ui::Vigenere *ui;
    dcrypt *dec;

signals:
    void showCrypto();
};

bool isallowed(QString s);

#endif // VIGENERE_H
