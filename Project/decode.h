#ifndef DECODE_H
#define DECODE_H

#include <QDialog>
#include <stegraphy.h>

namespace Ui {
class decode;
}

class decode : public QDialog
{
    Q_OBJECT

public:
    explicit decode(QWidget *parent = nullptr, QString file = "0");
    ~decode();
    QString file_path;
//    void set_path(QString);

signals:
    void showStego();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::decode *ui;
};

#endif // DECODE_H
