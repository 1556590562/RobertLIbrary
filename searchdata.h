#ifndef SEARCHDATA_H
#define SEARCHDATA_H

#include <QDialog>

namespace Ui {
class SearchData;
}

class SearchData : public QDialog
{
    Q_OBJECT

public:
    explicit SearchData(QWidget *parent = nullptr);
    ~SearchData();
    QString Get_SearchName();
    QString Get_SearchNum();
    QString Get_SearchPost();
    QString Get_SearchOther();
    QString Get_SearchScores();
    QString Get_SearchRange();

private slots:
    void on_pbt_Search_clicked();

private:
    Ui::SearchData *ui;
};

#endif // SEARCHDATA_H
