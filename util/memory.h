#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class Memory {
private:
	uintptr_t baseAddress;
public:
	Memory() {
		baseAddress = (uintptr_t)GetModuleHandle(NULL);
	}

	auto Read(uintptr_t offset) {
		return *(uintptr_t*)(baseAddress + offset);
	}

	void Write(uintptr_t address, auto value) {
		*(uintptr_t*)(address) = value;
	}
};