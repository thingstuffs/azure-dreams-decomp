#ifndef SLUS_JTBL_800517CC_H
#define SLUS_JTBL_800517CC_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "shared/sprite_frame_state.h"
extern int D_800814A0;

typedef struct EffectState800517CC {
    void *parent;
    s16 state;
    u16 timer;
    s16 wait;
    s16 unkA;
    s16 trigger;
} EffectState800517CC;

typedef struct VecState800517CC {
    s32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 vy;
} VecState800517CC;

typedef struct ColorState800517CC {
    u8 pad[0xC];
    u8 r;
    u8 g;
    u8 b;
} ColorState800517CC;

typedef struct ParentState800517CC {
    u8 pad0[6];
    u16 timer;
    u8 pad8[8];
    void *child10;
} ParentState800517CC;

extern void advance_sprite_animation_and_textures(void *);
extern s32 rsin(s32);
extern s32 rcos(s32);
extern s32 rand(void);

/* Update the effect motion state and detach it from its parent when finished. */

void func_800517CC( EffectState800517CC *effect, VecState800517CC *motion, SpriteFrameState *color);

#endif
