#include "util/memory.h"
#include "util/offsets.h"

void injected_thread() {
	Memory memory = Memory();
	while (true) {
		if (GetAsyncKeyState('M')) {
			uintptr_t localPlayer = memory.Read(LOCAL_PLAYER_OFFSET);
			memory.Write(localPlayer + HEALTH_OFFSET, 69);
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