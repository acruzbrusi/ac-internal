#include "../util/memory.h"
#include "../util/offsets.h"

class Trainer {
private:
	Memory memory;
	uintptr_t localPlayer;
public:
	Trainer() {
		memory = Memory();
		localPlayer = memory.Read(memory.GetBaseAddress() + LOCAL_PLAYER_OFFSET);
	}

	void SetHealth(uintptr_t value) {
		memory.Write(localPlayer + HEALTH_OFFSET, value);
	}

	void SetPrimaryAmmo(uintptr_t value) {
		memory.Write(localPlayer + PRIMARY_AMMO_OFFSET, value);
	}

	void SetSecondaryAmmo(uintptr_t value) {
		memory.Write(localPlayer + SECONDARY_AMMO_OFFSET, value);
	}

	void SetArmor(uintptr_t value) {
		memory.Write(localPlayer + ARMOR_OFFSET, value);
	}

	uintptr_t GetHealth(void) {
		return memory.Read(localPlayer + HEALTH_OFFSET);
	}

	uintptr_t GetPrimaryAmmo(void) {
		return memory.Read(localPlayer + PRIMARY_AMMO_OFFSET);
	}
	
	uintptr_t GetSecondaryAmmo(void) {
		return memory.Read(localPlayer + SECONDARY_AMMO_OFFSET);
	}

	uintptr_t GetArmor(void) {
		return memory.Read(localPlayer + ARMOR_OFFSET);
	}
};