#include "common.h"

typedef struct TownB4C60 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} TownB4C60;

extern void func_800B23F8(TownB4C60 *arg0);

void func_800B23C0(TownB4C60 *arg0) {
    s32 value = arg0->unkC;

    if (value != 0) {
        arg0->unk4 = (value - 1) / 10;
        func_800B23F8(arg0);
        return;
    }
    arg0->unk4 = 0;
}
