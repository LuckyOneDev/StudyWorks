// Первый драфт. Дерево балансируется по ASCII коду вставляемого значения. Функции вроде работают
/*
1 a
1 h
1 c
1 d 
1 e
1 l
1 f
1 z

2 e

3

4
5
6

height = 3
vowels = 2
size = 8

   a
    \
     h
   /   \
  c     l
 / \   / \
d   e f   z 
*/


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
  return std::string("aeiouAEIOUауоеияюёэыАУОЕИЯЮЁЭЫ").find(c) != std::string::npos;
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
      root = insert(root, val);
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
      buf = -1;
      get_height(root, buf);
      std::cout << "\nВысота дерева: " << buf << std::endl;
      break;
    case 5:
      buf = 0;
      node_count(root, buf);
      std::cout << "\nКоличество узлов: " << buf << std::endl;
      break;
    case 6:
      buf = 0;
      vowel_count(root, buf);
      std::cout << "\nКоличество гласных: " << buf << std::endl;
      break;
    }
  }
}