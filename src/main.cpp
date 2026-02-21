#include "../util/offsets.h"
#include "player.h"
#include "menu.h"

#include <cstdio>

Menu menu;

DWORD ret_address = 0x0040BE83;
DWORD print_address = 0x419880; // address of print subroutine

const char* empty_text = "";
static char debugText[4][32];
const char* text = "";

DWORD x;
DWORD y;

void print_text(DWORD x, DWORD y, const char* text) {
	__asm {
		mov ecx, text
		push y
		push x
		call print_address
		add esp, 8 // balance stack
	}
}

__declspec(naked) void codecave() {

	// recreate speed print with empty text
	__asm {
		mov ecx, empty_text
		call print_address
		pushad
	}
	
	// draw menu loop
	print_text(10, 50 + (100 * menu.cursor_position), menu.cursor);
	for (int i = 0; i < MAX_ITEMS; i++) {
		print_text(50, 50 + (100 * i), menu.items[i]);
		print_text(500, 50 + (100 * i), menu.get_state(i));
	}


	__asm {
		popad
		jmp ret_address
	}
}


Player* player;
void injected_thread() {
	menu = Menu();

	uintptr_t baseAddress = (uintptr_t)GetModuleHandle(NULL);
	player = (Player*)(*(uintptr_t*)(baseAddress + LOCAL_PLAYER_OFFSET));

	while (true) {
		
		if (menu.item_enabled[HEALTH]) { player->health = 999; }
		if (menu.item_enabled[PRIMARY_AMMO]) { player->primaryAmmo = 99; }
		if (menu.item_enabled[SECONDARY_AMMO]) { player->secondaryAmmo = 99; }
		if (menu.item_enabled[ARMOR]) { player->armor = 99; }

		menu.handle_input();

		Sleep(1);
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {

	DWORD old_protect;
	unsigned char* hook_location = (unsigned char*)0x0040BE7E; // draw showspeed call location

	if (fdwReason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)injected_thread, NULL, 0, NULL);

		VirtualProtect((void*)hook_location, 5, PAGE_EXECUTE_READWRITE, &old_protect);
		*hook_location = 0xE9; // relative JMP at hook location
		*(DWORD*)(hook_location + 1) = (DWORD)&codecave - ((DWORD)hook_location + 5);
		// relative JMP needs a 4-byte offset
		// offset = destination - (current_address + 5)
		// +5 is accounting for size of JMP (opcode + 4-byte offset)
		// replacing call instruction (also 5 bytes) so don't need to pad
	}

	return true;
}