#include "common.h"

extern s32 func_8001ADE0(s32);
extern void func_8001AD60(s32);
extern void *D_80016000[3];

typedef struct {
    u8 pad[0x20];
    void *unk20;
} Unk20;

typedef struct {
    u8 pad[0x2F8];
    void (*callback)(s32, s32);
} CallbackData;

s32 func_800163C0(void) {
    if (func_8001ADE0(0x3EB) != 0) {
        func_8001AD60(0x3EB);
        ((CallbackData *)((Unk20 *)D_80016000[0])->unk20)->callback(0xD, 0x200);
        return 1;
    }
    return 0;
}
