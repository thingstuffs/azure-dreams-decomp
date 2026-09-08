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

/* Marks and processes up to ten eligible tiles in each perpendicular direction, returning the total. */
s16 func_800D0DE0(s32 direction, s32 origin_x, s32 origin_y) {
    register s16 *settings = D_8008333C;
    s16 second_stopped = 0;
    s16 first_stopped = 0;
    s16 plus_dir = (direction + 2) & 7;
    s16 minus_dir = (direction - 2) & 7;
    u16 first_count;
    u16 second_count;
    s16 first_x = D_8006CCD8[(s16)direction] + origin_x;
    s16 first_y = D_8006CCE8[(s16)direction] + origin_y;
    s16 second_x = D_8006CCD8[minus_dir] + first_x;
    s16 second_y = D_8006CCE8[minus_dir] + first_y;
    register s32 step = 0;

    first_count = second_count = 0;

    do {
        if (first_x < 0 || first_x >= (1 << settings[10])) {
            first_stopped = 1;
        }
        if (first_y < 0 || first_y >= (1 << settings[11])) {
            first_stopped = 1;
        }
        {
            s32 stopped = first_stopped;
            if (stopped != 0) {
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
                first_x += D_8006CCD8[plus_dir];
                first_y += D_8006CCE8[plus_dir];
                goto check_second;
            }
            first_stopped = 1;
        }

check_second:
        if (second_x < 0 || second_x >= (1 << settings[10])) {
            second_stopped = 1;
        }
        if (second_y < 0 || second_y >= (1 << settings[11])) {
            second_stopped = 1;
        }
        {
            s32 stopped = second_stopped;
            if (stopped != 0) {
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
                second_x += D_8006CCD8[minus_dir];
                second_y += D_8006CCE8[minus_dir];
                goto next_iteration;
            }
            second_stopped = 1;
        }

next_iteration:
        ;
    } while (++step < 10);

    return first_count + second_count;
}
