#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 *D_800E3D7C;
extern u8 D_80170F20[];
extern u8 D_80173B98[];
extern u8 D_80176318[];
extern u8 D_80176378[];

void func_80172C10(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 one;
    s32 value;
    s32 *global_state;

    one = 1;
    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        func_800AD4D0(arg3);
        FIELD(arg1, s32, 0xC) =
            *(s16 *)((u8 *)&D_8006CCD8 +
                     ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 19;
        FIELD(arg1, s32, 0x10) =
            *(s16 *)((u8 *)&D_8006CCE8 +
                     ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 19;
        FIELD(arg0, u8, 0x9B)++;

        if (FIELD(arg3, u8, 0x28) == 0) {
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0xC) = 0;
            if (FIELD(arg0, u8, 0xA7) != 0) {
                func_800AAA54(arg0, arg1, arg2, D_80176378);
                if (FIELD(arg0, u8, 0xA8) != 0) {
                    u8 *mark;

                    mark = D_800E3D7C;
                    mark += FIELD(arg0, u8, 0xA8);
                    mark[0xF9] = one;
                }
                return;
            }
            func_800AAA54(arg0, arg1, arg2, D_80176318);
            return;
        }

        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg0, s16, 0x96) = 0;
            FIELD(arg0, u8, 0x9B) = 2;
            return;
        }
        FIELD(arg0, s16, 0x96) =
            (FIELD(arg3, s32, 0x1C) & 0x228) ? 8 : -1;
        /* fall through */

    case 1:
        FIELD(arg1, s32, 0xC) -= FIELD(arg1, s32, 0xC) / 4;
        FIELD(arg1, s32, 0x10) -= FIELD(arg1, s32, 0x10) / 4;

        if (FIELD(arg0, s16, 0x96) > 0) {
            FIELD(arg0, s16, 0x96) = FIELD(arg0, u16, 0x96) - 1;
        } else if (FIELD(arg2, u16, 0x14) & 0x6000) {
            FIELD(arg0, s16, 0x96) = 0;
        }

        if (FIELD(arg0, s16, 0x96) != 0) {
            return;
        }
        if (FIELD(arg3, u8, 0x28) != 0) {
            goto increment_state;
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        if (FIELD(arg0, u8, 0xA7) != 0) {
            func_800AAA54(arg0, arg1, arg2, D_80176378);
            if (FIELD(arg0, u8, 0xA8) != 0) {
                u8 *mark;

                mark = D_800E3D7C;
                mark += FIELD(arg0, u8, 0xA8);
                mark[0xF9] = 1;
            }
            return;
        }
        func_800AAA54(arg0, arg1, arg2, D_80176318);
        return;

increment_state:
        FIELD(arg0, s16, 0x96) = 8;
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 2: {
        s32 case_x;
        s32 case_y;
        s32 case_delta;
        s16 case_timer;
        u16 case_utimer;

        case_timer = FIELD(arg0, s16, 0x96);
        if (case_timer > 0) {
            case_x = FIELD(arg2, u8, 0x24) << 6;
            case_delta = FIELD(arg1, s16, 2) - 0x20;
            case_x = (case_x - case_delta) << 16;
            case_x = case_x / case_timer;
            case_delta = FIELD(arg1, s16, 6) - 0x20;
            FIELD(arg1, s32, 0xC) = case_x;
            case_y = (FIELD(arg2, u8, 0x25) << 6) - case_delta;
            FIELD(arg1, s32, 0x10) =
                (case_y << 16) / FIELD(arg0, s16, 0x96);
        }

        case_utimer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = case_utimer;
        if ((s32)(case_utimer << 16) > 0) {
            return;
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

        global_state = &D_80083460;
        value = global_state[4];
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            global_state[4] = value & 0x7FFFFFFF;
        }
        if (FIELD(arg0, u8, 0xA7) != 0) {
            FIELD(arg0, void *, 0x8C) = D_80173B98;
        } else {
            FIELD(arg0, void *, 0x8C) = D_80170F20;
        }
        return;
    }

    default:
        return;
    }
}

/* MECHANISM: Split the fall-through timer web so direct fields emit the fresh lh/lhu pair.
   Case-2 sibling locals preload the second coordinate into the first mflo hazard slot.
   Compound /4 damping and pointer-update indexing recover retail coloring and order. */
