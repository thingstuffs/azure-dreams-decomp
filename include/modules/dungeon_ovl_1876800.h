#ifndef DUNGEON_OVL_1876800_H
#define DUNGEON_OVL_1876800_H
#include "common.h"
#include "modules/dungeon_native_abi.h"
typedef struct EffectMotion {
    s32 x, y, z;
    s32 vx, vy, vz;
} EffectMotion;

/* The object an effect belongs to: bit 0x8000 of its +0x52 flag word marks it. */
typedef struct EffectOwner {
    u8 pad_00[0x52];
    u16 flags;
} EffectOwner;

/* The effect's own record; the 0x20-byte ObjectNodeHeader sits right before it. */
typedef struct EffectRecord {
    EffectOwner *owner;
    u8 pad_04[0x44];
    u16 timer;       /* 0x48: frames to wait in state 0 */
    s16 fade_step;   /* 0x4A: brightness removed per frame in state 1 */
    s16 state;       /* 0x4C: 0 = wait, 1 = fade the sprite */
} EffectRecord;

typedef struct SpriteEntry {
    u8 pad_00[4];
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[6];
    u8 red;          /* 0x0C; the word at +0x0C is cleared as one */
    u8 green;
    u8 blue;
    u8 pad_0F;
    u8 pad_10[4];
    u16 status;      /* 0x14: func_800478B8 result bits, 0x6000 = reached */
} SpriteEntry;


void func_80024850(EffectRecord *, EffectMotion *, SpriteEntry *);
s32 func_800249BC(void *);
#endif
