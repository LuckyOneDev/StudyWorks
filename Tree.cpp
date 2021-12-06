/*
абвгдеёжзийклмнуфхцчшщъыьэюя
1 а
1 ж
1 в
1 г
1 б
1 к
1 и
1 ш
2 и
3
4
5
6
height = 3
vowels = 2
size = 8
   а
    \
     ж
   /   \
  в     к
 / \   / \
б   г и   ш
*/

#include <iostream>
#include <windows.h>
#include <algorithm>
#undef max

// Узел бинарного дерева
// Содержит значение и 2 потомка
struct Node {
  Node(char val) {
    value = val;
  }
  char value;
  Node* l = nullptr;
  Node* r = nullptr;
};

//Проверяет является ли символ гласной русского языка
bool isVowel(char c) {
  return std::string("ауоеияюёэыАУОЕИЯЮЁЭЫ").find(c) != std::string::npos;
}

//Вставляет новое значение в дерево
//root - корень дерева
//val - значение
Node* insert(Node* root, char val)
{
  //Если дерево пустое, создаём его
  if (root == nullptr) return new Node(val);

  //Если больше вставляем справа, меньше - слева
  if (root->value > val)
    root->l = insert(root->l, val);
  else
    root->r = insert(root->r, val);
  return root;
}

//Ищет значение в дереве.
//root - корень дерева
//k - значение
//Возвращает указатель на найденное значение
Node* search(Node* node, char k) {
  if (!node) return 0; // пустое дерево
  if (k == node->value)
    return node;
  if (k < node->value)
    return search(node->l, k);
  return search(node->r, k);
}

//Выводит дерево на печать
//root - корень дерева
void print_tree(Node* root, int depth = 0) {
  //Если узла не существует, завершаем
  if (!root) return;
  std::cout << depth << " : '" << root->value << "' : " << root << std::endl;
  //Увеличиваем глубину
  depth++;
  //Выводим левого и правого потомка
  print_tree(root->l, depth);
  print_tree(root->r, depth);
}

//Возвращает высоту дерева
int get_height(Node* root) {
  //Если узла не существует, завершаем
  if (!root) return 0;
  return std::max(get_height(root->l), get_height(root->r)) + 1;
}

//Возвращает количество узлов
int node_count(Node* root) {
  //Если узла не существует, завершаем
  if (!root) return 0;
  return node_count(root->l) + node_count(root->r) + 1;
}

//Возвращает количество гласных
int vowel_count(Node* root) {
  //Если узла не существует, завершаем
  if (!root) return 0;
  return vowel_count(root->l) + vowel_count(root->r) + isVowel(root->value);
}
int main()
{
  //Устанавливаем русский язык
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  //Создание переменной под дерево
  Node* root = nullptr;

  //Цикл ввода
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
      std::cout << "\nВысота дерева: " << get_height(root) - 1 << std::endl;
      break;
    case 5:
      std::cout << "\nКоличество узлов: " << node_count(root) << std::endl;
      break;
    case 6:
      std::cout << "\nКоличество гласных: " << vowel_count(root) << std::endl;
      break;
    }
  }
}
