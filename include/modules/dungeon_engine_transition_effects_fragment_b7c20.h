#ifndef FRAGMENT_FRAGMENT_B7C20_H
#define FRAGMENT_FRAGMENT_B7C20_H
#include "common.h"
/* One packed eight-byte transfer value; the consumers only copy it. */
typedef struct { u32 word[2]; } __attribute__((packed)) TransitionWords;
typedef struct MapTile { u16 type; u16 height; u16 unk_04; } MapTile;
extern TransitionWords D_80088CB0;
extern u8 D_800E50A8[];
extern MapTile D_800EA000[];
extern void func_800672D8(void *transfer_value, u8 *pixels);
#endif
