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

void func_807AFDEC(void *arg0, Position3 *arg1, ColorPart *arg2)
{
    void *call_base;
    Offset3 offset;
    Position3 *source;
    s32 color;
    u16 value;
    s16 timer;

    offset.x = 0;
    offset.y = 0;
    offset.z = -D_800DDC42 - 8;

    source = ((S_807AFDEC_1_pre *)(((S_807AFDEC_0 *)arg0)->unk_00))[-1].unk_00;
    value = source->x;
    arg1->x = value;
    arg1->y = source->y + offset.y;
    arg1->z = source->z + offset.z;

    if (((S_807AFDEC_0 *)arg0)->unk_08.s == 0) {
        color = arg2->b | (arg2->r | arg2->g);
        color += (0xC0 - color) / ((S_807AFDEC_0 *)arg0)->unk_0C.s;

        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)arg0)->unk_00))->unk_14 & 1) {
            arg2->r = color;
        }
        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)arg0)->unk_00))->unk_14 & 4) {
            arg2->g = color;
        }
        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)arg0)->unk_00))->unk_14 & 2) {
            arg2->b = color;
        }

        {
            call_base = (u8 *)arg0 - 0x20;

            if (((S_807AFDEC_0 *)arg0)->unk_0C.s >= 8) {
                func_800F749C(call_base, arg1, ((S_807AFDEC_0 *)arg0)->unk_00);
                func_800F749C(call_base, arg1, ((S_807AFDEC_0 *)arg0)->unk_00);
                func_800F749C(call_base, arg1, ((S_807AFDEC_0 *)arg0)->unk_00);
            }

            timer = ((S_807AFDEC_0 *)arg0)->unk_0C.u - 1;
            ((S_807AFDEC_0 *)arg0)->unk_0C.u = timer;
            if ((timer << 16) <= 0) {
                ((S_807AFDEC_0 *)arg0)->unk_0C.u = 8;
                ((S_807AFDEC_0 *)arg0)->unk_08.u++;
                func_800F7830();
            }
        }
    } else {
        color = arg2->b | (arg2->r | arg2->g);
        color += -color / ((S_807AFDEC_0 *)arg0)->unk_0C.s;

        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)arg0)->unk_00))->unk_14 & 1) {
            arg2->r = color;
        }
        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)arg0)->unk_00))->unk_14 & 4) {
            arg2->g = color;
        }
        if (((S_807AFDEC_1 *)(((S_807AFDEC_0 *)arg0)->unk_00))->unk_14 & 2) {
            arg2->b = color;
        }

        timer = ((S_807AFDEC_0 *)arg0)->unk_0C.u - 1;
        ((S_807AFDEC_0 *)arg0)->unk_0C.u = timer;
        if ((timer << 16) <= 0) {
            (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}
