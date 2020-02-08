#ifndef DIALOGADDS_H
#define DIALOGADDS_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class DialogAddS;
}

class DialogAddS : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddS(QWidget *parent = nullptr);
    ~DialogAddS();
    float Get_InnovativeScores();
    void Compute_InnovativeScores();
    QStringList Get_ObjectList();

private slots:
    void on_pbt_Ok_clicked();

    void on_comboBox_AwardClass_activated(const QString &arg1);

private:
    Ui::DialogAddS *ui;
    QStringListModel *theListModel;
    QStringList *strList=nullptr;

    float InnovativeScores;
    QStringList ObjectList;
};

#endif // DIALOGADDS_H
