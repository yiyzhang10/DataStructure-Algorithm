#include <iostream>
#include <vector>
using namespace std;

// 定义颜色常量
enum Color { RED, BLACK };

// 定义节点结构体
struct Node {
    int value;      // 节点存储的值
    Color color;    // 节点颜色，RED表示红色，BLACK表示黑色
    Node* left, * right, * parent;    // 左右子节点和父节点指针
    Node(int val) {        // 节点构造函数
        value = val;
        color = RED;       // 初始颜色为红色
        left = right = parent = NULL;   // 子节点和父节点指针初始为NULL
    }
};

// 定义红黑树类
class RedBlackTree {
private:
    Node* root;    // 根节点指针

    // 左旋操作函数
    void leftRotate(Node* x) {
        Node* y = x->right;           // 记录x的右子节点
        x->right = y->left;           // 将y的左子节点链接到x的右子节点
        if (y->left != NULL)
            y->left->parent = x;      // 将y的左子节点的父节点设为x
        y->parent = x->parent;        // 将y的父节点设为x的父节点
        if (x->parent == NULL)
            root = y;                 // 如果x为根节点，将y设为新的根节点
        else if (x == x->parent->left)
            x->parent->left = y;      // 如果x为父节点的左子节点，将y设为父节点的左子节点
        else
            x->parent->right = y;     // 如果x为父节点的右子节点，将y设为父节点的右子节点
        y->left = x;                  // 将x设为y的左子节点
        x->parent = y;                // 将y设为x的父节点
    }

    // 右旋操作函数
    void rightRotate(Node* y) {
        Node* x = y->left;            // 记录y的左子节点
        y->left = x->right;           // 将x的右子节点链接到y的左子节点
        if (x->right != NULL)
            x->right->parent = y;     // 将x的右子节点的父节点设为y
        x->parent = y->parent;        // 将x的父节点设为y的父节点
        if (y->parent == NULL)
            root = x;                 // 如果y为根节点，将x设为新的根节点
        else if (y == y->parent->left)
            y->parent->left = x;      // 如果y为父节点的左子节点，将x设为父节点的左子节点
        else
            y->parent->right = x;     // 如果y为父节点的右子节点，将x设为父节点的右子节点
        x->right = y; // 将y设为x的右子节点
        y->parent = x; // 将x设为y的父节点
    }

    // 插入节点操作函数
    void insertNode(Node* z) {
        Node* y = NULL;
        Node* x = root;
        while (x != NULL) {            // 查找插入位置
            y = x;
            if (z->value < x->value)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == NULL)
            root = z;                  // 如果树为空，将z设为根节点
        else if (z->value < y->value)
            y->left = z;
        else
            y->right = z;
        z->left = NULL;
        z->right = NULL;
        z->color = RED;                // 新节点初始颜色为红色
        insertFixup(z);                // 调整红黑树
    }

