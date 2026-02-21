#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define MAX_ITEMS 5

#define HEALTH 0
#define PRIMARY_AMMO 1
#define SECONDARY_AMMO 2
#define ARMOR 3
#define NO_RECOIL 4

class Menu {
public:
	int cursor_position;
	const char* cursor = ">";

	const char* items[MAX_ITEMS] = { "Health", "Primary", "Secondary", "Armor", "NoRecoil"};
	bool item_enabled[MAX_ITEMS] = { false };

	const char* get_state(int item) {
		return item_enabled[item] ? "On" : "Off";
	}

	void handle_input() {
		if (GetAsyncKeyState('K') & 1) { cursor_position++; }
		if (GetAsyncKeyState('J') & 1) { cursor_position--; }
		if (GetAsyncKeyState('H') & 1 || GetAsyncKeyState('L') & 1) {
			item_enabled[cursor_position] = !item_enabled[cursor_position];
		}

		// wrap
		if (cursor_position < 0) { cursor_position = (MAX_ITEMS - 1); }
		if (cursor_position > (MAX_ITEMS - 1)) { cursor_position = 0; }
	}

	Menu() {
		cursor_position = 0;
	}
};