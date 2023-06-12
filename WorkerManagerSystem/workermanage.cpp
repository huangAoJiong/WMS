#include "workermanage.h"

WorkerManage::WorkerManage()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    // 1、员工数据的txt文件不存在
    if (!ifs.is_open())
    {
        cout << "文件不存在\n";
        this->m_EmpNum = 0;
        this->m_EmpWorkerArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    // 2、员工数据文件存在，但是为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        cout << "文件为空\n";
        this->m_EmpNum = 0;
        this->m_EmpWorkerArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    else // 3、员工数据存在且不为空
    {
        this->m_EmpNum = this->getEmpNum();
        this->m_FileIsEmpty = false;
        string *tmp = new string[4];
        this->m_EmpWorkerArray = new Worker *[this->getEmpNum()];
        int id;
        string name;
        int gender;
        int partId;
        int count_flag = 0;
        while (ifs >> tmp[0] && ifs >> tmp[1] && ifs >> tmp[2] && ifs >> tmp[3])
        {
            Worker *worker = NULL;
            cout << "************哈哈哈哈哈哈哈哈*****:" << tmp[0] << endl;
            id = stoi(tmp[0].substr(tmp[0].find(":") + 1));
            name = (tmp[1].substr(tmp[1].find(":") + 1));
            gender = (tmp[2].substr(tmp[2].find(":") + 1) == "男") ? 0 : 1;
            partId = stoi(tmp[3].substr(tmp[3].find(":") + 1));
            if (partId == 2)
            {
                worker = new Manager(id, name, gender, partId);
            }
            else if (partId == 3)
            {
                worker = new Employee(id, name, gender, partId);
            }
            this->m_EmpWorkerArray[count_flag] = worker;
            count_flag++;
        }
        delete[] tmp;
    }

    ifs.close();
}

