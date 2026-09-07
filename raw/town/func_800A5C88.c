#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Unk800A5C88;

extern s32 func_800A3450(s32 *, s32);

void func_800A33E8(Unk800A5C88 *arg0) {
    Unk800A5C88 local;
    s32 i;

    local.unk0 = arg0->unk0;
    i = 0;
    local.unk4 = arg0->unk4;
    local.unk8 = arg0->unk8 - 0x240000;

    do {
        if (func_800A3450(&local.unk0, i) == 0) {
            break;
        }
        i++;
    } while (i < 12);
}
