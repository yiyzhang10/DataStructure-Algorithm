#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int a, b;
    int n;
    cin >> n;
    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int max3 = INT_MIN;
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    int num;
    while (n--) { // 注意 while 处理多个 case
        cin >> num;
        if(num >= max1){
            max3 = max2;
            max2 = max1;
            max1 = num;
        }
        else{
            if(num >= max2){
                max3 = max2;
                max2 = num;
            }
            else{
                if(num >= max3){
                    max3 = num;
                }
            }
        }
        if(num <= min1){
            min2 = min1;
            min1 = num;
        }
        else{
            if(num <= min2)
            min2 = num;
        }
    }
    int result1 = max1 * max2 * max3;
    int result2 = min1 * min2 * max1;
    cout << (result1 > result2 ? result1 : result2);
    return 0;
}
// 64 位输出请用 printf("%lld")