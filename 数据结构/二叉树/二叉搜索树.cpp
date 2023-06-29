#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

// 定义二叉搜索树节点结构体
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:

    TreeNode* root;

    // 构造函数
    BinarySearchTree() : root(nullptr) {}

    // 插入操作
    void insert(int val) {
        if (!root) {  // 如果根节点为空，直接插入
            root = new TreeNode(val);
            return;
        }
        TreeNode* cur = root;
        while (cur) {
            if (val < cur->val) {  // 如果值小于当前节点值，往左子树走
                if (!cur->left) {
                    cur->left = new TreeNode(val);
                    return;
                }
                cur = cur->left;
            }
            else if (val > cur->val) {  // 如果值大于当前节点值，往右子树走
                if (!cur->right) {
                    cur->right = new TreeNode(val);
                    return;
                }
                cur = cur->right;
            }
            else {  // 如果值等于当前节点值，直接返回
                return;
            }
        }
    }

    // 判断操作
    bool contains(int val) {
        TreeNode* cur = root;
        while (cur) {
            if (val < cur->val) {  // 如果值小于当前节点值，往左子树走
                cur = cur->left;
            }
            else if (val > cur->val) {  // 如果值大于当前节点值，往右子树走
                cur = cur->right;
            }
            else {  // 如果值等于当前节点值，返回true
                return true;
            }
        }
        return false;  // 如果找到叶子节点都没找到，则返回false
    }
   
    // 中序遍历
    void inorderTraversal(vector<int> &res, TreeNode* root) {
        if (!root) {
            return;
        }
        inorderTraversal(res, root->left);
        res.push_back(root->val);
        inorderTraversal(res, root->right);
    }

    // 辅助函数：找到当前节点的后继节点
    TreeNode* findSuccessor(TreeNode* node) {
        TreeNode* cur = node->right;
        while (cur && cur->left) {
            cur = cur->left;
        }
        return cur;
    }

    // 辅助函数：递归删除节点
    TreeNode* remove(TreeNode* node, int val) {
        if (!node) {  // 如果节点为空，返回空指针
            return nullptr;
        }
        if (val < node->val) {  // 如果值小于当前节点值，往左子树走
            node->left = remove(node->left, val);
        }
        else if (val > node->val) {  // 如果值大于当前节点值，往右子树走
            node->right = remove(node->right, val);
        }
        else {  // 如果值等于当前节点值，删除当前节点
            if (!node->left) {  // 如果左子树为空，返回右子树
                return node->right;
            }
            if (!node->right) {  // 如果右子树为空，返回左子树
                return node->left;
            }
            // 如果左右子树都存在，找到当前节点的后继节点
            TreeNode* successor = findSuccessor(node);
            node->val = successor->val; // 将后继节点的值赋给当前节点
            node->right = remove(node->right, successor->val); // 递归删除后继节点
        }
        return node;
    }

    // 获取满二叉树的深度
    int getDepth(TreeNode* root) {
        int depth = 0;
        while (root) {
            depth++;
            root = root->left;
        }
        return depth;
    }

    
};


bool isBST(vector<string>& arr, int root, int minVal, int maxVal) {
    // 如果当前节点是空节点，它一定是二叉搜索树
    if (root >= arr.size() || arr[root] == "null") {
        return true;
    }
    // 将节点的值从字符串转换为整数
    int val = stoi(arr[root]);
    // 检查节点的值是否在 minVal 和 maxVal 的范围内
    if (val <= minVal || val >= maxVal) {
        return false;
    }
    // 判断左右子树是否都为二叉搜索树
    return isBST(arr, 2 * root + 1, minVal, val) && isBST(arr, 2 * root + 2, val, maxVal);
}

int main() {
    //输入数组，首先直接判断数组表示的是否为二叉搜索树
    vector<string> arr = { "5", "1", "4", "null", "null", "3", "6" };
    cout << "打印输入的数组：" << endl;
    for (string s : arr) {
        cout << s << " ";
    }
    cout << endl << endl;
    if (isBST(arr, 0, INT_MIN, INT_MAX)) {
        cout << "经过判断，所给数组是一个二叉搜索树" << endl;
    }
    else {
        cout << "经过判断，所给数组不是一个二叉搜索树" << endl;
    }

    //根据输入数组构建二叉搜索树
    cout << "根据所给数组构建二叉搜索树" << endl;
    BinarySearchTree bst;
    for (int i = 0; i < arr.size(); i++)
    {
        if(arr[i] != "null")
        bst.insert(stoi(arr[i]));
    }
    cout << "构建成功" << endl << endl;
    cout << endl << "打印二叉搜索树的中序遍历" << endl;
    vector<int> ino;
    bst.inorderTraversal(ino, bst.root);
    for (int s : ino) {
        cout << s << " ";
    }
    cout << endl << endl;
    while (1) {
        cout << "输入数字选择你要进行的操作：" << endl;
        cout << "1：查询" << endl;
        cout << "2：删除" << endl;
        cout << "3：插入" << endl;
        int number;
        cin >> number;
        switch (number) {
        case 1:
            //判断数字是否在二叉搜索树中
            cout << endl<< "输入数字查询其是否在二叉搜索树中(输入-1跳出)：" << endl;
            while (1) {
                int number;
                cin >> number;
                if (number == -1)
                    break;
                if (bst.contains(number))
                    cout << number << "在二叉搜索树中" << endl; // 输出1
                else
                    cout << number << "不在二叉搜索树中" << endl;
            }
            break;
        case 2:
            //删除元素，如果查找到进行删除，未查找到报未查找到信息
            cout << endl << "输入数字在二叉搜索树中查找并删除(输入-1跳出)：" << endl;
            while (1) {
                int number;
                cin >> number;
                if (number == -1)
                    break;
                if (bst.contains(number)) {
                    bst.remove(bst.root, number);
                    cout << number << "在二叉搜索树中，删除成功" << endl;
                    //经过以上处理后，新的二叉排序树中序遍历显然应当为递增，进行测试
                    cout << endl << "打印删除后二叉搜索树的中序遍历" << endl;
                    vector<int> ino;
                    bst.inorderTraversal(ino, bst.root);
                    for (int s : ino) {
                        cout << s << " ";
                    }
                    cout << endl << endl;
                }
                else
                {
                    cout << number << "不在二叉搜索树中，无法删除" << endl;
                }
            }
            break;
        case 3:
            //将元素插入二叉搜索树中
            cout << endl << "输入数字插入二叉搜索树中(输入-1跳出)：" << endl;
            while (1) {
                int number;
                cin >> number;
                if (number == -1)
                    break;
                bst.insert(number);
                cout << "插入成功" << endl;
                //经过以上处理后，新的二叉排序树中序遍历显然应当为递增，进行测试
                cout << endl << "打印插入后二叉搜索树的中序遍历" << endl;
                vector<int> ino;
                bst.inorderTraversal(ino, bst.root);
                for (int s : ino) {
                    cout << s << " ";
                }
                cout << endl << endl;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}