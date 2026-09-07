#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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
    register Rect8 *call_rect ASM_REG("$5");
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
    status = FIELD(arg0, s16, 0xA);
    D_80025E80 = 1;
    if (status == 0) {
        s32 old_value;
        s32 delta;

        FIELD(arg0, s16, 0xA) = 1;
        old_value = FIELD(arg1, s32, 8);
        ASM_KEEP(old_value);
        delta = -0x20000;
        ASM_KEEP(old_value);
        ASM_TAILSLOT_PIN(delta);
        func_80024A54();
    }

    FIELD(arg0, s16, 0xA) = 0;
    FIELD(arg1, s32, 8) += 0x20000;
    state = FIELD(arg0, s16, 0);
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

    FIELD(arg0, u16, 0)++;
    FIELD(arg2, u16, 0x14) &= 0xFF7F;

draw:
    second.x = 0x340;
    second.y = 0x100;
    second.w = 0x60;
    second.h = 0x54;
    pos[0] = 0x370;
    pos[1] = 0x148;
    func_800B8FC8(FIELD(arg0, void *, 0x38), &second, pos, 0, 1);

    pos[0] = first.x + (first.w >> 1) - 6;
    adjusted_phase = FIELD(arg0, s16, 2);
    if (adjusted_phase < 0) {
        adjusted_phase += 3;
    }
    quarter = (adjusted_phase >> 2) - 0x4E;
    pos[1] = first.y - quarter;
    func_800B8FC8(FIELD(arg0, void *, 0x3C), &first, pos, 1, 1);

    phase = FIELD(arg0, s16, 2);
    if (phase < 0x15) {
        FIELD(arg2, s8, 0xE) = (phase << 7) / 20;
        FIELD(arg2, s8, 0xD) = (FIELD(arg0, s16, 2) << 7) / 20;
        FIELD(arg2, s8, 0xC) = (FIELD(arg0, s16, 2) << 7) / 20;
    }
    if (FIELD(arg0, s16, 2) >= 0x51) {
        FIELD(arg2, s8, 0xE) = ((0x64 - FIELD(arg0, s16, 2)) << 7) / 20;
        FIELD(arg2, s8, 0xD) = ((0x64 - FIELD(arg0, s16, 2)) << 7) / 20;
        FIELD(arg2, s8, 0xC) = ((0x64 - FIELD(arg0, s16, 2)) << 7) / 20;
    }

    next_phase = (u16)FIELD(arg0, s16, 2) + 1;
    FIELD(arg0, s16, 2) = next_phase;
    if (next_phase >= 0x65) {
        FIELD(arg0, s16, 2) = 0;
        FIELD(arg0, u16, 0)++;
        FIELD(FIELD(arg0, void *, 0x34), s16, 0x90) = 1;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if ((u32)(FIELD(FIELD(arg0, void *, 0x30), u8, 0x13) - 0x33) < 4U) {
        FIELD(arg2, u16, 0x14) |= 0x80;
    }
}
