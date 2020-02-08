#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogadds.h"
#include "dialogorgan.h"
#include "dialogcomprehensive.h"
#include "dialogspecialm.h"
#include <signal.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    float Get_DeScore();
    float Get_DeScore2();
    float Get_ZhiScore();
    float Get_TiScore();
    float Get_SumScore();
    QString Get_CPinfo();
    QString Get_StuNum();
    QString Get_StuName();
    void Set_AlterStuNum(QString stuName,QString stuNum,QString Dexz,QString Dexb,QString Zhi,QString Ti,QString Fz);

private slots:
    void on_pushButton_clicked();

    void on_pbt_AddScores_clicked();

    void on_pbt_AddOtherScores_clicked();

    void on_pushButton_2_clicked();

    void on_pbt_SMAdd_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pbt_ReSet_clicked();

    void on_pbt_Finish_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;

    DialogAddS *dlgAdds=nullptr;
    DialogOrgan *dlgOrgan=nullptr;
    DialogComprehensive *dlgComprehensive=nullptr;
    DialogSpecialM *dlgSpecialM=nullptr;

    float DeScores1;
    float DeScores2;
    float ZhiScores;
    float TiScores;
    float SumScores;
signals:
    void Update_Completed();
};

#endif // MAINWINDOW_H
