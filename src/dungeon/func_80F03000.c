#include "common.h"
#include "shared/object_flags.h"

typedef struct GridPoint {
    union {
        s16 x;
        u8 unk_00;
    } unk_00;
    union {
        s16 y;
        u16 unk_02;
        u8 unk_02_u8;
    } unk_02;
} GridPoint;

typedef struct GridData {
    GridPoint point[8];
} GridData __attribute__((packed));

typedef struct S_80F03000_0 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    s16 unk_2E;
    u8 pad_30[4];
    s16 unk_34;
    s16 unk_36;
    u8 pad_38[8];
    void *unk_40;
    u8 pad_44[0x18];
    s8 unk_5C;
    s8 unk_5D;
    u8 pad_5E[0x0E];
    s32 unk_6C;
    s32 unk_70;
    s32 unk_74;
    s32 unk_78;
    s32 unk_7C;
    s32 unk_80;
} S_80F03000_0;

typedef struct S_80F03000_1 {
    union {
        s32 s32;
        struct {
            u8 pad_00[2];
            union { s16 s16; u16 u16; } unk_02;
        } parts;
    } unk_00;
    union {
        s32 s32;
        struct {
            u8 pad_04[2];
            union { s16 s16; u16 u16; } unk_06;
        } parts;
    } unk_04;
    union {
        s32 s32;
        struct {
            s16 unk_08;
            s16 unk_0A;
        } parts;
    } unk_08;
    u8 pad_0C[2];
    s16 unk_0E;
    u8 pad_10[2];
    s16 unk_12;
    u8 pad_14[2];
    s16 unk_16;
} S_80F03000_1;

typedef struct S_80F03000_2 {
    u8 pad_00[6];
    s16 unk_06;
    s32 *unk_08;
    u8 pad_0C[8];
    u16 unk_14;
    u8 pad_16[6];
    u16 unk_1C;
    u16 unk_1E;
} S_80F03000_2;

typedef struct S_80F03000_3 {
    u8 pad_00[0xA4];
    s16 unk_A4;
} S_80F03000_3;

typedef struct S_80F03000_4 {
    u16 unk_00;
} S_80F03000_4;

extern s32 func_800A45D8(u16, u16, s16);
extern s32 func_800A7234(s8, s8, s16, s16 *, s16 *, s16 *);
extern void func_800A7A7C(s16, s16, s16, s32, s8 *);
extern s16 func_800BCB04(s32, s32, s16);

extern u8 D_8014C808[];

/* The module's read-only data comes first (0x8014C800): two entry words, the eight (dx, dy)
 * tile steps at D_8014C808, then this function's switch table and the other functions' tables. */
const u32 module_head[] __asm__("func_8014C800") = {
    0x8014D718, 0x8014D8E0, 0x00000001, 0x00010001,
    0x00010000, 0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFF0000, 0xFFFF0001,
};


void func_8014C8BC(S_80F03000_0 *motion, S_80F03000_1 *position, S_80F03000_2 *display);

