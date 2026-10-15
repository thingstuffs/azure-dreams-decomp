#ifndef SLUS_OWNED_80047338_H
#define SLUS_OWNED_80047338_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad0[4];
    u16 unk4;
    u8 pad1[2];
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} S_80047338_hdr;

typedef struct {
    u8 pad0[0xC];
    void *unkC;
} S_80047338_rec;

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} S_80047270_hdr;

extern void func_80047270(void *a0, S_80047270_hdr *a1);


extern u16 D_80081518;
extern u16 D_8008151A;
extern u16 D_8008151C;
extern u16 D_8008151E;

/* Packs a texture into the atlas, decodes its data, and uploads it to VRAM. */

void func_80047338(S_80047338_hdr *texture, S_80047338_rec *record, s32 data_offset);

#endif
