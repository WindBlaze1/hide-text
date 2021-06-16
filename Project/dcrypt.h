#ifndef DCRYPT_H
#define DCRYPT_H

#include <QDialog>

namespace Ui {
class dcrypt;
}

class dcrypt : public QDialog
{
    Q_OBJECT

public:
    explicit dcrypt(QWidget *parent = nullptr, QString file = "0",QString key = "0", int k = 0);
    ~dcrypt();
    QString file;
    QString key;
    int k;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::dcrypt *ui;
signals:
    void showPrev();
};

#endif // DCRYPT_H