    // 插入调整红黑树函数
    void insertFixup(Node* z) {
        // 父节点为红才需要调整，为黑时不需要调整
        while (z->parent != NULL && z->parent->color == RED) {
            // 父节点是祖父节点的左孩子
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                // 叔节点为红，变色即可，父节点变黑，叔节点变黑
                // 祖父节点变红，注意需要递归调整祖父节点
                if (y != NULL && y->color == RED) {     // 1
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent; // 递归调整
                }
                // 叔节点为黑，分情况讨论
                else {
                    // 自身是父节点的右孩子，左旋父节点，父节点变成自身的左孩子转到情况3
                    if (z == z->parent->right) {         // 2
                        z = z->parent;
                        leftRotate(z);
                    }
                    // 此处有两种情形
                    // 1、情况2转来
                    // 2、自身是父节点的左孩子
                    // 父节点变黑，祖父节点变红，再右旋祖父节点
                    z->parent->color = BLACK;            // 3
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            // 父节点是祖父节点的右孩子
            else {
                Node* y = z->parent->parent->left;
                // 叔节点为红，变色即可，父节点变黑，叔节点变黑
                // 祖父节点变红，注意需要递归调整祖父节点
                if (y != NULL && y->color == RED) {     // 1
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;// 递归调整
                }
                // 叔节点为黑，分情况讨论
                else {
                    // 自身是父节点的左孩子，右旋父节点，父节点变成自身的右孩子转到情况3
                    if (z == z->parent->left) {          // 2
                        z = z->parent;
                        rightRotate(z);
                    }
                    // 此处有两种情形
                    // 1、情况2转来
                    // 2、自身是父节点的右孩子
                    // 父节点变黑，祖父节点变红，再左旋祖父节点
                    z->parent->color = BLACK;            // 3
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;                           // 根节点颜色为黑色
    }

    // 删除节点操作函数
    void deleteNode(Node* z) {
        Node* y, * x;
        // 左右孩子有一个为空节点，直接删除自身,让孩子节点代替自己即可
        if (z->left == NULL || z->right == NULL)
            y = z;
        // 左右都非空的情况下，需要找到后继节点，将自己的值更改为后继节点的值后再删除后继节点，后继节点即右子树中最小的值
        else {
            y = z->right;
            while (y->left != NULL)
                y = y->left;
        }
        // y现在是需要被删除的节点，可能是z本身，也可能是后继节点，通过前面可知，y最多有一个孩子，左孩子或者右孩子，让x为其孩子节点
        if (y->left != NULL)
            x = y->left;
        else
            x = y->right;
        // 进行赋值，更改z的节点值为y的值，之后删除y即可
        if (y != z)
            z->value = y->value;
        // 以下为删除y，分情况讨论x是否为空的情形
        // 如果x不为空，则将它和其父节点连接起来
        if (x != NULL) {
            // 首先调整x的父指针
            x->parent = y->parent;
            // Case1：x是新的根
            // 之后进行判断，若y的父节点是空，显然y现在为根，删除y即让x成为根
            if (y->parent == NULL) {
                root = x;
            }
            // y是其父节点左孩子，让父节点左孩子成为x
            else if (y == y->parent->left) {
                y->parent->left = x;
            }
            // y是其父节点右孩子，让父节点右孩子成为x
            else {
                y->parent->right = x;
            }
            // x替代了y，对x进行调整
            if (y->color == BLACK) {
                deleteFixup(x);
            }
            delete y;
        }
        // 替代节点为空，即要删除的节点没有左右孩子
        else {
            if (y->parent == NULL) {
                root = NULL;
            }
            else {
                // x为空，未替代y，对y进行调整
                if (y->color == BLACK) {
                    deleteFixup(y);
                }
                // 调整y的父节点
                if (y == y->parent->left) {
                    y->parent->left = NULL;
                }
                else {
                    y->parent->right = NULL;
                }
            }
            delete y;
        }
    }

    // 删除调整红黑树函数
    void deleteFixup(Node* x) {
        // 需要调整的节点非根节点，且为黑节点，若为根节点或红节点，最后直接染黑即可
        while (x != root && x->color == BLACK) {
            // x是左孩子
            if (x == x->parent->left) {
                // 令w为x的叔节点
                Node* w = x->parent->right;
                // Case2
                // 叔节点为红，交换叔节点与父节点颜色，即叔节点染黑，父节点染红
                // 然后进行左旋，此时经过左旋后叔节点应该为新的节点，且由于之前叔节点为红，新的叔节点一定为黑
                // 注意左旋之后暂未满足性质五，还需要对新的叔节点按照其他情况继续调整
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                // Case3
                // 以下不区分叔节点的来源，确定其一定为黑色
                // 叔节点的子节点均为黑或空，叔节点染红，x指向其父节点，在最后染黑
                if ((w->left == NULL || w->left->color == BLACK) &&
                    (w->right == NULL || w->right->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                }
                // 其他情况，叔节点的子节点存在非空与黑
                else {
                    // Case4
                    // 叔节点右孩子节点为空或者黑，则左孩子一定为红，将左孩子染黑，自身染红，再右旋叔节点
                    // 此时经过右旋后叔节点应该为新的节点，且叔节点一定为黑，右孩子结点一定为红
                    if (w->right == NULL || w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    // Case5
                    // 此时无论有没有执行上面的if语句，可知叔节点一定为黑，其右孩子一定为红
                    // 左旋变色，x变为根节点，在最后染黑
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if(w->right != NULL)
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            // x是右孩子
            else {
                // 令w为x的叔节点
                Node* w = x->parent->left;
                // Case2
                // 叔节点为红，交换叔节点与父节点颜色，即叔节点染黑，父节点染红
                // 然后进行右旋，此时经过右旋后叔节点应该为新的节点，且由于之前叔节点为红，新的叔节点一定为黑
                // 注意右旋之后暂未满足性质五，还需要对新的叔节点按照其他情况继续调整
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                // Case3
                // 以下不区分叔节点的来源，确定其一定为黑色
                // 叔节点的子节点均为黑或空，叔节点染红，x指向其父节点，在最后染黑
                if ((w->left == NULL || w->left->color == BLACK) &&
                    (w->right == NULL || w->right->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                }
                // 其他情况，叔节点的子节点存在非空与黑
                else {
                    // Case4
                    // 叔节点左孩子节点为空或者黑，则右孩子一定为红，将右孩子染黑，自身染红，再左旋叔节点
                    // 此时经过右旋后左节点应该为新的节点，且叔节点一定为黑，左孩子结点一定为红
                    if (w->left == NULL || w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    // Case5
                    // 此时无论有没有执行上面的if语句，可知叔节点一定为黑，其左孩子一定为红
                    // 右旋变色，x变为根节点，在最后染黑
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left != NULL)
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        // x染黑
        x->color = BLACK;
    }

    // 中序遍历实现函数
    void inOrder(Node* node) {
        if (node != NULL) {
            inOrder(node->left);
            if (node->color == RED)
                cout << "red   ";
            else
                cout << "black   ";
            cout << node->value << " ";
            cout << endl;
            inOrder(node->right);
        }
    }

public:
    // 构造函数
    RedBlackTree() {
        root = NULL;
    }
    // 插入节点函数
    void insert(int value) {
        Node* z = new Node(value);
        insertNode(z);
    }

    // 删除节点函数
    void remove(int value) {
        Node* z = searchNode(value);
        if (z != NULL)
            deleteNode(z);
    }

    // 搜索节点函数
    Node* searchNode(int value) {
        Node* node = root;
        while (node != NULL && node->value != value) {
            if (value < node->value)
                node = node->left;
            else
                node = node->right;
        }
        return node;
    }

    // 中序遍历函数
    void inOrderTraversal() {
        inOrder(root);
        cout << endl;
    }
};

int main() {
    RedBlackTree tree;
    vector<int> arr = { 1,5,6,7,8,9,10,11,12,13,14,15 };
    // 插入节点
    cout << "输入数组为：";
    for (int x : arr) {
        cout << x << " ";
        tree.insert(x);
    }
    cout << endl << "根据数组构造红黑树完成" << endl;

    // 中序遍历
    cout << endl << "进行红黑树中序遍历：" << endl;
    tree.inOrderTraversal();
    cout << endl << endl;

    while (1) {
        cout << "输入数字选择你要进行的操作：" << endl;
        cout << "1：查询" << endl;
        cout << "2：删除" << endl;
        cout << "3：插入" << endl;
        int number;
        cin >> number;
        switch (number)
        {
        case 1:
            //判断数字是否在红黑树中
            cout << "输入数字查询其是否在红黑树中(输入-1跳出)：" << endl;
            while (1) {
                int number;
                cin >> number;
                if (number == -1)
                    break;
                Node* node = tree.searchNode(number);
                if (node) {
                    if (node->color == 0)
                        cout << number << "在红黑树中，颜色为红" << endl; // 输出1
                    else
                        cout << number << "在红黑树中，颜色为黑" << endl; // 输出1
                }
                else
                    cout << number << "不在红黑树中" << endl;
                cout << endl;
            }
            break;
        case 2:
            //删除元素，如果查找到进行删除，未查找到报未查找到信息
            cout << endl << "输入数字在红黑树中查找并删除(输入-1跳出)：" << endl;
            while (1) {
                int number;
                cin >> number;
                if (number == -1)
                    break;
                if (tree.searchNode(number)) {
                    tree.remove(number);
                    cout << number << "在红黑树中，删除成功" << endl;
                    cout << "再次进行红黑树中序遍历：" << endl;
                    tree.inOrderTraversal();
                    cout << endl;
                }
                else
                {
                    cout << number << "不在红黑树中，无法删除" << endl;
                    cout << endl;
                }
            }
            break;
        case 3:
            //将元素插入红黑树中
            cout << endl << "输入数字插入红黑树中(输入-1跳出)：" << endl;
            while (1) {
                int number;
                cin >> number;
                if (number == -1)
                    break;
                tree.insert(number);
                cout << "插入成功" << endl;
                cout << "进行红黑树中序遍历：" << endl;
                tree.inOrderTraversal();
                cout << endl;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}

