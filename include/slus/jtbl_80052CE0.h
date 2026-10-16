#ifndef SLUS_JTBL_80052CE0_H
#define SLUS_JTBL_80052CE0_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

typedef struct S_52CE0_Rect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} S_52CE0_Rect;

typedef struct S_52CE0 {
    s16 state;
    s16 timer;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
} S_52CE0;

typedef struct S_52CE0_Pos {
    s32 x;
    s32 y;
} S_52CE0_Pos;

typedef struct S_52CE0_Ent {
    u8 pad0[0x14];
    u16 flags;
} S_52CE0_Ent;

extern void drawShadedHorizontalLine(s16 a0, s16 a1, s16 a2, s16 a3);
extern void MoveImage(S_52CE0_Rect *rect, s32 x, s32 y);

/* Advance the entity animation, moving its position and copying image rows in VRAM. */

void func_80052CE0(S_52CE0 *anim, S_52CE0_Pos *position, S_52CE0_Ent *entity);

#endif
