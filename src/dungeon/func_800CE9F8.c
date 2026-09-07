#include "common.h"
#include "m2c_compat.h"

typedef void (*Func4)(void *, void *, void *, void *);
extern u16 D_80083462[5];
extern Func4 D_800E22E0[];
extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern s32 func_800BCB04();

typedef struct S_800D4158_0 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800D4158_0;   /* arg2 in func_800D4158 */

typedef struct S_800D4158_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D4158_1;   /* arg1 in func_800D4158 */

typedef struct S_800D4158_2 {
    u8 pad_00[0x90];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x3];
    union { u8 u; s8 s; } unk_9D;   /* accessed as both */
    u16 unk_9E;
} S_800D4158_2;   /* arg0 in func_800D4158 */

void func_800D4158(void *arg0, S_800D4158_1 *arg1, S_800D4158_0 *arg2) {
    void *s0 = arg0;
    u16 flags;
    u32 flags32;
    s16 dist16;
    s32 raw;
    s16 phase;
    s32 color;

    if (*D_80083462 & 0x2000) {
        (*(u8 *)((u8 *)s0 + 0x71)) = (*(u8 *)((u8 *)s0 + 0x71)) & 0x7f;
        goto epilogue;
    }
    if ((*(Func4 *)((u8 *)s0 + 0x8c)) != NULL) {
        ((Func4)(*(Func4 *)((u8 *)s0 + 0x8c)))(s0, arg1, arg2, s0);
    }
    D_800E22E0[(*(u8 *)((u8 *)s0 + 0x9a))](s0, arg1, arg2, s0);
    if (!(arg2->unk_14 & 0x8000)) {
        if (!(arg2->unk_14 & 0x40)) {
            func_800478B8(arg2);
        }
    }
    arg1->unk_00.at00.v += arg1->unk_0C;
    arg1->unk_04.at00.v += arg1->unk_10;
    flags = ((S_800D4158_2 *)arg0)->unk_98;
    if (flags & 8) {
        ((S_800D4158_2 *)arg0)->unk_9D.u = 0;
        goto step_done;
    }
    arg1->unk_14 += ((S_800D4158_2 *)arg0)->unk_9D.s * 0x14000;
    ((S_800D4158_2 *)arg0)->unk_9D.s = ((S_800D4158_2 *)arg0)->unk_9D.u + 1;
step_done:
    ((S_800D4158_2 *)arg0)->unk_90.at00.v += arg1->unk_14;
    if (((S_800D4158_2 *)arg0)->unk_98 & 4) {
        goto clear_flag;
    }
    raw = func_800BCB04(arg1->unk_00.at02.v, arg1->unk_04.at02.v,
                        (s16)((*(u16 *)((u8 *)s0 + 0x88)) - 0x20));
    dist16 = (s16)raw;
    if (dist16 >= 0x200) {
        goto clear_flag;
    }
    if (((S_800D4158_2 *)arg0)->unk_90.at02.v + (*(s16 *)((u8 *)s0 + 0x88)) < dist16) {
        (void)*(volatile u16 *)((s8 *)arg0 + 0x98);
        goto flag_check;
    }
    if (dist16 >= (*(s16 *)((u8 *)s0 + 0x88))) {
        ((S_800D4158_2 *)arg0)->unk_90.at00.v = 0;
    } else {
        ((S_800D4158_2 *)arg0)->unk_90.at02.v = raw - (*(u16 *)((u8 *)s0 + 0x88));
    }
    arg1->unk_14 = 0;
    (*(s32 *)((u8 *)s0 + 0x1c)) |= 0x08000000;
    ((S_800D4158_2 *)arg0)->unk_9D.s = 0;
flag_check:
    flags32 = (*(u32 *)((u8 *)s0 + 0x1c));
    if (flags32 & 0x40000000) {
        (*(u32 *)((u8 *)s0 + 0x1c)) = flags32 & 0xbfffffff;
        raw = func_800BCB04(
        (arg2->unk_24 << 6) | 0x20,
        (arg2->unk_25 << 6) | 0x20,
            (s16)((*(u16 *)((u8 *)s0 + 0x88)) - 0x20));
        ((S_800D4158_2 *)arg0)->unk_90.at02.v += (*(u16 *)((u8 *)s0 + 0x88)) - raw;
        (*(s16 *)((u8 *)s0 + 0x88)) = raw;
    }
    goto angle_start;
clear_flag:
    (*(u32 *)((u8 *)s0 + 0x1c)) &= 0xf7ffffff;
angle_start:
    arg1->unk_0A = (*(u16 *)((u8 *)s0 + 0x88)) +
                                   ((S_800D4158_2 *)arg0)->unk_90.at02.v;
angle_done:
    phase = ((S_800D4158_2 *)arg0)->unk_9E;
    phase++;
    phase %= 96;
    ((S_800D4158_2 *)arg0)->unk_9E = phase;
    if ((s16)phase < 0x19) {
        color = (func_800644B8((s16)phase * 0x55) >> 4) * 0x60;
        color = (color >> 8) + 0x80;
        arg2->unk_0E = color;
        arg2->unk_0D = color;
        arg2->unk_0C = color;
    } else {
        arg2->unk_0E = 0x80;
        arg2->unk_0D = 0x80;
        arg2->unk_0C = 0x80;
    }
    arg2->unk_14 |= 0x40;
    (*(u32 *)((u8 *)s0 + 0x1c)) |= 0x200;
epilogue:
    return;
}
