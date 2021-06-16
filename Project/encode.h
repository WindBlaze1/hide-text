#ifndef ENCODE_H
#define ENCODE_H

#include <QDialog>
#include <stegraphy.h>

namespace Ui {
class Encode;
}

class Encode : public QDialog
{
    Q_OBJECT

public:
    explicit Encode(QWidget *parent = nullptr);
    QString target_file;//For file_to_edit location
    QString msg;        //For message location
    QString save_loc;   //For save file location
    ~Encode();
    void set_target(QString str);

private:
    Ui::Encode *ui;

signals:
    void showStego();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

};

#endif // ENCODE_H
