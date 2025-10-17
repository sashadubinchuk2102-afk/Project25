#include "Header.h"

void addItem(Item*& library, size_t& size, Item item)
{
    Item* tmp = new Item[size + 1];
    for (size_t i = 0; i < size; i++)
        tmp[i] = library[i];
    tmp[size] = item;
    size++;
    delete[] library;
    library = tmp;
}

string getType(Type type)
{
    switch (type)
    {
    case BOOK: return "Book";
    case NEWSPAPER: return "Newspaper";
    case MAGAZINE: return "Magazine";
    default: return "Unknown";
    }
}

void fillLibrary(Item*& library, size_t& size, const size_t& count)
{
    for (size_t i = 0; i < count; i++)
    {
        Item tmp;
        editItem(tmp);
        addItem(library, size, tmp);
    }
}

void editItem(Item& item)
{
    int type;
    while (true)
    {
        cout << R"(
Select type:
    1 - Book
    2 - Newspaper
    3 - Magazine
Enter :: )";
        cin >> type;
        if (type < 1 || type > 3)
            cout << "Error type. Try again.\n";
        else
            break;
    }
    cin.ignore();

    cout << "Enter name: ";
    cin.getline(item.name, SIZE);
    cout << "Enter year: ";
    cin >> item.year;
    cin.ignore();

    if (type == BOOK)
    {
        item.type = BOOK;
        cout << "Enter author: ";
        cin.getline(item.author, SIZE);
        cout << "Enter genre: ";
        cin.getline(item.genre, SIZE);
    }
    else if (type == NEWSPAPER)
        item.type = NEWSPAPER;
    else
        item.type = MAGAZINE;
}

void deleteItem(Item*& library, size_t& size, const size_t& index)
{
    if (size == 0) return;
    Item* tmp = new Item[size - 1];
    for (size_t i = 0, j = 0; i < size; i++)
    {
        if (i != index)
            tmp[j++] = library[i];
    }
    delete[] library;
    library = tmp;
    size--;
}

void print(Item item)
{
    cout << "================== " << getType(item.type) << " =====================\n";
    cout << "\tTitle  :: " << item.name << endl;
    if (item.type == BOOK)
    {
        cout << "\tAuthor :: " << item.author << endl;
        cout << "\tGenre  :: " << item.genre << endl;
    }
    cout << "\tYear   :: " << item.year << endl;
}

void read(Item*& library, size_t& size)
{
    ifstream file(path, ios::binary);
    if (!file.is_open()) return;
    file.seekg(0, ios::end);
    size = file.tellg() / sizeof(Item);
    file.seekg(0);
    library = new Item[size];
    for (size_t i = 0; i < size; i++)
        file.read((char*)&library[i], sizeof(Item));
    file.close();
}

void save(Item*& library, size_t& size)
{
    ofstream file(path, ios::binary);
    if (!file.is_open()) return;
    for (size_t i = 0; i < size; i++)
        file.write((char*)&library[i], sizeof(Item));
    file.close();
}

// ----------------- ÄÎÄÀÒÊÎÂ² ÔÓÍÊÖ²¯ ------------------

void sortLibrary(Item*& library, size_t size)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if (library[j].type > library[j + 1].type ||
                (library[j].type == library[j + 1].type &&
                    strcmp(library[j].name, library[j + 1].name) > 0))
            {
                Item tmp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = tmp;
            }
        }
    }
    cout << "Sorted successfully.\n";
}

void searchBook(Item* library, size_t size)
{
    char author[SIZE], name[SIZE];
    cout << "Enter author: ";
    cin.ignore();
    cin.getline(author, SIZE);
    cout << "Enter book title: ";
    cin.getline(name, SIZE);
    bool found = false;
    for (size_t i = 0; i < size; i++)
    {
        if (library[i].type == BOOK &&
            strcmp(library[i].author, author) == 0 &&
            strcmp(library[i].name, name) == 0)
        {
            print(library[i]);
            found = true;
        }
    }
    if (!found) cout << "Book not found.\n";
}

void searchMagazine(Item* library, size_t size)
{
    char name[SIZE];
    cout << "Enter magazine name: ";
    cin.ignore();
    cin.getline(name, SIZE);
    bool found = false;
    for (size_t i = 0; i < size; i++)
    {
        if (library[i].type == MAGAZINE && strcmp(library[i].name, name) == 0)
        {
            print(library[i]);
            found = true;
        }
    }
    if (!found) cout << "Magazine not found.\n";
}

void filterByAuthor(Item* library, size_t size)
{
    char author[SIZE];
    cout << "Enter author: ";
    cin.ignore();
    cin.getline(author, SIZE);
    bool found = false;
    for (size_t i = 0; i < size; i++)
    {
        if (library[i].type == BOOK && strcmp(library[i].author, author) == 0)
        {
            print(library[i]);
            found = true;
        }
    }
    if (!found) cout << "No books found for this author.\n";
}

void filterByGenre(Item* library, size_t size)
{
    char genre[SIZE];
    cout << "Enter genre: ";
    cin.ignore();
    cin.getline(genre, SIZE);
    bool found = false;
    for (size_t i = 0; i < size; i++)
    {
        if (library[i].type == BOOK && strcmp(library[i].genre, genre) == 0)
        {
            print(library[i]);
            found = true;
        }
    }
    if (!found) cout << "No books found for this genre.\n";
}

void filterMagazinesByYear(Item* library, size_t size)
{
    size_t year;
    cout << "Enter year: ";
    cin >> year;
    bool found = false;
    for (size_t i = 0; i < size; i++)
    {
        if (library[i].type == MAGAZINE && library[i].year == year)
        {
            print(library[i]);
            found = true;
        }
    }
    if (!found) cout << "No magazines found for this year.\n";
}

void countBooksByGenre(Item* library, size_t size)
{
    char genre[SIZE];
    cout << "Enter genre: ";
    cin.ignore();
    cin.getline(genre, SIZE);
    int count = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (library[i].type == BOOK && strcmp(library[i].genre, genre) == 0)
            count++;
    }
    cout << "Books of genre '" << genre << "': " << count << endl;
}

void deleteNewspapersByYear(Item*& library, size_t& size)
{
    size_t year;
    cout << "Enter year to delete newspapers: ";
    cin >> year;
    size_t newSize = 0;
    Item* tmp = new Item[size];
    for (size_t i = 0; i < size; i++)
    {
        if (!(library[i].type == NEWSPAPER && library[i].year == year))
            tmp[newSize++] = library[i];
    }
    delete[] library;
    library = new Item[newSize];
    for (size_t i = 0; i < newSize; i++)
        library[i] = tmp[i];
    delete[] tmp;
    size = newSize;
    cout << "Deleted all newspapers for year " << year << ".\n";
}

