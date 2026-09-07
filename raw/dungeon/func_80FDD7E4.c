#include "common.h"

extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80170EA8;
extern s32 D_80174068;

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_80172FE4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 timer;
    s32 current_x;
    s32 current_y;
    s32 target_x;
    s32 value;
    s32 *state;

    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        func_800AD4D0(arg3);
        FIELD(arg1, s32, 0x0C) =
            -*(s16 *)((u8 *)&D_8006CCD8 +
                      ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 15;
        FIELD(arg1, s32, 0x10) =
            -*(s16 *)((u8 *)&D_8006CCE8 +
                      ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 15;
        FIELD(arg0, u8, 0x9B)++;

        if (FIELD(arg3, u8, 0x28) == 0) {
            goto start_action;
        }
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg0, s16, 0x96) = 0;
            FIELD(arg0, u8, 0x9B) = 2;
            return;
        }
        if (FIELD(arg3, s32, 0x1C) & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        FIELD(arg0, s16, 0x96) = timer;
        FIELD(arg1, s32, 0x0C) -= FIELD(arg1, s32, 0x0C) / 4;
        FIELD(arg1, s32, 0x10) -= FIELD(arg1, s32, 0x10) / 4;
        /* fall through */

    case 1:
        FIELD(arg1, s32, 0x0C) +=
            *(s16 *)((u8 *)&D_8006CCD8 +
                     ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 14;
        {
            register s32 table_offset ASM_REG("$2");
            u8 *table_base;

            table_base = (u8 *)&D_8006CCE8;
            table_offset = (FIELD(arg3, u16, 0x6A) >> 8) & 0xE;
            ASM_KEEP(table_offset);
            FIELD(arg1, s32, 0x10) +=
                *(s16 *)(table_base + table_offset) << 14;
        }
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
        goto start_action;

start_action:
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800AAA54(arg0, arg1, arg2, &D_80174068);
        return;

increment_state:
        FIELD(arg0, s16, 0x96) = 8;
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 2:
        if (FIELD(arg0, s16, 0x96) != 0) {
            target_x = FIELD(arg2, u8, 0x24) << 6;
            current_x = FIELD(arg1, s16, 2) - 0x20;
            current_y = FIELD(arg1, s16, 6) - 0x20;
            FIELD(arg1, s32, 0x0C) =
                ((target_x - current_x) << 15) /
                FIELD(arg0, s16, 0x96);
            FIELD(arg1, s32, 0x10) =
                (((FIELD(arg2, u8, 0x25) << 6) - current_y) << 15) /
                FIELD(arg0, s16, 0x96);
        }
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

        state = &D_80083460;
        value = state[4];
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            state[4] = value & 0x7FFFFFFF;
        }
        FIELD(arg0, void *, 0x8C) = &D_80170EA8;
        return;

    default:
        return;
    }
}
