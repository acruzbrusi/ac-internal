#pragma once

#define MAX_ITEMS 4

#define HEALTH 0
#define PRIMARY_AMMO 1
#define SECONDARY_AMMO 2
#define ARMOR 3

class Menu {
public:
	int cursor_position;
	const char* cursor = ">";

	const char* items[MAX_ITEMS] = { "Health", "Primary", "Secondary", "Armor" };
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
		if (cursor_position < 0) { cursor_position = 3; }
		if (cursor_position > 3) { cursor_position = 0; }
	}

	Menu() {
		cursor_position = 0;
	}
};