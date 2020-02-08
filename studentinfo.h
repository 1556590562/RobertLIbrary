#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QString>
#include <mainwindow.h>

class StudentInfo
{
public:
    StudentInfo();
    void Updata(MainWindow *Mwindow);

private:
    QString *stuNum=nullptr,*stuName=nullptr,*isPassAllExam=nullptr,*isCLeader=nullptr,*FKinds=nullptr,*Others=nullptr;
    int range_Basis=0,range_Dev=0,range_Comp=0;
    float Score_Dexz=0,Score_Dexb=0,Score_DeSum=0,Score_DeF=0,Score_Zhi=0,Score_ZiF=0,Score_Ti=0,Score_TiF=0,Score_Basis=0,Score_Dev=0,Score_Comp=0;

public:
    void Set_stuNum(QString);
    void Set_stuName(QString);
    void Set_isCLeader(bool);
    void Set_isPassAllExam(bool);
    void Set_Dexz(float);
    void Set_Dexb(float);
    void Set_ScoreZhi(float);
    void Set_ScoreTi(float);
    void Set_ScoreDev(float);
    QString Get_stuNum();
    QString Get_stuName();
    QString Get_isCLeader();
    QString Get_isPassAllExam();
    float Get_Dexz();
    float Get_Dexb();
    float Get_ScoreZhi();
    float Get_ScoreTi();
    float Get_ScoreDev();
};

#endif // STUDENTINFO_H
