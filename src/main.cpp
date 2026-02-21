#include "trainer.h"

#include <cstdio>

static char text[32];
void injected_thread() {
	Trainer trainer = Trainer();
	while (true) {
		trainer.SetHealth(999);
		trainer.SetPrimaryAmmo(999);
		trainer.SetSecondaryAmmo(999);
		trainer.SetArmor(999);

		snprintf(text, sizeof(text), "Health: %.2f", (double)trainer.GetHealth());

		Sleep(100);
	}
}

DWORD ret_address = 0x0040BE7E; // return at subroutine call

DWORD x = 0x100;
DWORD y = 0x100;

__declspec(naked) void codecave() {

	__asm {
		mov ecx, offset text
		push y
		push x
		jmp ret_address
	}
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {

	DWORD old_protect;
	unsigned char* hook_location = (unsigned char*)0x0040BE78;

	if (fdwReason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)injected_thread, NULL, 0, NULL);

		VirtualProtect((void*)hook_location, 5, PAGE_EXECUTE_READWRITE, &old_protect);
		*hook_location = 0xE9; // relative JMP at hook location
		*(DWORD*)(hook_location + 1) = (DWORD)&codecave - ((DWORD)hook_location + 5);
		// relative JMP needs a 4-byte offset
		// offset = destination - (current_address + 5)
		// +5 is accounting for size of JMP (opcode + 4-byte offset)

		// push 708
		// push eax
		// ^ 6 bytes
		// so pad last byte with NOP
		*(hook_location + 5) = 0x90;
	}

	return true;
}