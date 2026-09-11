#include "common.h"

extern int rand(void);
#ifndef NON_MATCHING
extern void *D_80089140[15];
#endif

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
#ifndef NON_MATCHING
    u32 case_index;
    static void *const case_labels[4] = {
        &&case_4, &&case_15, &&case_18, &&case_14
    };
#endif

    amount = flags = 0;
#ifndef NON_MATCHING
    case_index = entry->unk1 - 4;
    if (case_index >= 15) {
        goto done;
    }
    goto *D_80089140[case_index];
#else
    switch (entry->unk1) {
    case 4:
#endif
case_4:
        amount = (rand() & 7) | 4;
        goto done;
#ifdef NON_MATCHING
    case 15:
    case 16:
    case 17:
#endif
case_15:
        flags = -128;
        if ((rand() & 3) != 0) {
            goto done;
        }
        roll = (rand() & 3) - 1;
        amount = roll;
        if (roll >= 0) {
            goto done;
        }
        flags = -64;
        goto done;
#ifdef NON_MATCHING
    case 18:
#endif
case_18:
        amount = rand() % 40 + 60;
        goto done;
#ifdef NON_MATCHING
    case 14:
#endif
case_14:
        amount = 1;
        flags = 0;
#ifdef NON_MATCHING
        break;
    }
#endif
done:
    entry->unk2 = amount;
    entry->unk3 = flags;
}
