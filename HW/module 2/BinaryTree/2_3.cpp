// Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N. 
// Требуется построить бинарное дерево, заданное наивным порядком вставки. 
// Т.е., при добавлении очередного числа K в дерево с корнем root, 
// если root→Key ≤ K, то узел K добавляется в правое поддерево root;
//  иначе в левое поддерево root. Выведите элементы в порядке post-order (снизу вверх).

// Рекурсия запрещена.



#include <vector>
#include <sstream>
#include <cassert>
#include <iostream>
#include <queue>
#include <stack>

class IntCmp {
public:
    bool operator()(int l, int r) {
        return l < r;
    }
};

template <typename T, typename Compare>
class BinaryTree {
public:
    BinaryTree(const Compare& _cmp) : root(nullptr), cmp(_cmp) {}
    ~BinaryTree();

    void add(const T& key);
    void traverseDfs(void (*visit)(const T& key));

private:
    struct Node {
        T key;
        Node* left;
        Node* right;
        Node(const T& _key) : key(_key), left(nullptr), right(nullptr) {}
    };

    Node* root;
    Compare cmp;
};


template <typename T, typename Compare>
void BinaryTree<T, Compare>::traverseDfs(void (*visit)(const T& key)) {

    if (root == nullptr) {
        return;
    }

    std::stack<Node*> st1;
    std::stack<Node*> st2;

    Node* node = root;
    st1.push(node);

    while (!st1.empty()) {
        node = st1.top();
        st1.pop();
        st2.push(node);

        if (node->left != nullptr) {
            st1.push(node->left);
        }

        if (node->right != nullptr) {
            st1.push(node->right);
        }
    }

    while (!st2.empty()) {
        node = st2.top();
        st2.pop();
        visit(node->key);
    }
}


template <typename T, typename Compare>
BinaryTree<T, Compare>::~BinaryTree() {

    if (root == nullptr) {
        return;
    }
    std::queue<Node*> q;

    q.push(root);
    q.push(nullptr);
    while (!q.empty()) {

        // delete node
        for (Node* node = q.front(); node != nullptr; node = q.front()) {
            if (node->left != nullptr || node->right != nullptr) {
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                
                if (node->right != nullptr) {
                    q.push(node->right);
                }

                q.push(nullptr);
            }

            delete node;
            q.pop();
        }
        q.pop();
    }
}

template <typename T, typename Compare>
void BinaryTree<T, Compare>::add(const T& key) {
    if (root == nullptr) {
        root = new Node(key);
        return;
    }

    Node* node = root;

    while (node != nullptr) {
        if (cmp(key, node->key)) {

            if (node->left == nullptr) {
                node->left = new Node(key);
                return;
            }

            node = node->left;
        } else {

            if (node->right == nullptr) {
                node->right = new Node(key);
                return;
            }

            node = node->right;
        }
    }
    node = new Node(key);
}


template<typename T>
void print(const T& key) {
    std::cout << key << " ";
}

int run(std::istream& input, std::ostream& output) {
    int n;
    input >> n;
    int key;
    IntCmp cmp;
    BinaryTree<int, IntCmp> tree(cmp);

    for (size_t i = 0; i < n; ++i) {
        input >> key;
        tree.add(key);
    }

    tree.traverseDfs([](const int& key) { std::cout << key << " "; });
    // tree.traverseDfs([](const int& key) { print<int>(key); });

    return 0;
}

void testHashTable() {
    // {
    //     std::stringstream input;
    //     std::stringstream output;
    //     input << "10 7 2 10 8 5 3 6 4 1 9";
    //     run(input, output);
    //     assert(output.str() == "1 4 3 6 5 2 9 8 10 7 ");
    // }
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 7 10 2 6 1 9 4 5 8 3";
        run(input, output);
        assert(output.str() == "1 3 5 4 6 2 8 9 10 7 ");
    }
    // {
    //     std::stringstream input;
    //     std::stringstream output;
    //     input << "10 4 3 9 5 6 8 7 2 10 1";
    //     run(input, output);
    //     assert(output.str() == "1 2 3 7 8 6 5 10 9 4 ");
    // }
}

int main() {
    run(std::cin, std::cout);
    // testBinaryTree();

    return 0;
}