#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Entry12;

typedef struct {
    u16 unk0;
    u16 unk2;
} Entry4;

typedef struct {
    u8 pad0[0x20];
    s32 unk20;
    u16 unk24;
    u16 unk26;
} TownState;

extern Entry12 D_80016470[];
extern TownState D_800167B4;
extern Entry4 D_80016818[];

void func_80017EA0(s32 arg0) {
    register TownState *state ASM_REG("$2") = &D_800167B4;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    Entry12 *entries = D_80016470;
    Entry12 *entry = &entries[arg0];
    Entry4 *position;

    state->unk20 = entry->unk0;
    position = &D_80016818[arg0];
    state->unk24 = position->unk0;
    state->unk26 = position->unk2;
}
