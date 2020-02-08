#ifndef DIALOGCOMPREHENSIVE_H
#define DIALOGCOMPREHENSIVE_H

#include <QDialog>
#include <QStringListModel>

#define MAXSIZE 10

namespace Ui {
class DialogComprehensive;
}

class DialogComprehensive : public QDialog
{
    Q_OBJECT

public:
    explicit DialogComprehensive(QWidget *parent = nullptr);
    ~DialogComprehensive();

    float Get_ComScores();
    QStringList Get_ObjectName();

private slots:
    void on_pbt_AwardAdd_clicked();

    void on_pbt_SCOk_clicked();

    void on_pbt_SLPCOk_clicked();

    void on_pbt_ECAdd_clicked();

private:
    Ui::DialogComprehensive *ui;
    QStringListModel *strlist;
    QStringList *slist;

    float ComScores;
    float preScores[MAXSIZE],preScores2[MAXSIZE];
    int preSP,preSP2;

    void preSP_Adjust();

    void InitUi();
};

#endif // DIALOGCOMPREHENSIVE_H
