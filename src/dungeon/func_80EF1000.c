#include "common.h"

typedef struct GridPoint {
    union {
        s16 x;
        u8 unk_00;
    } unk_00;
    union {
        s16 y;
        u16 unk_02;
        u8 unk_00;
    } unk_02;
} GridPoint;

typedef struct GridData {
    GridPoint point[8];
} GridData __attribute__((packed));

typedef struct FlagBlock {
    s32 value;
    s32 pad[2];
} FlagBlock;

typedef struct S_func_80EF1000_1 {
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
} S_func_80EF1000_1;

typedef struct S_func_80EF1000_2 {
    union {
        s32 unk_00;
        struct {
            u8 pad_00[2];
            union {
                s16 s;
                u16 u;
            } unk_02;
        } half;
    } unk_00;
    union {
        s32 unk_04;
        struct {
            u8 pad_04[2];
            union {
                s16 s;
                u16 u;
            } unk_06;
        } half;
    } unk_04;
    union {
        s32 unk_08;
        struct {
            s16 unk_08;
            s16 unk_0A;
        } half;
    } unk_08;
    u8 pad_0C[2];
    s16 unk_0E;
    u8 pad_10[2];
    s16 unk_12;
    u8 pad_14[2];
    s16 unk_16;
} S_func_80EF1000_2;

typedef struct S_func_80EF1000_3 {
    u8 pad_00[6];
    s16 unk_06;
    void *unk_08;
    u8 pad_0C[8];
    u16 unk_14;
    u8 pad_16[6];
    u16 unk_1C;
    u16 unk_1E;
} S_func_80EF1000_3;

typedef struct S_func_80EF1000_4 {
    u8 pad_00[0xA4];
    s16 unk_A4;
} S_func_80EF1000_4;

typedef struct S_func_80EF1000_5 {
    u16 unk_00;
} S_func_80EF1000_5;

extern s32 func_800A45D8(u16, u16, s16);
extern s32 func_800A7234(s8, s8, s16, s16 *, s16 *, s16 *);
extern void func_800A7A7C(s16, s16, s16, s32, s8 *);
extern s16 func_800BCB04(s32, s32, s16);

extern u8 D_8015E808[];
extern FlagBlock D_800814A0;
extern u32 D_8015E828[];
__asm__(".set D_8015E828, 0x8015E828");

#ifdef __mips__
static const u32 bank_words[] __asm__("func_8015E800")
    __attribute__((section(".text.func_8015E800"), aligned(4))) = {
    0x8015F718, 0x8015F8E0, 0x00000001, 0x00010001,
    0x00010000, 0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFF0000, 0xFFFF0001, 0x8015E9E8, 0x8015E9F0,
    0x8015E9F8, 0x8015EA00, 0x8015EA08, 0x00000000,
    0x801600CC, 0x801600CC, 0x801600CC, 0x801600F8,
    0x80160078, 0x80160078, 0x80160078, 0x80160024,
    0x8016005C, 0x801600F8, 0x801600F8, 0x801600BC,
    0x8016155C, 0x801615E8, 0x8016162C, 0x8016168C,
    0x80161750, 0x00000000, 0x80161810, 0x80161A48,
    0x80161A90, 0x80161BE4, 0x80161BF8, 0x00000000,
    0x801618C0, 0x801618B8, 0x801618B0, 0x801618C8,
    0x8016186C, 0x80161864, 0x8016185C,
};
__asm__(".globl func_8015E800\n"
        ".size func_8015E800, 1752");
#define BODY_NAME func_8015E8BC
#else
#define BODY_NAME func_8015E800
#endif

void BODY_NAME(S_func_80EF1000_1 *motion, S_func_80EF1000_2 *position, S_func_80EF1000_3 *sprite)
#ifdef __mips__
    __attribute__((section(".text.func_8015E800")))
#endif
;

