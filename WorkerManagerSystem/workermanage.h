#ifndef __WORKMANAGE_H_
#define __WORKMANAGE_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include "worker.h"
#include "manager.h"
#include "employee.h"

using namespace std;

#define FILENAME "worker.txt"
class WorkerManage
{
public:
    WorkerManage();

    // 文件是非为空的标志
    bool m_FileIsEmpty;
    // 获取文件内员工个数
    int getEmpNum();

    // 员工人数
    int m_EmpNum;
    // 员工空间
    Worker **m_EmpWorkerArray;
    // 添加新员工函数
    void addEmpWorker();
    // 新增员工信息保存到文件
    bool saveWorkerData();
    // 显示所ii有员工信息
    bool shopWorkerData();
    // 根据职工编号判断员工是否存在
    int workerIsExit(int id);
    // 根据员工编号删除员工
    bool deleteWorker();
    // 置空文件，但是不会删除员工数组指针指向的数据
    void rmAll();
    // 修改职工信息
    void modifyWorkerData();
    // 查找职工信息
    bool selectWorkerData();
    // 显示菜单
    void shopMenus();
    // 按任意键继续...
    char anyGoon();
    // 建立主键--员工编号，不能重复添加
    bool idIsExit(int id); // 返回true说明主键存在，返回false说明主键不存在，可以添加
    // 又是数据文件会出现重复数据，但是只想员工的指针数组并没有出错，所以重新保存指针数值指向的数据以达到刷新
    bool refreshWorkerData();
    // 按照员工编号排序
    bool sort_Worker_Id();
    ~WorkerManage();
};

#endif