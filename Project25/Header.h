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

// додає книгу-журнал-газету
void addItem(Item*& library, size_t& size, Item item);
string getType(Type type);
//функція заповнення
void fillLibrary(Item*& library, size_t& size, const size_t& count);
// редагування
void editItem(Item& item);
// видаляє
void deleteItem(Item*& library, size_t& size, const size_t& index);
// виводить
void print(Item item);
// зчитує
void read(Item*& library, size_t& size);
//зберігає
void save(Item*& library, size_t& size);
//сортує
void sortLibrary(Item*& library, size_t size);
//пошук книги
void searchBook(Item* library, size_t size);
//пошук жургналу
void searchMagazine(Item* library, size_t size);
// відсортовує за автором
void filterByAuthor(Item* library, size_t size);
//відсортовує за жанром
void filterByGenre(Item* library, size_t size);
// відсортовує журнали певного року
void filterMagazinesByYear(Item* library, size_t size);
//перераховує книги за жанром
void countBooksByGenre(Item* library, size_t size);
//видаляє газети певного року
void deleteNewspapersByYear(Item*& library, size_t& size);

