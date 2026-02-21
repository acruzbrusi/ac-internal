#pragma once

typedef struct Player {
	char unknown1[4];
	float x;
	float y;
	float z;
	char unknown2[0x30];
	float yaw;
	float pitch;
	char unknown3[0xB0];
	int health;
	int armor;
	char unknown4[0x3C];
	int secondaryAmmo;
	char unknown5[0x10];
	int primaryAmmo;
} Player;