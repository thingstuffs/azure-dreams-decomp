#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173450_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173450_0;   /* arg0 in func_80173450 */


typedef struct S_80173450_2 {
    u8 pad_00[0xC];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173450_2;   /* arg2 in func_80173450 */

typedef struct S_80173450_3 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80173450_3;   /* global in func_80173450 */



extern s32 D_800814A0;
extern s32 D_80083460;

void func_8009A028(void *);
void func_8009A3D0(s32, s32, s32);
void func_800A2FE0(void *);
void func_800A32A4(void *);
void func_800A56E0(s32);
void func_800ACF88(void *);

void func_80173450(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 flags;
    u16 count;
    s32 *global;
    s32 value;
    s32 x;
    s32 y;
    s32 mode;
    s16 *page;

    state = ((S_80173450_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto process;
    }
    if (state >= 2) {
        goto state_ge_2;
    }
    page = (s16 *)0x80080000;
    if (state == 0) {
        goto state_zero;
    }
    goto end;

state_ge_2:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (state == 2) {
        goto update;
    }
    goto end;

state_zero:
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    if (page[0x1A35] != 0) {
        goto end;
    }
    ((S_80173450_0 *)arg0)->unk_9B = 1;

process:
    flags = ((Rec_D_80082E80 *)arg3)->unk_14.at00_s32.v;
    if (flags & 0x4000) {
        if (!(flags & 0x20000000)) {
            func_800ACF88(arg3);
        }
    }
    func_800A56E0(0x805);
    ((S_80173450_0 *)arg0)->unk_96 = 4;
    ((S_80173450_0 *)arg0)->unk_9B++;
    ((S_80173450_2 *)arg2)->unk_12 -= 0x80;

update:
    ((Rec_D_80082E80 *)arg3)->unk_1C.at00_s32.v |= 0x10000000;
    count = ((S_80173450_0 *)arg0)->unk_96 - 1;
    ((S_80173450_0 *)arg0)->unk_96 = count;
    if ((s16)count <= 0) {
        if (((S_80173450_2 *)arg2)->unk_0C.u8 >= 0x10) {
            ((S_80173450_2 *)arg2)->unk_0C.s32 += 0xFFEFEFF0;
        }
        ((S_80173450_2 *)arg2)->unk_10 = 0x20;
        ((S_80173450_2 *)arg2)->unk_14 |= 0xC;
    } else {
        ((S_80173450_2 *)arg2)->unk_0C.s32 = 0x808080;
    }

    if (!(((S_80173450_2 *)arg2)->unk_14 & 0x8000)) {
        if (((S_80173450_2 *)arg2)->unk_0C.u8 >= 0x10) {
            goto end;
        }
    }

    global = &D_80083460;
    value = ((S_80173450_3 *)global)->unk_10;
    if (value == (s32)((u8 *)arg3 - 0x20)) {
        ((S_80173450_3 *)global)->unk_10 = value & 0x7FFFFFFF;
    }
    func_800A2FE0(arg3);
    func_800A32A4(arg3);

    x = ((S_80173450_2 *)arg2)->unk_24;
    y = ((S_80173450_2 *)arg2)->unk_25;
    mode = 0x3000;
    if (((Rec_D_80082E80 *)arg3)->unk_1C.at00_s32.v & 0x2000) {
        mode = 0x300;
    }
    func_8009A3D0(x, y, mode);
    func_8009A028(arg3);
    (*(u16 *)((u8 *)arg3 + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    return;
}

/* MECHANISM: Preserve unused $a1 so arg2/arg3 naturally hold in $s1/$s2, and
   encode the true-space local joins as goto-shaped CFG in retail block order.
   A guarded $v0 page hold plus seam fence restores the zero-state delay slots;
   exact-width fields and the direct D_800814A0 RMW close the remaining words. */
