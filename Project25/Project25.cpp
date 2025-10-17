#include <iostream>
#include "Header.h"
using namespace std;

int main()
{
    Item* library = nullptr;
    size_t size = 0;
    read(library, size);

    int choice;
    while (true) {
        cout << R"(
==================== LIBRARY MENU ====================
1 - Fill database
2 - Show all
3 - Add item
4 - Delete item
5 - Sort by type & title
6 - Search book (by author & title)
7 - Search magazine (by title)
8 - Filter: books by author
9 - Filter: books by genre
10 - Filter: magazines by year
11 - Count: books by genre
12 - Delete newspapers by year
0 - Exit
======================================================
Enter your choice :: )";

        cin >> choice;
        if (choice == 0)
            break;

        switch (choice)
        {
        case 1: {
            int count;
            cout << "Enter number of items: ";
            cin >> count;
            fillLibrary(library, size, count);
            save(library, size);
            break;
        }
        case 2:
            for (size_t i = 0; i < size; i++)
                print(library[i]);
            break;
        case 3: {
            Item tmp;
            editItem(tmp);
            addItem(library, size, tmp);
            save(library, size);
            break;
        }
        case 4: {
            size_t index;
            cout << "Enter index to delete (0-" << size - 1 << "): ";
            cin >> index;
            if (index < size)
                deleteItem(library, size, index);
            save(library, size);
            break;
        }
        case 5:
            sortLibrary(library, size);
            save(library, size);
            break;
        case 6:
            searchBook(library, size);
            break;
        case 7:
            searchMagazine(library, size);
            break;
        case 8:
            filterByAuthor(library, size);
            break;
        case 9:
            filterByGenre(library, size);
            break;
        case 10:
            filterMagazinesByYear(library, size);
            break;
        case 11:
            countBooksByGenre(library, size);
            break;
        case 12:
            deleteNewspapersByYear(library, size);
            save(library, size);
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }

    delete[] library;

}



