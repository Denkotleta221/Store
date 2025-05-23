#pragma once
#include <string>
using std::string;

struct Store;
void initialize_data(Store& store);
void add_category(Store& store, string name);
void add_product(Store& store, string name, int categoryIndex);
void start(Store& store, string text = "");
void log_in(Store& store);
void sign_in(Store& store);
void main_menu(Store& store);
void category(Store& store);
void cart_show(Store& store);
string* cart(Store& store, string* ary, int& size, int choice_prod);
void admin(Store& store);
void admin_menu(Store& store);
