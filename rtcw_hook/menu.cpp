#include "menu.h"
#include "funcs.h"
#include "variables.h"

vec4_t colorBlack = { 0, 0, 0, 1 };
vec4_t colorRed = { 1, 0, 0, 1 };
vec4_t colorGreen = { 0, 1, 0, 1 };
vec4_t colorBlue = { 0, 0, 1, 1 };
vec4_t colorYellow = { 1, 1, 0, 1 };
vec4_t colorMagenta = { 1, 0, 1, 1 };
vec4_t colorCyan = { 0, 1, 1, 1 };
vec4_t colorWhite = { 1, 1, 1, 1 };
vec4_t colorLtGrey = { 0.75, 0.75, 0.75, 1 };
vec4_t colorMdGrey = { 0.5, 0.5, 0.5, 1 };
vec4_t colorDkGrey = { 0.25, 0.25, 0.25, 1 };

namespace menu
{
	int menu_height = 0;
	int item_index = 0;
	int selected_item_index = 0;
	std::vector<std::shared_ptr<c_menu_item>> menu_items{};

	void add_items()
	{
		//why std::shared_ptr?? leftover, that's why
		menu_items.push_back(std::make_shared<c_menu_item>("Aimbot", &vars.aimbot.enabled, 0, 1));
		menu_items.push_back(std::make_shared<c_menu_item>("Silent Aim", &vars.aimbot.silentaim, 0, 1));
		menu_items.push_back(std::make_shared<c_menu_item>("Autofire", &vars.aimbot.autofire, 0, 1));
		menu_items.push_back(std::make_shared<c_menu_item>("No Recoil", &vars.weapons.norecoil, 0, 1));
		menu_items.push_back(std::make_shared<c_menu_item>("No Spread", &vars.weapons.nospread, 0, 1));
		menu_items.push_back(std::make_shared<c_menu_item>("High Damage", &vars.weapons.highdamage, 0, 1));
		menu_items.push_back(std::make_shared<c_menu_item>("Wallhack", &vars.visuals.wallhack, 0, 1));
		menu_items.push_back(std::make_shared<c_menu_item>("ESP", &vars.visuals.esp, 0, 1));
		menu_items.push_back(std::make_shared<c_menu_item>("Field of View", &vars.visuals.fov, 65, 180));
		//menu_items.push_back(std::make_shared<c_menu_item>("Bunnyhop", &vars.misc.bunnyhop, 0, 1));
		menu_items.push_back(std::make_shared<c_menu_item>("AI Cockblock", &vars.misc.cockblock, 0, 1));
	}

	void paint()
	{
		engine::cg_fillrect(10, 35, 150.f, 20.f, colorBlack);
		engine::cg_drawrect(10, 35, 150.f, 20.f, 0.5f, colorCyan);
		engine::cg_drawstringext(28, 40, "[ RtCW ClientHook ]", colorLtGrey, qtrue, qtrue, 6, 8, 32); //uhh more or less centered lol
		calc_height();
		engine::cg_fillrect(10, 60, 150.f, menu_height, colorDkGrey);
		engine::cg_drawrect(10, 60, 150.f, menu_height, 0.5f, colorCyan);

		int item_y = 55;

		for(size_t i = 0; i < menu_items.size(); ++i)
		{
			auto item = menu_items.at(i);
			engine::cg_drawstringext(15, item_y += 10, item->name.c_str(), selected_item_index == item->item_index ? colorWhite : colorMdGrey, qtrue,
				selected_item_index == item->item_index ?  qtrue : qfalse, 5, 6, 64);
			engine::cg_drawstringext(140, item_y, std::to_string(*item->value).c_str(), selected_item_index == item->item_index ? colorWhite : colorMdGrey, qtrue,
				selected_item_index == item->item_index ? qtrue : qfalse, 5, 6, 64);
		}
	}

	std::shared_ptr<c_menu_item> get_selected_item()
	{
		return menu_items.at(selected_item_index);
	}

	void calc_height()
	{
		//initial padding
		menu_height = 5;
		for (auto &item : menu_items)
			menu_height += 10;
		//add some more padding after everything
		menu_height += 5;
	}

	void handle_keys(WPARAM key)
	{
		const size_t items_size = menu_items.size();

		if (key == VK_UP)
		{
			if (selected_item_index - 1 < 0)
				selected_item_index = items_size - 1;
			else
				selected_item_index--;
		}
		else if (key == VK_DOWN)
		{
			if (selected_item_index + 1 == items_size)
				selected_item_index = 0;
			else
				selected_item_index++;
		}
		auto item = get_selected_item();
		if (key == VK_RIGHT)
		{
			if (*item->value + 1 > item->high_limit)
				return;

			*item->value += 1;
		}
		else if (key == VK_LEFT)
		{
			if (*item->value - 1 < item->low_limit)
				return;

			*item->value -= 1;
		}
	}
}