#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} State;

M2C_UNK func_80096A90();                 /* extern */
extern s16 D_8006ADD6;
extern s32 D_800FE508[4];
extern State D_800FE520;

/* Process the terminated entry list and initialize the state for the current mode. */
void func_80096B50(s32 *entries) {
    s16 mode;
    s32 *entry;

    entry = entries;
    D_800FE508[0] = 0x1FFFFFFF;
    D_800FE508[2] = 0x1FFFFFFF;
    D_800FE508[1] = 0;
    D_800FE508[3] = 0;
    if (*entry != 0) {
        do {
            func_80096A90(D_800FE508, *entry);
            do {
                entry++;
            } while (0);
        } while (*entry != 0);
    }
    mode = D_8006ADD6;
    if (mode == 8) {
        D_800FE520.unk0 = 0x03000000;
        (&D_800FE520)->unk4 = 0x04000000;
        (&D_800FE520)->unkC = 0x02A00000;
        (&D_800FE520)->unk8 = 0;
        (&D_800FE520)->unk10 = 0x80000000;
        return;
    }
    if (mode == 0xB) {
        D_800FE520.unk0 = 0;
        (&D_800FE520)->unk4 = 0x04A00000;
        (&D_800FE520)->unkC = 0x03B00000;
        (&D_800FE520)->unk8 = 0;
        (&D_800FE520)->unk10 = 0x80000000;
        return;
    }
    D_800FE520.unk0 = 0x80000000;
}