WorkerManage::~WorkerManage()
{
    if (this->m_EmpWorkerArray != NULL)
    {
        delete[] this->m_EmpWorkerArray;
        this->m_EmpWorkerArray = NULL;
    }
}
char WorkerManage::anyGoon()
{
    char buf = 0;
    struct termios old = {0};
    std::cout << "按下任意键继续..." << std::endl;
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");

    system("clear");
    return buf;
}
void WorkerManage::shopMenus()
{
    cout << "在职总人数:" << this->getEmpNum() << endl;
    cout << "\n************************************************************" << endl;
    cout << "******************欢迎使用职工管理系统**********************" << endl;
    cout << "****************** 0、退出系统 *****************************" << endl;
    cout << "****************** 1、添加职工信息 *************************" << endl;
    cout << "****************** 2、显示职工信息 *************************" << endl;
    cout << "****************** 3、删除职工信息 *************************" << endl;
    cout << "****************** 4、修改职工信息 *************************" << endl;
    cout << "****************** 5、查找职工信息 *************************" << endl;
    cout << "****************** 6、按照编号排序 *************************" << endl;
    cout << "****************** 7、 刷  新 *****************************" << endl;
    cout << "****************** 9、删库跑路 *****************************" << endl;
    cout << "************************************************************\n"
         << endl;
}
void WorkerManage::addEmpWorker()
{
    cout << "请输入需要添加员工人数:";
    int add_count = 0;
    cin >> add_count;
    if (add_count > 0)
    {
        // 计算新空间员工人数
        int newSize = this->m_EmpNum + add_count;
        // 开辟新空间
        Worker **newSpace = new Worker *[newSize];
        // 将原空间下的内容放到新空间
        if (this->m_EmpWorkerArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpWorkerArray[i];
            }
        }
        // 添加新数据
        for (int i = 0; i < add_count; i++)
        {
            int id;
            string name;
            int gender;
            int partId;
            cout << "请输入新增员工ID:";
            cin >> id;
            while (this->idIsExit(id))
            {
                cout << "修改的ID已存在，请重新输入:";
                cin >> id;
            }
            cout << "请输入新增员工姓名:";
            cin >> name;
            cout << "请输入新增员工性别:\n0:男\n1:女\n ";
            cin >> gender;
            cout << "请输入职工岗位:\n1:Boos （暂无岗位）\n2:经理\n3:普通员工\n";
            cin >> partId;
            Worker *worker = NULL;
            switch (partId)
            {
            case 1: // Boos
                /* code */
                ;
                // break;
            case 2: // manager
                /* code */
                worker = new Manager(id, name, gender, partId);
                break;
            case 3: // employee
                /* code */
                worker = new Employee(id, name, gender, partId);
                break;

            default:
                break;
            }
            newSpace[this->m_EmpNum + i] = worker;
        }
        // 释放原有空间
        delete[] this->m_EmpWorkerArray;
        // 更改新空间的指向数据
        this->m_EmpWorkerArray = newSpace;
        this->m_EmpNum = newSize;
        this->saveWorkerData();
        cout << "添加成功" << add_count << "名新职工\n\n";
    }
    else
    {
        cout << "输入人数有误，请检查重试！\n";
    }
    this->m_FileIsEmpty = false;
}
// 置空文件
void WorkerManage::rmAll()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    ofs << "";
    ofs.close();
    // 员工指针清零，员工人数清0,文件为空标志转换true
    // this->m_EmpWorkerArray = NULL;
    // this->m_EmpNum = 0;
    // this->m_FileIsEmpty = true;
}
// 根据员工编号删除员工
bool WorkerManage::deleteWorker()
{
    int id = -1;
    cout << "请输入要删除的职工编号（ID）:" << endl;
    cin >> id;
    cout << id;
    if ((this->workerIsExit(id)) == -1)
    {
        cout << "选择的职工编号不存在\n";
        return false;
    }
    else
    {
        for (int i = (this->workerIsExit(id)); i < this->m_EmpNum - 1; i++)
        {
            this->m_EmpWorkerArray[i] = this->m_EmpWorkerArray[i + 1];
        }
        this->m_EmpNum--;
        // this->rmAll();
        this->saveWorkerData();
    }
    return true;
}
int WorkerManage::workerIsExit(int id)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpWorkerArray[i]->m_Id == id)
        {
            index = i;
        }
    }
    return index;
}
bool WorkerManage::saveWorkerData()
{
    // this->rmAll();
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    int count_flag = 0;
    while (count_flag < this->m_EmpNum)
    {
        ofs << "编号:" << this->m_EmpWorkerArray[count_flag]->m_Id
            << "\t姓名:" << this->m_EmpWorkerArray[count_flag]->m_Name
            << "\t性别:" << ((this->m_EmpWorkerArray[count_flag]->m_Gender == 0) ? "男" : "女")
            << "\t部门:" << this->m_EmpWorkerArray[count_flag]->m_PartId << endl;
        count_flag++;
    }
    ofs.close();
    return true;
}
// 显示所ii有员工信息
bool WorkerManage::shopWorkerData()
{
    if ((this->m_FileIsEmpty))
    {
        cout << "没有员工数据" << endl;
        return false;
    }
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if (!ifs.is_open())
    {
        cout << "没有员工信息 或其他原因。\n";
        return false;
    }
    else
    {
        string buf;
        while (getline(ifs, buf))
        {
            cout << buf << endl;
        }
    }
    ifs.close();
    return true;
}

