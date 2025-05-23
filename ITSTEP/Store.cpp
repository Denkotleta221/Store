#include <iostream>
#include <windows.h>
#include <conio.h>
#include "function.h"
using namespace std;
using std::string;

struct Category {
    string name;
};

struct Product {
    string name;
    int categoryIndex;
};

struct Store {
    Category* categories;
    int categoryCount;

    Product* products;
    int productCount;

    string* cart;
    int cartSize;
};

void add_data(Store& store) {
    add_category(store, "Dairy");
    add_product(store, "Milk", 0);
    add_product(store, "Cheese", 0);
    add_product(store, "Yogurt", 0);
    add_product(store, "Butter", 0);
    add_product(store, "Cream", 0);

    add_category(store, "Cereals");
    add_product(store, "Oatmeal", 1);
    add_product(store, "Corn Flakes", 1);
    add_product(store, "Granola", 1);
    add_product(store, "Rice Krispies", 1);
    add_product(store, "Wheat Bran", 1);

    add_category(store, "Bakery");
    add_product(store, "Bread", 2);
    add_product(store, "Croissant", 2);
    add_product(store, "Muffin", 2);
    add_product(store, "Bagel", 2);
    add_product(store, "Bun", 2);

    add_category(store, "Meat");
    add_product(store, "Beef", 3);
    add_product(store, "Chicken", 3);
    add_product(store, "Pork", 3);
    add_product(store, "Lamb", 3);
    add_product(store, "Turkey", 3);

    add_category(store, "Fruits");
    add_product(store, "Apple", 4);
    add_product(store, "Banana", 4);
    add_product(store, "Orange", 4);
    add_product(store, "Grapes", 4);
    add_product(store, "Pineapple", 4);

    add_category(store, "Back");
}


void add_category(Store& store, string name) {
    if (store.categoryCount < 10) {
        store.categories[store.categoryCount++] = { name };
    }
}

void add_product(Store& store, string name, int categoryIndex) {
    if (store.productCount < 100) {
        store.products[store.productCount++] = { name, categoryIndex };
    }
}

void start(Store& store, string text) {
    system("cls");
    cout << "Welcome to 'My Store'\n";
    int choice;
    cout << "1. Log in\n";
    cout << "2. Sign in\n";
    cout << "3. Admin\n";
    cout << text;
    cin >> choice;

    switch (choice) {
    case 1: log_in(store); break;
    case 2: sign_in(store); break;
    case 3: admin(store); break;
    default:
        start(store, "Dont corect choice please try again.\n");
        break;
    }
}

void log_in(Store& store) {
    system("cls");
    string name, pass;
    cout << "Log in:\n";
    cout << "Enter your name: ";
    cin >> name;
    cout << "\nEnter your password: ";
    cin >> pass;

    main_menu(store);
}

void sign_in(Store& store) {
    system("cls");
    string name, pass;
    cout << "Sign in:\n";
    cout << "Enter your name: ";
    cin >> name;
    cout << "\nEnter your password: ";
    cin >> pass;

    main_menu(store);
}

void main_menu(Store& store) {
    system("cls");
    cout << "Main Menu:\n";
    cout << "1. Categories\n";
    cout << "2. Cart\n";
    cout << "3. Back\n";
    cout << "4. Exit\n";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: category(store); break;
    case 2: cart_show(store); break;
    case 3: start(store, ""); break;
    case 4:
        cout << "Exiting the store\n";
        delete[] store.categories;
        delete[] store.products;
        delete[] store.cart;
        exit(0);
    default:
        cout << "Dont corect choice please try again.\n";
        main_menu(store);
        break;
    }
}

void cart_show(Store& store) {
    system("cls");
    cout << "Your cart:\n";
    if (store.cartSize == 0) {
        cout << "Cart is empty..\n";
    }
    else {
        for (int i = 0; i < store.cartSize; i++) {
            cout << i + 1 << ". " << store.cart[i] << "\n";
        }
    }
    system("pause");
    main_menu(store);
}

