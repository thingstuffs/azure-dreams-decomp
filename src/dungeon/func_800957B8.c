#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u8 pad0A[0xA];
    s16 height;
} FuncArg1;

extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];
s32 func_8009A350();            /* extern */
void *func_8009B25C();           /* extern */
s32 func_800A0548();                        /* extern */
s16 func_800BCB04();                   /* extern */
extern s8 D_800DD7DC;


typedef struct S_8009AF18_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8009AF18_0;   /* arg2 in func_8009AF18 */

typedef struct S_8009AF18_1 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_8009AF18_1;   /* world in func_8009AF18 */

typedef struct S_8009AF18_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8009AF18_2;   /* temp_v0 in func_8009AF18 */

typedef struct S_8009AF18_3 {
    u8 pad_00[0x124];
    void * unk_124;
} S_8009AF18_3;   /* *(void **)(page + 0x3D7C) in func_8009AF18 */

typedef struct S_8009AF18_4 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_8009AF18_4;   /* ((S_8009AF18_3 *)(*(void **)(page + 0x3D7C)))->unk_124 in func_8009AF18 */

/* Checks successive tiles in a direction and returns the stopping distance. */
s32 func_8009AF18(u32 direction_flags, FuncArg1 *origin, S_8009AF18_0 *start_tile, u16 max_steps) {
    u16 tile_flags;
    s32 direction_index;
    s32 direction;
    s32 height_result;
    s32 check_x;
    s16 step;
    s32 world_y;
    s32 world_x;
    s32 tile_x;
    s32 tile_y;
    S_8009AF18_2 *occupant;

    step = 1;
    D_800DD7DC = 0;
    tile_x = start_tile->unk_24;
    tile_y = start_tile->unk_25;
    direction_index = (direction_flags >> 9) & 7;
    world_x = (tile_x << 6) | 0x20;
    world_y = (tile_y << 6) | 0x20;
    if ((s16)max_steps > 0) {
        direction = direction_index;
        do {
            check_x = (s16) tile_x;
            if (func_800A0548(check_x, (s16) tile_y) != 0) {
                return (s16) (step - 1);
            }
            if ((func_8009A350(check_x, (s16) tile_y, direction, &tile_flags) << 0x10) != 0) {
                tile_x += (u16)dirStepX[direction];
                tile_y += (u16)dirStepY[direction];
                if (tile_flags & 0x3300) {
                    {
                        S_8009AF18_1 *world;

                        world = (S_8009AF18_1 *)D_800E3D7C;
                        occupant = func_8009B25C(world, tile_x & 0xFFFF, tile_y & 0xFFFF, world->unk_88);
                    }
                    if (occupant != NULL) {
                        if (occupant->unk_13 == 0x1F) {
                            if (!(occupant->unk_1C & 0x228)) {
                                if (((S_8009AF18_4 *)(((S_8009AF18_3 *)(void *)D_800E3D7C)->unk_124))->unk_13 < 0) {
                                    D_800DD7DC = 1;
                                    occupant->unk_14 |= 0x800000;
                                }
                            }
                        }
                    }
                    return (s16)step;
                }
                world_x += D_800DCEAC[direction];
                world_y += D_800DCEBC[direction];
                height_result = func_800BCB04(world_x & 0xFFFF, world_y & 0xFFFF, origin->height);
                if (height_result >= 0x200) {
                    return (s16) (step - 1);
                }
            } else {
                return (s16) (step - 1);
            }
            step++;
        } while (step <= (s16)max_steps);
    }
    return (s16)step;
}

