/* 算法第二次实验：快速排序
* 2023.03.30
* 张祎阳 */

#include <iostream>
#include <vector>
using namespace std;

int Paritition(vector<int>& arr, int low, int high) {
    // 传进来的部分的第一个数作为本轮基准数字
    int pivot = arr[low];
    // 快速排序核心过程：交换。对传进来的部分进行排序
    while (low < high) {
        while (low < high && arr[high] >= pivot)
            --high;
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivot)
            ++low;
        arr[high] = arr[low];
    }
    // 最终填入基准数字并返回其位置
    arr[low] = pivot;
    return low;
}

void QuickSort(vector<int>& arr, int low, int high)
{
    // 如果递归进来的部分只有一个数或零个数，不用继续划分排序，直接返回
    if (low >= high)
        return;
    // 进行排序，并得到本轮的基准数字排序后的位置
    int position = Paritition(arr, low, high);
    cout << "本轮基准为：" << arr[position] << "  ";
    cout << "本轮排序后数组：";
    for (int x : arr)
        cout << x << " ";
    cout << endl;
    // 根据本轮基准数字排序后的位置，对两侧的部分分别进行排序
    QuickSort(arr, low, position - 1);
    QuickSort(arr, position + 1, high);
}

int main() {
    // 使用vector容器定义数组
    vector<int> arr = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    cout << "排序前数组：" << endl;
    for (int x : arr)
        cout << x << " ";
    cout << endl;
    // 进行快速排序
    QuickSort(arr, 0, arr.size() - 1);
    // 输出排序后的数组
    cout << "排序后数组：" << endl;
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}