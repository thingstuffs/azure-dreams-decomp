#include "common.h"

typedef struct {
    u8 pad0[0x50];
    void *unk50;
    u8 pad54[0x32];
    u8 unk86;
} UnkStruct;

s16 func_80098250(UnkStruct *arg0) {
    s16 value;

    value = arg0->unk86;
    if (arg0->unk50 != 0) {
        value += *(s8 *)((u8 *)arg0->unk50 + 2);
    }
    if (value < 0) {
        value = 0;
    }
    if (value >= 100) {
        value = 99;
    }
    return value;
}
