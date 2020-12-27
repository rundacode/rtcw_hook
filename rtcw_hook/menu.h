#pragma once
#include "framework.h"

using callback_t = void*();

class c_menu_item;

namespace menu
{
	void add_items();
	//render the menu
	void paint();
	void calc_height();
	void handle_keys(WPARAM key);
	std::shared_ptr<c_menu_item> get_selected_item();

	extern int menu_height;
	extern int item_index; //global item index, incremented each time it is assigned to an item
	extern int selected_item_index;
	extern std::vector<std::shared_ptr<c_menu_item>> menu_items;
}

class c_menu_item
{
public:
	c_menu_item(std::string_view _name, int* _value, int lLimit, int hLimit) : 
		name(_name.data()), value(_value), low_limit(lLimit), high_limit(hLimit), item_index(menu::item_index++) {}

	std::string name = "[ missing option name ]";
	int* value;
	int item_index = 0;
	//limits are ignored if we're dealing with a bool
	int low_limit = 0;
	int high_limit = 1;
	callback_t callback;
	//FUCK PRIVATE LMAO
};