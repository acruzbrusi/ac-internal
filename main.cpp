#include <Windows.h>
#include "util/offsets.h"

void injected_thread() {
	while (true) {
		if (GetAsyncKeyState('M')) {
			uintptr_t baseAddress = (uintptr_t)GetModuleHandle(NULL);
			uintptr_t localPlayer = baseAddress + LOCAL_PLAYER_OFFSET;
			uintptr_t playerAddress = *(uintptr_t*)localPlayer;
			uintptr_t* health = (uintptr_t*)(playerAddress + HEALTH_OFFSET);
			*health = 100;
		}

		Sleep(100);
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)injected_thread, NULL, 0, NULL);
	}

	return true;
}