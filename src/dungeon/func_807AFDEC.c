#include "common.h"


typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Offset3;

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Position3;

typedef struct {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
} ColorPart;

extern s32 D_800814A0;
extern u8 D_800DDC42;

extern void func_800F749C(void *, Position3 *, void *);
extern void func_800F7830(void) __attribute__((noreturn));


typedef struct S_807AFDEC_0 {
    void * unk_00;
    u8 pad_04[0x4];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
    u8 pad_0A[0x2];
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
} S_807AFDEC_0;   /* arg0 in func_807AFDEC */

typedef struct S_807AFDEC_1_pre {
    Position3 * unk_00;
    u8 pad_04[0x14];
} S_807AFDEC_1_pre;   /* the 0x18 bytes before ((S_807AFDEC_0 *)arg0)->unk_00 in func_807AFDEC, addressed as ((S_807AFDEC_0 *)arg0)->unk_00[-1] */

typedef struct S_807AFDEC_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_807AFDEC_1;   /* ((S_807AFDEC_0 *)arg0)->unk_00 in func_807AFDEC */

/* Position the effect and fade its selected color channels in, then out. */
void func_807AFDEC(void *effect, Position3 *position, ColorPart *tint)
{
    void *effect_base;
    Offset3 offset;
    Position3 *source_pos;
    s32 intensity;
    u16 source_x;
    s16 ticks_left;

    offset.x = 0;
    offset.y = 0;
    offset.z = -D_800DDC42 - 8;

    source_pos = ((S_807AFDEC_1_pre *)(((S_807AFDEC_0 *)effect)->unk_00))[-1].unk_00;
    source_x = source_pos->x;
    position->x = source_x;
    position->y = source_pos->y + offset.y;
    position->z = source_pos->z + offset.z;

    if (((S_807AFDEC_0 *)effect)->unk_08.s == 0) {
        intensity = tint->b | (tint->r | tint->g);
        intensity += (0xC0 - intensity) / ((S_807AFDEC_0 *)effect)->unk_0C.s;

        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)effect)->unk_00))->unk_14 & 1) {
            tint->r = intensity;
        }
        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)effect)->unk_00))->unk_14 & 4) {
            tint->g = intensity;
        }
        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)effect)->unk_00))->unk_14 & 2) {
            tint->b = intensity;
        }

        {
            effect_base = (u8 *)effect - 0x20;

            if (((S_807AFDEC_0 *)effect)->unk_0C.s >= 8) {
                func_800F749C(effect_base, position, ((S_807AFDEC_0 *)effect)->unk_00);
                func_800F749C(effect_base, position, ((S_807AFDEC_0 *)effect)->unk_00);
                func_800F749C(effect_base, position, ((S_807AFDEC_0 *)effect)->unk_00);
            }

            ticks_left = ((S_807AFDEC_0 *)effect)->unk_0C.u - 1;
            ((S_807AFDEC_0 *)effect)->unk_0C.u = ticks_left;
            if ((ticks_left << 16) <= 0) {
                ((S_807AFDEC_0 *)effect)->unk_0C.u = 8;
                ((S_807AFDEC_0 *)effect)->unk_08.u++;
                func_800F7830();
            }
        }
    } else {
        intensity = tint->b | (tint->r | tint->g);
        intensity += -intensity / ((S_807AFDEC_0 *)effect)->unk_0C.s;

        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)effect)->unk_00))->unk_14 & 1) {
            tint->r = intensity;
        }
        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)effect)->unk_00))->unk_14 & 4) {
            tint->g = intensity;
        }
        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)effect)->unk_00))->unk_14 & 2) {
            tint->b = intensity;
        }

        ticks_left = ((S_807AFDEC_0 *)effect)->unk_0C.u - 1;
        ((S_807AFDEC_0 *)effect)->unk_0C.u = ticks_left;
        if ((ticks_left << 16) <= 0) {
            (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}
