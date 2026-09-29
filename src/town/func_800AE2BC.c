#include "common.h"

extern int rand(void);

typedef struct {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s8 unk2;
    /* 0x3 */ s8 unk3;
} Struct800AE2BC;

/* Sets randomized entry values according to its type. */
void func_800ABA1C(Struct800AE2BC *record) {
    s16 amount;
    s32 flags;
    register Struct800AE2BC *entry = record;
    s32 roll;

    amount = flags = 0;
    switch (entry->unk1) {
    case 4:
        amount = (rand() & 7) | 4;
        break;
    case 15:
    case 16:
    case 17:
        flags = -128;
        if ((rand() & 3) != 0) {
            break;
        }
        roll = (rand() & 3) - 1;
        amount = roll;
        if (roll >= 0) {
            break;
        }
        flags = -64;
        break;
    case 18:
        amount = rand() % 40 + 60;
        break;
    case 14:
        amount = 1;
        flags = 0;
        break;
    }
    entry->unk2 = amount;
    entry->unk3 = flags;
}
