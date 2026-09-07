#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} TownStruct80110EB8;

extern TownStruct80110EB8 D_80110EB8;

s32 func_800AE534(s32 arg0) {
    D_80110EB8.unk0 = arg0;
    D_80110EB8.unk8 = 5;
    return 1;
}
