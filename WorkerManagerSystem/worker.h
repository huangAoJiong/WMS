#ifndef __WORK_H_
#define __WORK_H_
#include <iostream>
#include <string>

using namespace std;
class Worker
{
public:
    virtual void shopInfo() = 0;
    virtual string getPartName() = 0;

    int m_Id;      // 编号
    string m_Name; // 姓名
    int m_PartId;  // 部门id   1:boos   2:manager   3:employee
    int m_Gender;  // 性别0：男    1：女
private:
};

#endif