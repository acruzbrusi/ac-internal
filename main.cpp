#include "util/memory.h"
#include "util/offsets.h"

Memory memory;

void SetHealth(uintptr_t value) {
	uintptr_t localPlayer = memory.Read(LOCAL_PLAYER_OFFSET);
	memory.Write(localPlayer + HEALTH_OFFSET, value);
}

void SetPrimaryAmmo(uintptr_t value) {
	uintptr_t localPlayer = memory.Read(LOCAL_PLAYER_OFFSET);
	memory.Write(localPlayer + PRIMARY_AMMO_OFFSET, value);
}

void SetSecondaryAmmo(uintptr_t value) {
	uintptr_t localPlayer = memory.Read(LOCAL_PLAYER_OFFSET);
	memory.Write(localPlayer + SECONDARY_AMMO_OFFSET, value);
}

void SetArmor(uintptr_t value) {
	uintptr_t localPlayer = memory.Read(LOCAL_PLAYER_OFFSET);
	memory.Write(localPlayer + ARMOR_OFFSET, value);
}

void injected_thread() {
	Memory memory = Memory();
	while (true) {
		
		SetHealth(999);
		SetPrimaryAmmo(999);
		SetSecondaryAmmo(999);
		SetArmor(999);

		Sleep(100);
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)injected_thread, NULL, 0, NULL);
	}

	return true;
}