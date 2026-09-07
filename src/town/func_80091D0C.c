#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} UnkStruct;

extern s16 func_8008CB58(UnkStruct *, s32 *, s32);
extern s32 D_800CFD98[];

s16 func_8008F46C(void *arg0) {
    UnkStruct sp10;

    sp10.unk0 = *(s32 *)((u8 *)arg0 + 0);
    sp10.unk4 = *(s32 *)((u8 *)arg0 + 4) - *(s32 *)((u8 *)arg0 + 0x10);
    sp10.unk8 = *(s32 *)((u8 *)arg0 + 8);
    return func_8008CB58(&sp10, &D_800CFD98[0], 2);
}
