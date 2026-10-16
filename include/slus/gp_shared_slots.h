#ifndef SLUS_GP_SHARED_SLOTS_H
#define SLUS_GP_SHARED_SLOTS_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "shared/runtime_dispatch.h"
#include "common.h"


extern void *D_80083160[3];
extern u8 D_801C9E40[2][0x108D4];
extern u16 D_80083960[5];
extern s16 D_80080AA4;
extern u16 D_80080AA6;
extern u16 D_80080AA8;
extern u8 D_80080AAA;
extern s16 D_80083858[64];
extern s16 D_800838D8[64];
extern s32 VSync(s32 mode);
extern void PutDispEnv(void *env);
extern void PutDrawEnv(void *env);
extern void DrawSync(s32 mode);
extern s32 rcos(s32 angle);
extern s32 rsin(s32 angle);
extern void func_8003D0F0(void);
extern void func_8003CCB0(s32 layer);

static inline s32 shift10(s32 value)
{
    return value >> 10;
}

/* Swap draw buffers and update the animated coordinate history on a new display field. */

#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void TransMatrix(void *m, void *v);
extern void RotMatrix(void *r, void *m);
extern void SetRotMatrix(void *m);
extern void SetTransMatrix(void *m);
extern void RotTransSV(void *in, void *out, void *flag);
extern void DrawPrim(void *p);
extern s32 rsin(s32);
extern void *buildPositionedTextGlyphs(void *a0, void *a1, s32 a2);

extern s16 D_80080AAC;
extern void *D_80080AB0;
extern s16 D_80080AA4;
extern u16 D_80080AA8;
extern u8 D_8006CDB8[14];
extern u8 D_80083798[];
extern s16 D_80083858[64];
extern s16 D_800838D8[64];
extern void *D_80083160[3];

typedef union { struct { u8 u, v; } c; u16 word; } UVPair;
typedef struct {
    union { u32 word; u8 bytes[4]; } tag;
    u8 r, g, b, code;
    s16 x0, y0;
    UVPair uv0;
    u16 clut;
    s16 x1, y1;
    UVPair uv1;
    u16 tpage;
    s16 x2, y2;
    UVPair uv2;
    u16 pad2;
    s16 x3, y3;
    UVPair uv3;
    u16 pad3;
} SpriteQuad;

/* Draw fourteen sprites with interpolated positions and pulsing color. */

void func_8003CB08(void);
void func_8003CCB0(s32 blend_step);

#endif
