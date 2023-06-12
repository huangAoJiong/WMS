#ifndef __MANAGER_H_
#define __MANAGER_H_

#include <iostream>
#include <string>
#include "worker.h"
using namespace std;

class Manager : public Worker
{
public:
    Manager(int, string, int, int);
    void shopInfo();
    string getPartName();
};

#endif