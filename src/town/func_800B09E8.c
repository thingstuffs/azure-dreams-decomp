#include "common.h"

typedef struct {
    s32 words[17];
} CopyBlock;

typedef struct {
    u8 pad0[0x30];
    s32 value;
    CopyBlock block;
} Source;

typedef struct {
    u8 pad0[0x38];
    s32 value38;
    u8 pad3C[0x60];
    s32 value9C;
    u8 padA0[8];
    s32 valueA8;
    u8 padAC[0xE];
    u8 valueBA;
    u8 padBB[0xD];
    CopyBlock block;
} TownState;

extern TownState D_80082A38;

void func_800AE148(Source *arg0) {
    D_80082A38.value38 = arg0->value;
    D_80082A38.valueA8 = arg0->value;
    D_80082A38.valueBA = 0;
    D_80082A38.value9C = 0;
    D_80082A38.block = arg0->block;
}