/* Updates motion, landing interpolation, and completion of a moving object. */
void func_8014C8BC(S_80F03000_0 *motion, S_80F03000_1 *position, S_80F03000_2 *display)
{
    s8 command[4];
    GridPoint grid[8];
    GridPoint *grid_base;
    s32 fall_height;
    s32 move_height;
    u16 settle_frames;
    u16 scale;
    u32 tile_distance;
    s32 interp_goal;


    __builtin_memcpy(grid, D_8014C808, 32);

settle:
    if (motion->unk_2C == 1) {
        if (motion->unk_2E == 0) {
            motion->unk_2E = (s16)((u16)motion->unk_2E + 1);
            {
                s32 abs_x;
                s32 abs_y;
                s32 map_y;

                abs_x = position->unk_0E;
                abs_y = motion->unk_5C;
                map_y = motion->unk_5D;
                abs_x -= abs_y;
                abs_y = position->unk_12;
                if (abs_x < 0)
                    abs_x = -abs_x;
                abs_y -= map_y;
                if (abs_y < 0)
                    abs_y = -abs_y;
                tile_distance = abs_x + abs_y;
            }
            switch (tile_distance) {
            case 0:
                settle_frames = 4;
                break;
            case 1:
                settle_frames = 8;
                break;
            case 2:
                settle_frames = 12;
                break;
            case 3:
                settle_frames = 14;
                break;
            case 4:
            default:
                settle_frames = 16;
                break;
            }
            motion->unk_36 = settle_frames;
        }
        {
            u32 countdown_raw;
            s32 countdown;
            s32 shifted_countdown;

            countdown_raw = (u16)motion->unk_36 - 1;
            motion->unk_36 = countdown_raw;
            countdown_raw <<= 16;
            shifted_countdown = (s32)countdown_raw;
            countdown = shifted_countdown >> 16;
            if (countdown != 0) {
                s32 interp_current;

                interp_goal = position->unk_0E;
                interp_current = position->unk_00.parts.unk_02.s16;
                interp_goal *= 64;
                interp_current -= 32;
                interp_goal -= interp_current;
                interp_goal /= countdown;
                position->unk_00.parts.unk_02.s16 += interp_goal;

                {
                    s32 goal = position->unk_12;
                    s32 current = position->unk_04.parts.unk_06.s16;
                    s32 ticks = motion->unk_36;
                    s32 delta;
                    s32 scaled = goal;
                    scaled *= 64;
                    delta = current - 32;
                    interp_goal = scaled - delta;
                    interp_goal /= ticks;
                }
                interp_current = position->unk_04.parts.unk_06.u16;
                countdown = position->unk_08.parts.unk_0A;
                interp_current += interp_goal;

                interp_goal = position->unk_16;
                position->unk_04.parts.unk_06.s16 = interp_current;
                interp_goal -= countdown;
                interp_goal /= (s16)motion->unk_36;
                position->unk_08.parts.unk_0A += interp_goal;
            }
        }
        if ((s16)motion->unk_36 <= 0) {
            command[0] = 6;
            command[1] = 12;
            command[2] = 0;
            command[3] = 0;
            func_800A7A7C(position->unk_0E, position->unk_12,
                          position->unk_16, display->unk_08, command);
            ((S_80F03000_3 *)motion->unk_40)->unk_A4 = 0;
            ((S_80F03000_4 *)((u8 *)motion - 2))->unk_00 |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
            return;
        }
        if (display->unk_14 & 0x8000)
            goto settle;
    }
fall:
    if (motion->unk_2C == 2) {
        position->unk_08.s32 += motion->unk_74;
        motion->unk_74 += motion->unk_80;
        scale = display->unk_1E - 0xC8;
        display->unk_1E = scale;
        display->unk_1C = scale;
        fall_height = position->unk_08.parts.unk_0A;
        if (func_800BCB04((motion->unk_5C << 6) & 0xFFC0,
                          (motion->unk_5D << 6) & 0xFFC0,
                          (s16)((u16)position->unk_08.parts.unk_0A - 0x20)) - 7 <
            fall_height) {
            position->unk_08.parts.unk_0A = func_800BCB04(
                (motion->unk_5C << 6) & 0xFFC0,
                (motion->unk_5D << 6) & 0xFFC0,
                (s16)((u16)position->unk_08.parts.unk_0A - 0x20));
            position->unk_08.parts.unk_08 = 0;
            ((S_80F03000_3 *)motion->unk_40)->unk_A4 = 0;
            ((S_80F03000_4 *)((u8 *)motion - 2))->unk_00 |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
            return;
        }
        if (display->unk_14 & 0x8000)
            goto fall;
    }
move:
    grid_base = grid;
    if (motion->unk_2C != 0)
        return;
    position->unk_00.s32 += motion->unk_6C;
    motion->unk_6C += motion->unk_78;
    position->unk_04.s32 += motion->unk_70;
    {
        s32 coord;
        s32 world_coord;
        GridPoint *point;

        coord = motion->unk_70;
        world_coord = motion->unk_7C;
        interp_goal = motion->unk_34;
        interp_goal <<= 2;
        point = (GridPoint *)((u8 *)grid_base + interp_goal);
        interp_goal = motion->unk_5C;
        coord += world_coord;
        motion->unk_70 = coord;

        coord = point->unk_00.x;
        world_coord = position->unk_00.parts.unk_02.s16;
        interp_goal += coord;
        if (world_coord < 0)
            world_coord += 0x3F;
        coord = world_coord >> 6;
        if (interp_goal == coord) {
            coord = point->unk_02.unk_02;
            world_coord = position->unk_04.parts.unk_06.s16;
            interp_goal = motion->unk_5D;
            coord = (s16)coord;
            interp_goal += coord;
            if (world_coord < 0)
                world_coord += 0x3F;
            coord = world_coord >> 6;
            if (interp_goal == coord) {
                if ((func_800A45D8(position->unk_00.parts.unk_02.u16, position->unk_04.parts.unk_06.u16,
                    position->unk_08.parts.unk_0A) << 16) != 0 ||
                    func_800BCB04(position->unk_00.parts.unk_02.u16, position->unk_04.parts.unk_06.u16,
                                      position->unk_08.parts.unk_0A) >= 0x200) {
                    position->unk_00.s32 -= motion->unk_6C;
                    motion->unk_6C = 0;
                    motion->unk_78 = 0;
                    position->unk_04.s32 -= motion->unk_70;
                    motion->unk_70 = 0;
                    motion->unk_7C = 0;
                } else {
                    motion->unk_5C +=
                        ((GridPoint *)((u8 *)grid_base + (motion->unk_34 << 2)))->unk_00.unk_00;
                    motion->unk_5D +=
                        ((GridPoint *)((u8 *)grid_base + (motion->unk_34 << 2)))->unk_02.unk_02_u8;
                }
                display->unk_06 = 0;
            }
        }
    }
    position->unk_08.s32 += motion->unk_74;
    motion->unk_74 += motion->unk_80;
    move_height = position->unk_08.parts.unk_0A;
    if (func_800BCB04((motion->unk_5C << 6) & 0xFFC0, (motion->unk_5D << 6) & 0xFFC0,
        (s16)((u16)position->unk_08.parts.unk_0A - 0x20)) - 0x10 < move_height) {
        position->unk_08.parts.unk_0A = func_800BCB04(
            (motion->unk_5C << 6) & 0xFFC0,
            (motion->unk_5D << 6) & 0xFFC0,
            (s16)((u16)position->unk_08.parts.unk_0A - 0x20));
        position->unk_08.parts.unk_08 = 0;
        motion->unk_7C = 0;
        motion->unk_70 = 0;
        motion->unk_78 = 0;
        motion->unk_6C = 0;
        motion->unk_2C = (s16)((u16)motion->unk_2C + 1);
        if ((func_800A7234(motion->unk_5C, motion->unk_5D,
                           (s16)((u16)position->unk_08.parts.unk_0A - 0x20),
                           &position->unk_0E, &position->unk_12,
                           &position->unk_16) << 16) != 0)
        return;
        motion->unk_2C = 2;
        motion->unk_74 = (s32)0xFFF80000;
        return;
    }
    if (display->unk_14 & 0x8000)
        goto move;
    return;
}

/* The rest of the module's read-only data: the other functions' switch tables. */
static const u32 module_tables[] = {
    0x00000000, 0x8014E0CC, 0x8014E0CC, 0x8014E0CC,
    0x8014E0F8, 0x8014E078, 0x8014E078, 0x8014E078,
    0x8014E024, 0x8014E05C, 0x8014E0F8, 0x8014E0F8,
    0x8014E0BC, 0x8014F55C, 0x8014F5E8, 0x8014F62C,
    0x8014F68C, 0x8014F750, 0x00000000, 0x8014F810,
    0x8014FA48, 0x8014FA90, 0x8014FBE4, 0x8014FBF8,
    0x00000000, 0x8014F8C0, 0x8014F8B8, 0x8014F8B0,
    0x8014F8C8, 0x8014F86C, 0x8014F864, 0x8014F85C,
};
