#include "studentinfo.h"

StudentInfo::StudentInfo()
{
    stuName=new QString;
    *stuName="张三";
    stuNum=new QString;
    *stuNum="2016222000";
    isCLeader=new QString;
    *isCLeader="否";
    isPassAllExam=new QString;
    *isPassAllExam="否";
}

void StudentInfo::Set_stuNum(QString str)
{
    *stuNum=str;
}
void StudentInfo::Set_stuName(QString str)
{
    *stuName=str;
}
void StudentInfo::Set_Dexb(float xb)
{
    Score_Dexb=xb;
}
void StudentInfo::Set_Dexz(float xz)
{
    Score_Dexz=xz;
}
void StudentInfo::Set_ScoreTi(float Ti)
{
    Score_Ti=Ti;
}
void StudentInfo::Set_ScoreDev(float Dev)
{
    Score_Dev=Dev;
}
void StudentInfo::Set_ScoreZhi(float Zhi)
{
    Score_Zhi=Zhi;
}
void StudentInfo::Set_isCLeader(bool t)
{
    if(t==true){
        *isCLeader="是";
    }else{
        *isCLeader="否";
    }
}
void StudentInfo::Set_isPassAllExam(bool t)
{
    if(t==true){
        *isCLeader="是";
    }else{
        *isCLeader="否";
    }
}

QString StudentInfo::Get_stuNum()
{
    return *stuNum;
}
float StudentInfo::Get_Dexb()
{
    return Score_Dexb;
}
QString StudentInfo::Get_stuName()
{
    return *stuName;
}
float StudentInfo::Get_Dexz()
{
    return Score_Dexz;
}
float StudentInfo::Get_ScoreTi()
{
    return Score_Ti;
}
float StudentInfo::Get_ScoreZhi()
{
    return  Score_Zhi;
}
float StudentInfo::Get_ScoreDev()
{
    return Score_Dev;
}
QString StudentInfo::Get_isCLeader()
{
    return *isCLeader;
}
QString StudentInfo::Get_isPassAllExam()
{
    return *isPassAllExam;
}
