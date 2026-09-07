#include "common.h"

typedef struct {
    u8 pad[4];
    u16 flags;
} DungeonTile;

extern u16 D_8006CCD8[8];
extern u16 D_8006CCE8[8];
extern s16 D_8008333C[16];
extern DungeonTile D_800EA000[2];

extern s16 func_800D0FBC(void);
extern s16 func_800D10D0(void);
extern s32 func_800D169C(u16, u16, s16, u16);
extern s16 func_800D175C(s16, s16);

s16 func_800D0DE0(s32 arg0, s32 arg1, s32 arg2) {
    register s16 *settings = D_8008333C;
    s16 second_bad = 0;
    s16 first_bad = 0;
    s16 index_plus = (arg0 + 2) & 7;
    s16 index_minus = (arg0 - 2) & 7;
    u16 first_count;
    u16 second_count;
    s16 first_x = D_8006CCD8[(s16)arg0] + arg1;
    s16 first_y = D_8006CCE8[(s16)arg0] + arg2;
    s16 second_x = D_8006CCD8[index_minus] + first_x;
    s16 second_y = D_8006CCE8[index_minus] + first_y;
    register s32 iteration = 0;

    first_count = second_count = 0;

    do {
        if (first_x < 0 || first_x >= (1 << settings[10])) {
            first_bad = 1;
        }
        if (first_y < 0 || first_y >= (1 << settings[11])) {
            first_bad = 1;
        }
        {
            s32 bad = first_bad;
            ASM_KEEP_NV(bad);
            if (bad != 0) {
                goto check_second;
            }
        }
        {
            DungeonTile *tile = &D_800EA000[first_x + (first_y << settings[10])];
            if (tile->flags & 4) {
                first_count++;
                tile->flags |= 0x80;
                func_800D169C((u16)first_x, (u16)first_y,
                              func_800D175C(first_x, first_y),
                              tile->flags & 8);
                ASM_MEM_BARRIER();
                first_x += D_8006CCD8[index_plus];
                first_y += D_8006CCE8[index_plus];
                goto check_second;
            }
            first_bad = 1;
        }

check_second:
        if (second_x < 0 || second_x >= (1 << settings[10])) {
            second_bad = 1;
        }
        if (second_y < 0 || second_y >= (1 << settings[11])) {
            second_bad = 1;
        }
        {
            s32 bad = second_bad;
            ASM_KEEP_NV(bad);
            if (bad != 0) {
                goto next_iteration;
            }
        }
        {
            DungeonTile *tile = &D_800EA000[second_x + (second_y << settings[10])];
            if (tile->flags & 4) {
                second_count++;
                tile->flags |= 0x80;
                func_800D169C((u16)second_x, (u16)second_y,
                              func_800D175C(second_x, second_y),
                              tile->flags & 8);
                ASM_MEM_BARRIER();
                second_x += D_8006CCD8[index_minus];
                second_y += D_8006CCE8[index_minus];
                goto next_iteration;
            }
            second_bad = 1;
        }

next_iteration:
        ;
    } while (++iteration < 10);

    return first_count + second_count;
}
