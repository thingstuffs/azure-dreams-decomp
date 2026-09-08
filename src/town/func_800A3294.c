#include "common.h"

extern void *func_800A0988(s32);
extern void *D_800A08F0;

typedef struct {
    s8 pad[0x50];
    void *unk50;
    s8 pad2[0x18];
    s16 unk6C;
} EntityStruct;

void func_800A09F4(s32 arg0, s16 arg1) {
    void *temp_v0;
    EntityStruct *ent;

    temp_v0 = func_800A0988(arg0);
    ent = (EntityStruct *)((u8 *)temp_v0 + 0x20);
    if (temp_v0 != 0) {
        ent->unk50 = &D_800A08F0;
        ent->unk6C = arg1;
    }
}
