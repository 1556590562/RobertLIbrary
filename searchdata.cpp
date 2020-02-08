#include "searchdata.h"
#include "ui_searchdata.h"

SearchData::SearchData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchData)
{
    ui->setupUi(this);
}

SearchData::~SearchData()
{
    delete ui;
}

QString SearchData::Get_SearchName()
{
    if(!ui->led_SearchName->text().isNull()){
        return ui->led_SearchName->text();
    }else{
        return "none";
    }
}

QString SearchData::Get_SearchNum()
{
    if(!ui->led_SearchNum->text().isNull()){
        return ui->led_SearchNum->text();
    }else{
        return "none";
    }
}

QString SearchData::Get_SearchPost()
{
    if(!ui->led_SearchPost->text().isNull()){
        return ui->led_SearchPost->text();
    }else{
        return "none";
    }
}

QString SearchData::Get_SearchOther()
{
    if(!ui->led_SearchOther->text().isNull()){
        return ui->led_SearchOther->text();
    }else{
        return "none";
    }
}

QString SearchData::Get_SearchRange()
{
    if(!ui->led_SearchRange->text().isNull()){
        return ui->led_SearchRange->text();
    }else{
        return "none";
    }
}

QString SearchData::Get_SearchScores()
{
    if(!ui->led_SearchScore->text().isNull()){
        return ui->led_SearchScore->text();
    }else{
        return "none";
    }
}

void SearchData::on_pbt_Search_clicked()
{

}
