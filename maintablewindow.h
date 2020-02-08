#ifndef MAINTABLEWINDOW_H
#define MAINTABLEWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "studentinfo.h"
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <signal.h>
#include <loading.h>
#include "searchdata.h"
#include <QLabel>

#define TABLECOLUMNCOUNT 20
#define Buffcount 6

namespace Ui {
class MainTableWindow;
}

class MainTableWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainTableWindow(QWidget *parent = nullptr);
    ~MainTableWindow();

private:
    Ui::MainTableWindow *ui;
    QStandardItemModel *theMTModel;
    QItemSelectionModel *theMTSModel;
    MainWindow *theMainWindow=nullptr;
    StudentInfo *stuInfo=nullptr;
    SearchData *theSearchWindow=nullptr;
    int StudenCount;
    QString FileName[Buffcount];
    QString CurFileName;
    int CURSTEP,UndoCount,RedoCount;

    void closeEvent(QCloseEvent *event);

    QLabel *statuLabel;

private slots:
    void Init_Table();
    void Init_PrivateData();
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_act_Add_triggered();
    void on_act_About_triggered();
    void MtoTupdata();
    void on_act_ToPrintFile_triggered();
    void on_act_OpenFile_triggered();
    void on_act_SaveTable_triggered();
    void on_act_Exit_triggered();
    void on_act_Delete_triggered();
    void on_act_Left_triggered();
    void on_act_Center_triggered();
    void on_act_Full_triggered();
    void on_act_Right_triggered();
    void on_act_SetFontColor_triggered();
    void on_headClicked(int);
    void on_act_DataCheck_triggered();
    void Auto_Save();

    void on_act_Undo_triggered();

    void on_act_Redo_triggered();

    void on_act_CloseFile_triggered();

    void on_act_Search_triggered();

    void on_act_Alter_triggered();

signals:
    void FinishSituaion(int s);
    void Data_Changed();
};

#endif // MAINTABLEWINDOW_H