int WorkerManage::getEmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if (!ifs.is_open())
    {
        ifs.close();
        return 0;
    }
    int num = 0;
    string tmpBuf;

    while (getline(ifs, tmpBuf))
    {
        num++;
    }
    ifs.close();
    return num;
}
// 修改职工信息
void WorkerManage::modifyWorkerData()
{
    if (m_FileIsEmpty)
    {
        cout << "没有员工数据文件，请检查重试\n";
        return;
    }
    else
    {
        cout << "请输入需要修改职工的编号:";
        int modify_id;
        cin >> modify_id;
        int index = workerIsExit(modify_id);
        cout << "输入需要修改员工编号是:" << modify_id << ",\t所在索引为:" << index << "在职总人数:" << this->m_EmpNum << endl;
        if (index > -1)
        {
            cout << "您要修改职工的当前信息是:\n";
            this->m_EmpWorkerArray[index]->shopInfo();

            int new_id;
            string new_name;
            int new_gender;
            int new_partId;
            cout << "请输入员工的新ID:";
            cin >> new_id;
            cout << "请输入员工的新姓名:";
            cin >> new_name;
            cout << "0:男\n1:女\n请输入员工的新性别:";
            cin >> new_gender;
            cout << "1:Boos （暂无岗位）\n2:经理\n3:普通员工\n请输入职工的新岗位:";
            cin >> new_partId;
            Worker *worker = NULL;
            switch (new_partId)
            {
            case 1: // Boos
                /* code */
                ;
                // break;
            case 2: // manager
                /* code */
                worker = new Manager(new_id, new_name, new_gender, new_partId);
                cout << "选择的性别:" << worker->m_Gender << "\t:" << ((worker->m_Gender == 0) ? "男" : "女") << endl;
                break;
            case 3: // employee
                /* code */
                worker = new Employee(new_id, new_name, new_gender, new_partId);
                cout << "选择的性别:" << worker->m_Gender << "\t:" << ((worker->m_Gender == 0) ? "男" : "女") << endl;
                break;
            default:
                break;
            }
            this->m_EmpWorkerArray[index] = NULL;
            this->m_EmpWorkerArray[index] = worker;
            // this->rmAll();
            this->saveWorkerData();
            // delete worker;
            cout << "修改成功\n";
        }
        else
        {
            cout << "输入需要修改职工的编号不存在。\n";
        }
    }
}

// 建立主键--员工编号，不能重复添加
// 返回true说明主键存在，返回false说明主键不存在，可以添加
bool WorkerManage::idIsExit(int new_id)
{

    if (m_FileIsEmpty)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < this->getEmpNum(); i++)
        {

            if (new_id == this->m_EmpWorkerArray[i]->m_Id)
                return true;
        }
        cout << "没有员工信息文件asdasdadad\n";
    }
    // cout << "没有员工信息文件asdasdadad\n";
    return false;
}

bool WorkerManage::refreshWorkerData()
{
    if (m_FileIsEmpty)
    {
        cout << "没有员工信息文件\n";
        return false;
    }
    this->saveWorkerData();
    return true;
}
// 查找职工信息
bool WorkerManage::selectWorkerData()
{
    if (m_FileIsEmpty)
    {
        cout << "没有员工信息文件\n";
        return false;
    }
    cout << "请输入需要查找的职工编号:";
    int modify_id;
    cin >> modify_id;
    int index = workerIsExit(modify_id);
    if (index == -1)
    {
        cout << "查找编号为" << modify_id << "的职工不存在。\n";
        return false;
    }
    else
    {
        cout << "查找成功！\n";
        this->m_EmpWorkerArray[index]->shopInfo();
        return true;
    }
}

bool WorkerManage::sort_Worker_Id()
{
    if (m_FileIsEmpty)
    {
        cout << "没有员工信息文件\n";
        return false;
    }
    int count = 0;
    for (int i = 0; i < this->m_EmpNum - 1; i++)
    {
        int min_index;
        min_index = i;
        for (int j = i + 1; j < this->m_EmpNum; j++)
        {
            if (this->m_EmpWorkerArray[j]->m_Id < this->m_EmpWorkerArray[min_index]->m_Id)
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            Worker *temp = this->m_EmpWorkerArray[i];
            this->m_EmpWorkerArray[i] = this->m_EmpWorkerArray[min_index];
            this->m_EmpWorkerArray[min_index] = temp;
            // delete temp;
        }
    }
    this->saveWorkerData();
    return true;
}