#include "common.h"

extern void func_800478B8(void *arg0);
extern struct { s32 v; s32 pad[2]; } D_800814A0;

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[4];
    s32 unkC;
    s32 unk10;
} UnkStruct807B11B8;

void func_807B11B8(u16 *arg0, UnkStruct807B11B8 *arg1, u16 *arg2) {
    arg1->unk0 += arg1->unkC;
    arg1->unk4 += arg1->unk10;
    func_800478B8(arg2);
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        u16 *hp = (u16 *)((u8 *)arg0 - 2);
        *hp = (u16)(*hp | 0x8000);
        D_800814A0.v = D_800814A0.v | 0x8000;
    }
}
