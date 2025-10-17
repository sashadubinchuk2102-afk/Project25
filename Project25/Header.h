#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum Type
{
    BOOK = 1, NEWSPAPER, MAGAZINE
};

const size_t SIZE = 50;
const string path = "library.dat";

struct Item
{
    Type type;
    char name[SIZE]{};
    size_t year;
    char author[SIZE]{ '\0' };
    char genre[SIZE]{ '\0' };
};

// ���� �����-������-������
void addItem(Item*& library, size_t& size, Item item);
string getType(Type type);
//������� ����������
void fillLibrary(Item*& library, size_t& size, const size_t& count);
// �����������
void editItem(Item& item);
// �������
void deleteItem(Item*& library, size_t& size, const size_t& index);
// ��������
void print(Item item);
// �����
void read(Item*& library, size_t& size);
//������
void save(Item*& library, size_t& size);
//�����
void sortLibrary(Item*& library, size_t size);
//����� �����
void searchBook(Item* library, size_t size);
//����� ��������
void searchMagazine(Item* library, size_t size);
// ��������� �� �������
void filterByAuthor(Item* library, size_t size);
//��������� �� ������
void filterByGenre(Item* library, size_t size);
// ��������� ������� ������� ����
void filterMagazinesByYear(Item* library, size_t size);
//���������� ����� �� ������
void countBooksByGenre(Item* library, size_t size);
//������� ������ ������� ����
void deleteNewspapersByYear(Item*& library, size_t& size);

