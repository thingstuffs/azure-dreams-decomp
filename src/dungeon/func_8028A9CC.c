#include "common.h"

typedef struct {
    u8 pad[0x14];
    s16 shift;
    u8 tail[10];
} DungeonInfo;

extern u8 D_800E9FFA[];

void func_8001D9CC(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    s16 *top;
    s16 *bottom;
    register u8 *info_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register DungeonInfo *info ASM_REG("$25");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 value ASM_REG("$11");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s16 arg3_hold;
    s16 x;
    s16 y;
    s16 arg2_late;
    info_page = (u8 *)0x80080000;
    ASM_KEEP_NV(info_page);   /* MATCH pin: load-bearing for the whole function shape */
    info = (DungeonInfo *)(info_page + 0x333c);
    arg3_hold = arg3;
    top = (s16 *)(D_800E9FFA + (((((s16)arg1 - 1) << info->shift) + arg0) * 6));
    top[0] = 0xE;
    value = arg4 + 0x40;
    top[1] = value;
    top[2] = 9;

    top = (s16 *)(D_800E9FFA + 6 + (((((s16)arg1 - 1) << info->shift) + arg2) * 6));
    top[0] = 0xB;
    top[1] = value;
    top[2] = 9;

    top = (s16 *)(D_800E9FFA + ((((arg3_hold << info->shift) + arg0) * 6)));
    top[0] = 0xD;
    top[1] = value;
    top[2] = 9;

    arg2_late = arg2;
    top = (s16 *)(D_800E9FFA + 6 + ((((arg3_hold << info->shift) + arg2) * 6)));
    top[0] = 0xC;
    top[1] = value;
    top[2] = 9;

    top = (s16 *)(D_800E9FFA + 6 + (((((s16)arg1 - 1) << info->shift) + arg0) * 6));
    bottom = (s16 *)(D_800E9FFA + 6 + (((arg3_hold << info->shift) + arg0) * 6));
    x = arg0;
    if (arg0 < arg2) {
        do {
            x++;
            top[0] = 0x12;
            bottom[0] = 0x10;
            bottom[1] = value;
            top[1] = value;
            bottom[2] = 9;
            top[2] = 9;
            top += 3;
            bottom += 3;
        } while (x < arg2);
    }

    y = arg1;
    top = (s16 *)(D_800E9FFA + ((((y << info->shift) + arg0) * 6)));
    bottom = (s16 *)(D_800E9FFA + 6 + ((((y << info->shift) + arg2_late) * 6)));
    ASM_USE_NV(arg3_hold);   /* MATCH pin: load-bearing for the whole function shape */
    if (y < arg3_hold) {
        do {
            y++;
            top[0] = 0x11;
            bottom[0] = 0xF;
            bottom[1] = value;
            top[1] = value;
            bottom[2] = 9;
            top[2] = 9;
            top = (s16 *)((u8 *)top + (6 << info->shift));
            bottom = (s16 *)((u8 *)bottom + (6 << info->shift));
        } while (y < arg3_hold);
    }
}
