#ifndef __EMPLOYEE_H_
#define __EMPLOYEE_H_

#include <iostream>
#include <string>
#include "worker.h"
using namespace std;

class Employee : public Worker
{
public:
    Employee(int, string, int, int);
    void shopInfo();
    string getPartName();
};

#endif