#include <iostream>
#include "employee.h"
#include "worker.h"
#include "workermanage.h"
#include "manager.h"
using namespace std;

int main()
{
    int menu_flag;     // 设置选择菜单标志位
    WorkerManage man1; // 创建管理对象
    // Worker *w = NULL;
    // w = new Employee(101, "张三", 0, 3);
    // w->shopInfo();
    // w = new Manager(10, "王", 1, 2);
    // w->shopInfo();
    while (1)
    {
        man1.shopMenus();
        cout << "请输入需要操作的序号：" << endl;
        cin >> menu_flag;

        switch (menu_flag)
        {
        case 0:
            cout << "欢迎下次使用，再见\n";
            return 0;
            break;
        case 1:
            // addWorkData();
            system("clear");
            man1.addEmpWorker();
            // man1.saveWorkerData(); // 该保存数据功能的函数写到主函数会引发部分问题，如：写入数据有误，或者为空，保存的函数将失效出错
            man1.anyGoon();
            // cout << "暂无开发此功能，敬请期待。\n";
            break;
        case 2:
            system("clear");
            man1.shopWorkerData();
            man1.anyGoon();
            break;
        case 3:
            if (man1.deleteWorker())
            {
                cout << "删除成功\n";
            }
            man1.anyGoon();
            break;
        case 4:
            man1.modifyWorkerData();
            man1.anyGoon();
            // cout << "暂无开发此功能，敬请期待。\n";
            break;
        case 5:
            man1.selectWorkerData();
            man1.anyGoon();
            break;
        case 6:

            if (man1.sort_Worker_Id())
                cout << "排序成功\n";
            else
                cout << "排序失败\n";
            man1.anyGoon();
            break;
        case 7:
            if (!man1.refreshWorkerData())
            {
                cout << "刷新失败。\n";
                man1.anyGoon();
                continue;
            }
            cout << "刷新成功。\n";
            man1.anyGoon();
            break;
        case 8:
            cout << "测试程序\n";
            cout << man1.idIsExit(123) << endl;
            break;
        case 9:
        {
            string confirm_str;
            cout << "确认删库跑路？(Yes or No)??\n";
            cin >> confirm_str;
            if (confirm_str == "Yes" || confirm_str == "yes" || confirm_str == "Y" || confirm_str == "YEs" || confirm_str == "YES" || confirm_str == "y")
            {
                man1.rmAll();
                man1.m_EmpWorkerArray = NULL;
                man1.m_EmpNum = 0;
                man1.m_FileIsEmpty = true;
                cout << "删除成功！赶紧跑路！！！！！\n";
                man1.anyGoon();
                break;
            }
            man1.anyGoon();
            break;
        }
        default:
            cout << "输入序号有误，请重新输入！！" << endl;
        }
    }
    return 0;
}