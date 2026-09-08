#include "common.h"

typedef struct S_818FF19C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    s16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    u8 pad_0C[0x24];
    void * unk_30;
    void * unk_34;
    void * unk_38;
    void * unk_3C;
} S_818FF19C_0;   /* arg0 in func_818FF19C */

typedef struct S_818FF19C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_818FF19C_1;   /* arg1 in func_818FF19C */

typedef struct S_818FF19C_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_818FF19C_2;   /* arg2 in func_818FF19C */

typedef struct S_818FF19C_3 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_818FF19C_3;   /* ((S_818FF19C_0 *)arg0)->unk_34 in func_818FF19C */

typedef struct S_818FF19C_4 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818FF19C_4;   /* ((S_818FF19C_0 *)arg0)->unk_30 in func_818FF19C */



typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} __attribute__((packed)) Rect8;

extern Rect8 D_80024028;
extern Rect8 D_80024030;
extern s16 D_80025E80;
extern u16 D_80025EE8[];
extern s32 D_800814A0;

extern void func_80024A54() __attribute__((noreturn));
extern void func_80024AEC() __attribute__((noreturn));
extern void func_80024D54() __attribute__((noreturn));
extern s32 func_80067014(s32);
extern void func_800672D8(Rect8 *, u16 *);
extern void func_8006733C(Rect8 *, u16 *);
extern void func_800B8FC8(void *, Rect8 *, s16 *, s32, s32);

void func_818FF19C(void *arg0, void *arg1, void *arg2) {
    Rect8 *call_rect;
    Rect8 first;
    Rect8 second;
    s16 pos[2];
    s32 outer;
    s32 inner;
    s32 cell;
    s32 adjusted_phase;
    s32 quarter;
    s32 state;
    s32 status;
    s16 base_y;
    s16 row_y;
    s16 base_x;
    u16 empty;
    u8 *grid_page;
    s32 phase;
    s16 next_phase;
    u16 *scan;

    first = D_80024028;
    second = D_80024030;
    status = ((S_818FF19C_0 *)arg0)->unk_0A;
    D_80025E80 = 1;
    if (status == 0) {
        s32 old_value;
        s32 delta;

        ((S_818FF19C_0 *)arg0)->unk_0A = 1;
        old_value = ((S_818FF19C_1 *)arg1)->unk_08;
        delta = -0x20000;
        ASM_KEEP(old_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ASM_TAILSLOT_PIN(delta);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024A54();
    }

    ((S_818FF19C_0 *)arg0)->unk_0A = 0;
    ((S_818FF19C_1 *)arg1)->unk_08 += 0x20000;
    state = ((S_818FF19C_0 *)arg0)->unk_00.s;
    if (state != 0) {
        if (state != 1) {
            call_rect = &second;
            func_80024D54();
        }
        goto draw;
    }

    outer = 0;
    grid_page = (u8 *)0x80020000;
    empty = 0xFFFF;
    base_y = 0x340;
    do {
        inner = 0;
        row_y = base_y;
        base_x = 0x154;
        do {
            second.x = row_y;
            second.y = base_x;
            second.w = 0x18;
            second.h = 0x15;
            func_8006733C(&second, (u16 *)(grid_page + 0x5EE8));
            do {
            } while (func_80067014(1) != 0);

            scan = (u16 *)(grid_page + 0x5EE8);
            cell = 0;
            do {
                if (*scan == 0) {
                    *scan = empty;
                    func_80024AEC(cell);
                }
                *scan = 0;
                cell++;
                scan++;
            } while (cell < 0x1F8);

            func_800672D8(&second, (u16 *)(grid_page + 0x5EE8));
            inner++;
            base_x += 0x15;
        } while (inner < 4);

        outer++;
        base_y += 0x18;
    } while (outer < 4);

    ((S_818FF19C_0 *)arg0)->unk_00.u++;
    ((S_818FF19C_2 *)arg2)->unk_14 &= 0xFF7F;

draw:
    second.x = 0x340;
    second.y = 0x100;
    second.w = 0x60;
    second.h = 0x54;
    pos[0] = 0x370;
    pos[1] = 0x148;
    func_800B8FC8(((S_818FF19C_0 *)arg0)->unk_38, &second, pos, 0, 1);

    pos[0] = first.x + (first.w >> 1) - 6;
    adjusted_phase = ((S_818FF19C_0 *)arg0)->unk_02;
    if (adjusted_phase < 0) {
        adjusted_phase += 3;
    }
    quarter = (adjusted_phase >> 2) - 0x4E;
    pos[1] = first.y - quarter;
    func_800B8FC8(((S_818FF19C_0 *)arg0)->unk_3C, &first, pos, 1, 1);

    phase = ((S_818FF19C_0 *)arg0)->unk_02;
    if (phase < 0x15) {
        ((S_818FF19C_2 *)arg2)->unk_0E = (phase << 7) / 20;
        ((S_818FF19C_2 *)arg2)->unk_0D = (((S_818FF19C_0 *)arg0)->unk_02 << 7) / 20;
        ((S_818FF19C_2 *)arg2)->unk_0C = (((S_818FF19C_0 *)arg0)->unk_02 << 7) / 20;
    }
    if (((S_818FF19C_0 *)arg0)->unk_02 >= 0x51) {
        ((S_818FF19C_2 *)arg2)->unk_0E = ((0x64 - ((S_818FF19C_0 *)arg0)->unk_02) << 7) / 20;
        ((S_818FF19C_2 *)arg2)->unk_0D = ((0x64 - ((S_818FF19C_0 *)arg0)->unk_02) << 7) / 20;
        ((S_818FF19C_2 *)arg2)->unk_0C = ((0x64 - ((S_818FF19C_0 *)arg0)->unk_02) << 7) / 20;
    }

    next_phase = (u16)((S_818FF19C_0 *)arg0)->unk_02 + 1;
    ((S_818FF19C_0 *)arg0)->unk_02 = next_phase;
    if (next_phase >= 0x65) {
        ((S_818FF19C_0 *)arg0)->unk_02 = 0;
        ((S_818FF19C_0 *)arg0)->unk_00.u++;
        ((S_818FF19C_3 *)(((S_818FF19C_0 *)arg0)->unk_34))->unk_90 = 1;
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if ((u32)(((S_818FF19C_4 *)(((S_818FF19C_0 *)arg0)->unk_30))->unk_13 - 0x33) < 4U) {
        ((S_818FF19C_2 *)arg2)->unk_14 |= 0x80;
    }
}
