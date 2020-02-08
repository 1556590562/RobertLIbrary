#ifndef DIALOGSPECIALM_H
#define DIALOGSPECIALM_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class DialogSpecialM;
}

class DialogSpecialM : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSpecialM(QWidget *parent = nullptr);
    ~DialogSpecialM();

    float Get_SMScores();
    QStringList Get_ObjectName();

private slots:
    void on_pbt_SMAdd_clicked();

    void InitUi();

private:
    Ui::DialogSpecialM *ui;

    float SMScores;

    QStringListModel *theListModel;
    QStringList *theList;
};

#endif // DIALOGSPECIALM_H
