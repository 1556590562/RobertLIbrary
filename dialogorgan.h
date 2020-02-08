#ifndef DIALOGORGAN_H
#define DIALOGORGAN_H

#include <QDialog>

namespace Ui {
class DialogOrgan;
}

class DialogOrgan : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOrgan(QWidget *parent = nullptr);
    ~DialogOrgan();

    void InitCbB();
    float Get_OrganScores();
    QString Get_ObjectName();

private slots:
    void on_pbt_Ok_clicked();

private:
    Ui::DialogOrgan *ui;

    float OrganScores;
    QString ObjectName;
};

#endif // DIALOGORGAN_H
