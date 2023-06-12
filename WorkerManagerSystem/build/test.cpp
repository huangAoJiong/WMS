#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void sort_arr(int *arr, int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < N; j++)
        {
            if (arr[min_index] > arr[j])
            {
                min_index = j;
            }
        }
        if (i != min_index)
        {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}
void print_arr(const int (&arr)[], int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;
}
int main()
{
    // ifstream ifs;
    // ifs.open("worker.txt", ios::in);
    // string *buf = new string[5];
    // int id;

    // ifs >> buf[0]; //&&ifs >> name;
    // cout << buf[0] << endl;
    // id = stoi(buf[0].substr(buf[0].find("：") + 3));
    // cout << id << endl;
    // ifs.close();
    int arr1[] = {2, 4, 3, 6, 1, 8, 2};
    int len = sizeof(arr1) / sizeof(int);
    print_arr(arr1, len);
    sort_arr(arr1, len);
    print_arr(arr1, len);

    return 0;
}