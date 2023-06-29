#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
int main()
{
    int n;
    cout << "请输入任务个数" << endl;
    cin >> n;
    // 任务序号
    vector<int> number(n, 0);
    // 任务截止时间
    vector<int> d(n, 0);
    // 任务代价
    vector<int> w(n, 0);
    // 任务完成的位置
    vector<int> done(n, 0);
    long result = 0;
    // 任务序号
    for (int i = 0; i < n; i++)
    {
        number[i] = i + 1;
    }
    // 任务的截止时间
    cout << "请输入每个任务的截止时间" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> d[i];
    }
    // 任务的惩罚
    cout << "请输入每个任务的惩罚" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> w[i];
    }
    // 按惩罚从大到小排序,使得惩罚大的任务更先运行
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (w[j] < w[j + 1])
            {
                swap(number[j], number[j + 1]);
                swap(d[j], d[j + 1]);
                swap(w[j], w[j + 1]);
            }
        }
    }
    cout << "任务按照惩罚代价从大到小排序：" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "任务" << number[i] << ",截止时间为" << d[i] << ",惩罚代价为" << w[i] << endl;
    }

    cout << endl <<"任务调度：" << endl;
    // 主程序
    for (int i = 0; i < n; i++)
    {
        // flag标记当前任务是否超时
        bool flag = false;
        // time表示任务如果能够运行，最终的运行时间
        int time = d[i];
        // 从任务的截止时间从后往前遍历，若没有任务在运行，则可以占据位置运行
        for (time; time > 0; time--)
        {
            // 任务按照惩罚权值递减排序的，所以先加入到done中的任务都是惩罚权值较大的任务
            if (!done[time - 1])
            {
                done[time - 1] = true;
                flag = true;
                break;
            }
        }
        // flag==true,任务得到运行
        if (flag)
        {
            cout << "在时间" << time - 1 << "到时间" << time << "运行任务" << number[i] << endl;
        }
        // flag==true,任务被放弃
        if (!flag)
        {
            cout << "放弃任务" << number[i] << ",其截止时间为" << d[i] << ",超时代价为" << w[i] << endl;
            result += w[i];
        }
    }
    cout << "总的放弃的任务超时代价为" << result << endl;
    return 0;
}
