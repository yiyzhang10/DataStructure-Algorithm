/* 算法第二次实验：计数排序
* 2023.03.30
* 张祎阳 */

#include <iostream>
#include <vector>
using namespace std;

void countingsort(vector<int>& arr, vector<int>& sort_arr, int min, int max) {
	// 若数组长度小于等于1，可以不用排序，直接返回
	int len = arr.size();
	if (len <= 1)
		return;	
	// 根据待排序集合中最大元素和最小元素的差值范围，申请额外空间
	// 本题中最大值99，最小值90，可知计数数组长度应为10，count[0]为90的计数，count[9]为99的计数
	vector<int> count(max - min + 1, 0);
	cout << "根据待排序集合中最大元素和最小元素的差值范围，最大值为" << max << "，最小值为" << min << "，申请额外空间大小为" << max - min + 1 << endl;
	// 遍历待排序集合，将每一个元素出现的次数记录到元素值对应的额外空间内
	for (int x : arr)
		count[x - min]++;
	cout << "从" << min << "到" << max << "的计数统计" << endl;
	for (int x : count)
		cout << x << " ";
	cout << endl;
	// 对额外空间内数据进行计算，得出每一个元素的正确位置
	for (int i = 1; i < max - min + 1; i++)
		count[i] += count[i - 1];
	// 将待排序集合每一个元素移动到计算出的正确位置上
	for (int i = 0; i < len; i++) {
		sort_arr[count[arr[i] - min] - 1] = arr[i];
		count[arr[i] - min]--;
	}
}

int main()
{
	// 使用vector容器定义数组
	vector<int> arr = {95, 94, 91, 98, 99, 90, 99, 93, 91, 92};
	cout << "排序前数组：" << endl;
	for (int x : arr)
		cout << x << " ";
	cout << endl;
	vector<int> sorted_arr(arr.size(), 0);
	// 找到数组中的最大值与最小值
	int max = INT_MIN;
	int min = INT_MAX;
	for (int x : arr) {
		if (x > max)
			max = x;
	}
	for (int x : arr) {
		if (x < min)
			min = x;
	}
	// 传入原始数组，全为0的新数组以及最大最小值
	countingsort(arr, sorted_arr, min, max);
	// 输出排序后的数组
	cout << "排序后数组：" << endl;
	for (int x : sorted_arr)
		cout << x << " ";
	cout << endl;
	return 0;
}
