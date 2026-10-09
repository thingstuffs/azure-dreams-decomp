#ifndef SHARED_DUNGEON_PROJECTILE_VIEWS_H
#define SHARED_DUNGEON_PROJECTILE_VIEWS_H
#include "common.h"
#include "shared/sprite_source.h"
/* Partial game-object views jointly observed by projectile producers and callbacks.
 * Offsets and signed/unsigned access forms are retail constraints; sizes are views. */
typedef struct ProjectileState {
    void *unk_00;
    void *unk_04;
    u8 pad_08[1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;
    union { s32 s; u16 u; } unk_0C;
    s32 unk_10;
    u8 pad_14[0x3C];
    union { s16 s; u16 u; } unk_50;
} ProjectileState;

typedef struct ProjectileMotion {
    union {
        s32 s;
        struct { u8 pad_00[2]; s16 unk_02; } h;
    } unk_00;
    union {
        s32 s;
        struct { u8 pad_04[2]; s16 unk_06; } h;
    } unk_04;
    union {
        s32 s;
        struct { u8 pad_08[2]; u16 unk_0A; } h;
    } unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} ProjectileMotion;

typedef struct ProjectileSprite {
    void *unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[2];
    void *unk_08;
    union {
        struct { u8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[1]; u8 v; } at01;
        struct { u8 pad[2]; u8 v; } at02;
    } unk_0C;
    s16 unk_10;
    u8 pad_12[2];
    u16 unk_14;
    u8 pad_16[6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[4];
    u8 unk_24;
    u8 unk_25;
} ProjectileSprite;

typedef struct ProjectileActor {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;
    u8 pad_2C[0x34];
    union { void *p; s32 s; } unk_60;
    u8 pad_64[0x0E];
    union { s8 s; u8 u; } unk_72;
    union { s8 s; u8 u; } unk_73;
} ProjectileActor;

typedef struct ProjectileObject {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
} ProjectileObject;

typedef struct ProjectileParticle {
    void *unk_00;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x40];
    u16 unk_48;
    s16 unk_4A;
    union { s16 s; u16 u; } unk_4C;
} ProjectileParticle;

typedef struct AnimationFlags {
    u16 unk_00;
} AnimationFlags;

typedef struct ObjectStatusPrefix {
    u8 pad_00[0x1E];
    u16 unk_1E;
} ObjectStatusPrefix;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 rx;
    s32 ry;
    s32 rz;
} FixedCoords;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} SVECTOR;

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} PositionFields;

typedef struct {
    u32 tag;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    u8 u0;
    u8 v0;
    u16 clut;
    s16 x1;
    s16 y1;
    u8 u1;
    u8 v1;
    u16 tpage;
    s16 x2;
    s16 y2;
    u8 u2;
    u8 v2;
    u16 pad2;
    s16 x3;
    s16 y3;
    u8 u3;
    u8 v3;
    u16 pad3;
} POLY_FT4;

typedef struct {
    u8 pad0[0xB0];
    u32 ot[0x208];
    u8 pad8D0[0x8D0 - 0x8D0];
    u8 *next_prim;
} RenderContext;

typedef struct {
    u8 pad0[0x52];
    s16 frame;
} RenderRecord;

typedef struct EffectStatusPrefix {
    u16 unk_00;
} EffectStatusPrefix;
typedef struct ProjectileOwnerFlags {
    u8 pad_00[0x10];
    s32 unk_10;
} ProjectileOwnerFlags;
#endif
