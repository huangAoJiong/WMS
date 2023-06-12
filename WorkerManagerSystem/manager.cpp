#include "manager.h"

Manager::Manager(int id, string name, int gender, int partID)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_Gender = gender;
    this->m_PartId = partID;
}
void Manager::shopInfo()
{
    cout << "编号：" << m_Id << "\t"
         << "姓名：" << m_Name << "\t"
         << "性别：" << ((m_Gender == 0) ? "男" : "女") << "\t"
         << "部门岗位：" << this->getPartName() << endl;
}
string Manager::getPartName()
{
    return string("部长");
}