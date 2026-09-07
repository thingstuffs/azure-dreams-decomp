#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} UnkStruct_800B0DB8;

extern UnkStruct_800B0DB8 D_80110EB8;

s32 func_800AE518(s32 arg0) {
    D_80110EB8.unk0 = arg0;
    D_80110EB8.unk8 = 3;
    return 2;
}
