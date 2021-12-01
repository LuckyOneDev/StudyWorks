// Первый драфт. Дерево балансируется по ASCII коду вставляемого значения. Функции вроде работают

#include <iostream>
#include <windows.h>

struct Node {
    Node(char val) {
        value = val;
    }
    char value;
    Node* l = nullptr;
    Node* r = nullptr;
};

bool isVowel(char c) {
    return c == 'а' || c == 'у' || c == 'о' || c == 'е' || c == 'и' ||
        c == 'я' || c == 'ю' || c == 'ё' || c == 'э' || c == 'ы' ||
        c == 'А' || c == 'У' || c == 'О' || c == 'Е' || c == 'И' ||
        c == 'Я' || c == 'Ю' || c == 'Ё' || c == 'Э' || c == 'Ы';
}

Node* insert(Node* root, char val)
{
    if (root == nullptr) return new Node(val);
    if ((int)root->value > (int)val)
        root->l = insert(root->l, val);
    else
        root->r = insert(root->r, val);
    return root;
}

Node* search(Node* node, char k) {
    if (!node) return 0; // пустое дерево
    if (k == node->value)
        return node;
    if (k < node->value)
        return search(node->l, k);
    else
        return search(node->r, k);
}

void print_tree(Node* root, int depth = 0) {
    depth++;
    std::cout << depth << " : '" << root->value << "' : " << root << std::endl;
    if (root->l != nullptr) print_tree(root->l, depth);
    if (root->r != nullptr) print_tree(root->r, depth);
}

void get_height(Node* root, int& height) {
    height++;
    int bufl = height;
    int bufr = height;
    if (root->l != nullptr) {
        get_height(root->l, bufl);
        height = bufl;
    }
    if (root->r != nullptr) {
        get_height(root->r, bufr);
        height = bufr;
    }
}

void node_count(Node* root, int& count) {
    count++;
    if (root->l != nullptr) node_count(root->l, count);
    if (root->r != nullptr) node_count(root->r, count);
}

void vowel_count(Node* root, int& count) {
    if (isVowel(root->value)) count++;

    if (root->l != nullptr) vowel_count(root->l, count);
    if (root->r != nullptr) vowel_count(root->r, count);
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Node* root = nullptr;

    while (true)
    {
        std::cout << "\n0) Выйти из программы\n";
        std::cout << "1) Вставить новое значение\n";
        std::cout << "2) Поиск значения\n";
        std::cout << "3) Вывести дерево\n";
        std::cout << "4) Рассчитать высоту\n";
        std::cout << "5) Количество элементов\n";
        std::cout << "6) Количество гласных\n";
        int input;
        char val;
        int buf;
        std::cin >> input;

        switch (input) {
        case 0:
            return 0;
        case 1:
            std::cin >> val;
            insert(root, val);
            std::cout << "\nВставлено новое значение\n";
            break;
        case 2:
            std::cin >> val;
            std::cout << "\nАдрес значения: " << search(root, val) << std::endl;
            break;
        case 3:
            std::cout << "\nДерево:\n";
            print_tree(root);
            break;
        case 4:
            buf = 0;
            get_height(root, buf);
            std::cout << "\nВысота дерева: " << buf << std::endl;
            break;
        case 5:
            buf = 0;
            node_count(root, buf);
            std::cout << "\nКоличество листьев: " << buf << std::endl;
            break;
        case 6:
            buf = 0;
            vowel_count(root, buf);
            std::cout << "\nКоличество гласных: " << buf << std::endl;
            break;
        }

    }
}