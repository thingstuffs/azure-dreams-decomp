#include "common.h"

typedef struct {
    char pad[0x16];
    u16 unk16;
} Struct_80819920;

void func_80023920(s32 arg0, s32 arg1, Struct_80819920 *arg2) {
    arg2->unk16 -= 0x20;
}
