#include "myfunctions.h"

MyFunctions::MyFunctions()
{


}

QString MyFunctions::KeepTwo_Float(float f,int i)
{
    QString str;
    return str.setNum(f,'f',i);
}