void category(Store& store) {
    system("cls");
    for (int i = 0; i < store.categoryCount; i++) {
        cout << i + 1 << " ." << store.categories[i].name << "\n";
    }

    int choice;
    cout << "\nChoose a category (1-" << store.categoryCount << "): ";
    cin >> choice;

    if (choice < 1 || choice > store.categoryCount) {
        cout << "Dont corect choice.\n";
        category(store);
        return;
    }

    if (store.categories[choice - 1].name == "Back") {
        main_menu(store);
        return;
    }

    system("cls");
    cout << "\nItems in " << store.categories[choice - 1].name << ":\n";
    for (int i = 0; i < store.productCount; i++) {
        if (store.products[i].categoryIndex == (choice - 1)) {
            cout << i + 1 << ". " << store.products[i].name << "\n";
        }
    }

    int choice_product;
    cout << "Choose the product: ";
    cin >> choice_product;

    if (choice_product < 1 || choice_product > store.productCount || store.products[choice_product - 1].categoryIndex != (choice - 1)) {
        cout << "Dont corect product.\n";
        category(store);
        return;
    }

    system("cls");
    int pay_or_cart;
    cout << "Product: " << store.products[choice_product - 1].name << "\n";
    cout << "1. Buy\n";
    cout << "2. Add to cart.\n";
    cout << "3. Back to category.\n";
    cin >> pay_or_cart;

    switch (pay_or_cart) {
    case 1:
        cout << "Thank you for your purchase!\n";
        system("pause");
        main_menu(store);
        break;
    case 2:
        store.cart = cart(store, store.cart, store.cartSize, choice_product - 1);
        main_menu(store);
        break;
    case 3:
        category(store);
        break;
    default:
        cout << "Dont corect choice.\n";
        category(store);
        break;  
    }
}

string* cart(Store& store, string* ary, int& size, int choice_prod) {
    string* new_ary = new string[size + 1];
    for (int i = 0; i < size; i++) {
        new_ary[i] = ary[i];
    }
    new_ary[size] = store.products[choice_prod].name;
    delete[] ary;
    size += 1;
    return new_ary;
}

void admin_menu(Store& store) {
    system("cls");
    cout << "Admin Menu:\n";
    cout << "1. Add Category\n";
    cout << "2. Add Product to Category\n";
    cout << "3. Exit\n";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        string new_category;
        cout << "Enter new category name: ";
        cin >> new_category;

        store.categories[store.categoryCount - 1].name = new_category;
        add_category(store, "Back");

        cout << "Category added.\n";
        break;
    }
    case 2: {
        cout << "Select category to add product:\n";
        for (int i = 0; i < store.categoryCount; i++) {
            cout << i + 1 << ". " << store.categories[i].name << "\n";
        }

        int cat_index;
        cin >> cat_index;
        if (cat_index < 1 || cat_index > store.categoryCount) {
            cout << "Dont corect category.\n";
            break;
        }

        cat_index--;
        if (store.categories[cat_index].name == "Back") {
            cout << "'Back' is not category\n";
            break;
        }

        string new_item;
        cout << "Enter product name: ";
        cin >> new_item;

        add_product(store, new_item, cat_index);
        cout << "Product added.\n";
        break;
    }
    case 3:
        return;
    default:
        cout << "Dont corect choice\n";
        break;
    }

    system("pause");
    admin_menu(store);
}

void admin(Store& store) {
    system("cls");
    string name, pass;
    cout << "Admin Login:\n";
    cout << "Enter your name: ";
    cin >> name;
    cout << "\nEnter your password: ";
    cin >> pass;

    if (name == "admin228" && pass == "123") {
        admin_menu(store);
    }
    else {
        start(store, "Incorrect login or password!\n");
    }
}

int main() {
    Store store;
    store.categories = new Category[10];
    store.categoryCount = 0;

    store.products = new Product[100];
    store.productCount = 0;

    store.cart = new string[0];
    store.cartSize = 0;

    add_data(store);
    while (true) {
        start(store, "");
    }
}