/* Update flight, landing interpolation, and falling motion until completion. */
void BODY_NAME(S_func_80EF1000_1 *motion, S_func_80EF1000_2 *position, S_func_80EF1000_3 *sprite)
{
    s8 command[4];
    GridPoint grid[8];
    GridPoint *grid_base;
    s32 fall_height;
    s32 flight_height;
    u16 travel_frames;
    u16 shrink_scale;
    u32 tile_distance;

#ifdef __mips__
    static void *const switch_keepalive[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4
    };
#endif

    __builtin_memcpy(grid, D_8015E808, 32);

update_travel:
    if (motion->unk_2C != 1)
        goto update_fall;
    if (motion->unk_2E != 0)
        goto interpolate_position;
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
    if (tile_distance >= 5U)
        goto long_travel;
    goto *(void *)D_8015E828[tile_distance];
case_0:
    travel_frames = 4;
    goto set_travel_frames;
case_1:
    travel_frames = 8;
    goto set_travel_frames;
case_2:
    travel_frames = 12;
    goto set_travel_frames;
case_3:
    travel_frames = 14;
    goto set_travel_frames;
case_4:
long_travel:
    travel_frames = 16;
set_travel_frames:
    motion->unk_36 = travel_frames;
interpolate_position:
    {
        u32 countdown_raw;
        s32 countdown;
        s32 shifted_countdown;

        countdown_raw = (u16)motion->unk_36 - 1;
        motion->unk_36 = countdown_raw;
        ASM_KEEP(countdown_raw);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        shifted_countdown = (s32)(countdown_raw << 16);
        countdown = shifted_countdown >> 16;
        if (countdown == 0)
            goto check_arrival;
        {
            register s32 interp_goal ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            s32 interp_current;

            interp_goal = position->unk_0E;
            ASM_KEEP(interp_goal);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            interp_current = position->unk_00.half.unk_02.s - 32;
            interp_goal =
                (interp_goal * 64 - interp_current) / countdown;
            position->unk_00.half.unk_02.s += interp_goal;

            interp_goal = position->unk_12;
            ASM_KEEP(interp_goal);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            interp_current = position->unk_04.half.unk_06.s;
            countdown = motion->unk_36;
            ASM_KEEP(countdown);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            interp_goal = interp_goal * 64;
            interp_current -= 32;
            interp_goal -= interp_current;
            interp_goal /= countdown;

            interp_current = position->unk_04.half.unk_06.u;
            countdown = position->unk_08.half.unk_0A;
            interp_current += interp_goal;

            interp_goal = position->unk_16;
            position->unk_04.half.unk_06.s = interp_current;
            interp_goal = (interp_goal - countdown) /
                (s16)motion->unk_36;
            position->unk_08.half.unk_0A += interp_goal;
        }
    }
check_arrival:
    if ((s16)motion->unk_36 > 0)
        goto repeat_travel;
    command[0] = 6;
    command[1] = 12;
    command[2] = 0;
    command[3] = 0;
    func_800A7A7C(position->unk_0E, position->unk_12,
                  position->unk_16, sprite->unk_08, command);
    goto finish_motion;
repeat_travel:
    if (sprite->unk_14 & 0x8000)
        goto update_travel;

update_fall:
    if (motion->unk_2C != 2)
        goto update_flight;
    position->unk_08.unk_08 += motion->unk_74;
    motion->unk_74 += motion->unk_80;
    shrink_scale = sprite->unk_1E - 0xC8;
    sprite->unk_1E = shrink_scale;
    sprite->unk_1C = shrink_scale;
    fall_height = position->unk_08.half.unk_0A;
    if (func_800BCB04((motion->unk_5C << 6) & 0xFFC0,
                      (motion->unk_5D << 6) & 0xFFC0,
                      (s16)((u16)position->unk_08.half.unk_0A - 0x20)) - 7 >=
        fall_height)
        goto repeat_fall;
    position->unk_08.half.unk_0A = func_800BCB04(
        (motion->unk_5C << 6) & 0xFFC0,
        (motion->unk_5D << 6) & 0xFFC0,
        (s16)((u16)position->unk_08.half.unk_0A - 0x20));
    position->unk_08.half.unk_08 = 0;
finish_motion:
    ((S_func_80EF1000_4 *)motion->unk_40)->unk_A4 = 0;
    ((S_func_80EF1000_5 *)((u8 *)motion - 2))->unk_00 |= 0x8000;
    D_800814A0.value |= 0x8000;
    goto epilogue;
repeat_fall:
    if (sprite->unk_14 & 0x8000)
        goto update_fall;

update_flight:
    grid_base = grid;
    if (motion->unk_2C != 0)
        goto epilogue;
    position->unk_00.unk_00 += motion->unk_6C;
    motion->unk_6C += motion->unk_78;
    position->unk_04.unk_04 += motion->unk_70;
    {
        s32 coord;
        register s32 map_sum ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        s32 rounded;
        GridPoint *point;

        coord = motion->unk_70;
        map_sum = motion->unk_34;
        ASM_KEEP(map_sum);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        rounded = motion->unk_7C;
        ASM_KEEP(rounded);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        point = &grid_base[map_sum];
        ASM_KEEP(point);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        map_sum = motion->unk_5C;
        coord += rounded;
        motion->unk_70 = coord;

        coord = point->unk_00.x;
        rounded = position->unk_00.half.unk_02.s;
        map_sum += coord;
        if (rounded < 0)
            rounded += 0x3F;
        coord = rounded >> 6;
        if (map_sum != coord)
            goto update_height;

        coord = point->unk_02.unk_02;
        rounded = position->unk_04.half.unk_06.s;
        map_sum = motion->unk_5D;
        ASM_KEEP(map_sum);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        coord = (s16)coord;
        map_sum += coord;
        if (rounded < 0)
            rounded += 0x3F;
        coord = rounded >> 6;
        if (map_sum != coord)
            goto update_height;
    }
    if ((func_800A45D8(position->unk_00.half.unk_02.u, position->unk_04.half.unk_06.u,
                       position->unk_08.half.unk_0A) << 16) != 0)
        goto stop_horizontal;
    if (func_800BCB04(position->unk_00.half.unk_02.u, position->unk_04.half.unk_06.u,
                      position->unk_08.half.unk_0A) < 0x200)
        goto advance_tile;
stop_horizontal:
    position->unk_00.unk_00 -= motion->unk_6C;
    motion->unk_6C = 0;
    motion->unk_78 = 0;
    position->unk_04.unk_04 -= motion->unk_70;
    motion->unk_70 = 0;
    motion->unk_7C = 0;
    goto clear_sprite_motion;
advance_tile:
    motion->unk_5C +=
        ((GridPoint *)((u8 *)grid_base + (motion->unk_34 << 2)))->unk_00.unk_00;
    motion->unk_5D +=
        ((GridPoint *)((u8 *)grid_base + (motion->unk_34 << 2)))->unk_02.unk_00;
clear_sprite_motion:
    sprite->unk_06 = 0;
update_height:
    position->unk_08.unk_08 += motion->unk_74;
    motion->unk_74 += motion->unk_80;
    flight_height = position->unk_08.half.unk_0A;
    if (func_800BCB04((motion->unk_5C << 6) & 0xFFC0,
                      (motion->unk_5D << 6) & 0xFFC0,
                      (s16)((u16)position->unk_08.half.unk_0A - 0x20)) - 0x10 >=
        flight_height)
        goto repeat_flight;
    position->unk_08.half.unk_0A = func_800BCB04(
        (motion->unk_5C << 6) & 0xFFC0,
        (motion->unk_5D << 6) & 0xFFC0,
        (s16)((u16)position->unk_08.half.unk_0A - 0x20));
    position->unk_08.half.unk_08 = 0;
    motion->unk_7C = 0;
    motion->unk_70 = 0;
    motion->unk_78 = 0;
    motion->unk_6C = 0;
    motion->unk_2C = (s16)((u16)motion->unk_2C + 1);
    if ((func_800A7234(motion->unk_5C, motion->unk_5D,
                       (s16)((u16)position->unk_08.half.unk_0A - 0x20),
                       &position->unk_0E, &position->unk_12,
                       &position->unk_16) << 16) != 0)
        goto epilogue;
    motion->unk_2C = 2;
    motion->unk_74 = (s32)0xFFF80000;
    goto epilogue;
repeat_flight:
    if (sprite->unk_14 & 0x8000)
        goto update_flight;
epilogue:
    return;
}
