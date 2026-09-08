#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct GridPoint {
    s16 x;
    s16 y;
} GridPoint;

typedef struct GridData {
    GridPoint point[8];
} GridData __attribute__((packed));

typedef struct FlagBlock {
    s32 value;
    s32 pad[2];
} FlagBlock;

extern s32 func_800A45D8(u16, u16, s16);
extern s32 func_800A7234(s8, s8, s16, s16 *, s16 *, s16 *);
extern void func_800A7A7C(s16, s16, s16, s32, s8 *);
extern s16 func_800BCB04(s32, s32, s16);

extern u8 D_8016A808[];
extern FlagBlock D_800814A0;
extern u32 D_8016A828[];
__asm__(".set D_8016A828, 0x8016A828");

#ifdef __mips__
static const u32 bank_words[] __asm__("func_8016A800")
    __attribute__((section(".text.func_8016A800"), aligned(4))) = {
    0x8016B718, 0x8016B8E0, 0x00000001, 0x00010001,
    0x00010000, 0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFF0000, 0xFFFF0001, 0x8016A9E8, 0x8016A9F0,
    0x8016A9F8, 0x8016AA00, 0x8016AA08, 0x00000000,
    0x8016C0CC, 0x8016C0CC, 0x8016C0CC, 0x8016C0F8,
    0x8016C078, 0x8016C078, 0x8016C078, 0x8016C024,
    0x8016C05C, 0x8016C0F8, 0x8016C0F8, 0x8016C0BC,
    0x8016D55C, 0x8016D5E8, 0x8016D62C, 0x8016D68C,
    0x8016D750, 0x00000000, 0x8016D810, 0x8016DA48,
    0x8016DA90, 0x8016DBE4, 0x8016DBF8, 0x00000000,
    0x8016D8C0, 0x8016D8B8, 0x8016D8B0, 0x8016D8C8,
    0x8016D86C, 0x8016D864, 0x8016D85C,
};
__asm__(".globl func_8016A800\n"
        ".size func_8016A800, 1752");
#define BODY_NAME func_8016A8BC
#else
#define BODY_NAME func_8016A800
#endif

void BODY_NAME(void *motion, void *position, void *display)
#ifdef __mips__
    __attribute__((section(".text.func_8016A800")))
#endif
;

/* Updates motion, landing interpolation, and completion of a moving object. */
void BODY_NAME(void *motion, void *position, void *display)
{
    s8 command[4];
    GridPoint grid[8];
    GridPoint *grid_base;
    s32 fall_height;
    s32 move_height;
    u16 settle_frames;
    u16 scale;
    u32 tile_distance;

#ifdef __mips__
    static void *const switch_keepalive[] __attribute__((used)) = {
        &&distance_zero, &&distance_one, &&distance_two, &&distance_three, &&distance_four
    };
#endif

    __builtin_memcpy(grid, D_8016A808, 32);

settle:
    if (FIELD(motion, s16, 0x2C) != 1)
        goto fall;
    if (FIELD(motion, s16, 0x2E) != 0)
        goto interpolate;
    FIELD(motion, s16, 0x2E) = (s16)((u16)FIELD(motion, s16, 0x2E) + 1);
    {
        s32 abs_x;
        s32 abs_y;
        s32 map_y;

        abs_x = FIELD(position, s16, 0x0E);
        abs_y = FIELD(motion, s8, 0x5C);
        map_y = FIELD(motion, s8, 0x5D);
        abs_x -= abs_y;
        abs_y = FIELD(position, s16, 0x12);
        if (abs_x < 0)
            abs_x = -abs_x;
        abs_y -= map_y;
        if (abs_y < 0)
            abs_y = -abs_y;
        tile_distance = abs_x + abs_y;
    }
    if (tile_distance >= 5U)
        goto max_duration;
    goto *(void *)D_8016A828[tile_distance];
distance_zero:
    settle_frames = 4;
    goto set_duration;
distance_one:
    settle_frames = 8;
    goto set_duration;
distance_two:
    settle_frames = 12;
    goto set_duration;
distance_three:
    settle_frames = 14;
    goto set_duration;
distance_four:
max_duration:
    settle_frames = 16;
set_duration:
    FIELD(motion, s16, 0x36) = settle_frames;
interpolate:
    {
        u32 countdown_raw;
        s32 countdown;
        s32 shifted_countdown;

        countdown_raw = (u16)FIELD(motion, s16, 0x36) - 1;
        FIELD(motion, s16, 0x36) = countdown_raw;
        ASM_KEEP(countdown_raw);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        shifted_countdown = (s32)(countdown_raw << 16);
        countdown = shifted_countdown >> 16;
        if (countdown == 0)
            goto check_settled;
        {
            register s32 interp_goal ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            s32 interp_current;

            interp_goal = FIELD(position, s16, 0x0E);
            ASM_KEEP(interp_goal);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            interp_current = FIELD(position, s16, 2) - 32;
            interp_goal =
                (interp_goal * 64 - interp_current) / countdown;
            FIELD(position, s16, 2) += interp_goal;

            interp_goal = FIELD(position, s16, 0x12);
            ASM_KEEP(interp_goal);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            interp_current = FIELD(position, s16, 6);
            countdown = FIELD(motion, s16, 0x36);
            ASM_KEEP(countdown);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            interp_goal = interp_goal * 64;
            interp_current -= 32;
            interp_goal -= interp_current;
            interp_goal /= countdown;

            interp_current = FIELD(position, u16, 6);
            countdown = FIELD(position, s16, 0x0A);
            interp_current += interp_goal;

            interp_goal = FIELD(position, s16, 0x16);
            FIELD(position, s16, 6) = interp_current;
            interp_goal = (interp_goal - countdown) /
                (s16)FIELD(motion, s16, 0x36);
            FIELD(position, s16, 0x0A) += interp_goal;
        }
    }
check_settled:
    if ((s16)FIELD(motion, s16, 0x36) > 0)
        goto repeat_settle;
    command[0] = 6;
    command[1] = 12;
    command[2] = 0;
    command[3] = 0;
    func_800A7A7C(FIELD(position, s16, 0x0E), FIELD(position, s16, 0x12),
                  FIELD(position, s16, 0x16), FIELD(display, s32 *, 8), command);
    goto finish;
repeat_settle:
    if (FIELD(display, u16, 0x14) & 0x8000)
        goto settle;

fall:
    if (FIELD(motion, s16, 0x2C) != 2)
        goto move;
    FIELD(position, s32, 8) += FIELD(motion, s32, 0x74);
    FIELD(motion, s32, 0x74) += FIELD(motion, s32, 0x80);
    scale = FIELD(display, u16, 0x1E) - 0xC8;
    FIELD(display, u16, 0x1E) = scale;
    FIELD(display, u16, 0x1C) = scale;
    fall_height = FIELD(position, s16, 0x0A);
    if (func_800BCB04((FIELD(motion, s8, 0x5C) << 6) & 0xFFC0,
                      (FIELD(motion, s8, 0x5D) << 6) & 0xFFC0,
                      (s16)((u16)FIELD(position, s16, 0x0A) - 0x20)) - 7 >=
        fall_height)
        goto repeat_fall;
    FIELD(position, s16, 0x0A) = func_800BCB04(
        (FIELD(motion, s8, 0x5C) << 6) & 0xFFC0,
        (FIELD(motion, s8, 0x5D) << 6) & 0xFFC0,
        (s16)((u16)FIELD(position, s16, 0x0A) - 0x20));
    FIELD(position, s16, 8) = 0;
finish:
    FIELD(FIELD(motion, void **, 0x40), s16, 0xA4) = 0;
    FIELD(motion, u16, -2) |= 0x8000;
    D_800814A0.value |= 0x8000;
    goto epilogue;
repeat_fall:
    if (FIELD(display, u16, 0x14) & 0x8000)
        goto fall;

move:
    grid_base = grid;
    if (FIELD(motion, s16, 0x2C) != 0)
        goto epilogue;
    FIELD(position, s32, 0) += FIELD(motion, s32, 0x6C);
    FIELD(motion, s32, 0x6C) += FIELD(motion, s32, 0x78);
    FIELD(position, s32, 4) += FIELD(motion, s32, 0x70);
    {
        s32 coord;
        register s32 map_sum ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        s32 rounded;
        GridPoint *point;

        coord = FIELD(motion, s32, 0x70);
        map_sum = FIELD(motion, s16, 0x34);
        ASM_KEEP(map_sum);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        rounded = FIELD(motion, s32, 0x7C);
        ASM_KEEP(rounded);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        point = &grid_base[map_sum];
        ASM_KEEP(point);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        map_sum = FIELD(motion, s8, 0x5C);
        coord += rounded;
        FIELD(motion, s32, 0x70) = coord;

        coord = point->x;
        rounded = FIELD(position, s16, 2);
        map_sum += coord;
        if (rounded < 0)
            rounded += 0x3F;
        coord = rounded >> 6;
        if (map_sum != coord)
            goto update_height;

        coord = FIELD(point, u16, 2);
        rounded = FIELD(position, s16, 6);
        map_sum = FIELD(motion, s8, 0x5D);
        ASM_KEEP(map_sum);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        coord = (s16)coord;
        map_sum += coord;
        if (rounded < 0)
            rounded += 0x3F;
        coord = rounded >> 6;
        if (map_sum != coord)
            goto update_height;
    }
    if ((func_800A45D8(FIELD(position, u16, 2), FIELD(position, u16, 6),
                       FIELD(position, s16, 0x0A)) << 16) != 0)
        goto stop_horizontal;
    if (func_800BCB04(FIELD(position, u16, 2), FIELD(position, u16, 6),
                      FIELD(position, s16, 0x0A)) < 0x200)
        goto advance_tile;
stop_horizontal:
    FIELD(position, s32, 0) -= FIELD(motion, s32, 0x6C);
    FIELD(motion, s32, 0x6C) = 0;
    FIELD(motion, s32, 0x78) = 0;
    FIELD(position, s32, 4) -= FIELD(motion, s32, 0x70);
    FIELD(motion, s32, 0x70) = 0;
    FIELD(motion, s32, 0x7C) = 0;
    goto clear_movement;
advance_tile:
    FIELD(motion, s8, 0x5C) +=
        FIELD((u8 *)grid_base + (FIELD(motion, s16, 0x34) << 2), u8, 0);
    FIELD(motion, s8, 0x5D) +=
        FIELD((u8 *)grid_base + (FIELD(motion, s16, 0x34) << 2), u8, 2);
clear_movement:
    FIELD(display, s16, 6) = 0;
update_height:
    FIELD(position, s32, 8) += FIELD(motion, s32, 0x74);
    FIELD(motion, s32, 0x74) += FIELD(motion, s32, 0x80);
    move_height = FIELD(position, s16, 0x0A);
    if (func_800BCB04((FIELD(motion, s8, 0x5C) << 6) & 0xFFC0,
                      (FIELD(motion, s8, 0x5D) << 6) & 0xFFC0,
                      (s16)((u16)FIELD(position, s16, 0x0A) - 0x20)) - 0x10 >=
        move_height)
        goto repeat_move;
    FIELD(position, s16, 0x0A) = func_800BCB04(
        (FIELD(motion, s8, 0x5C) << 6) & 0xFFC0,
        (FIELD(motion, s8, 0x5D) << 6) & 0xFFC0,
        (s16)((u16)FIELD(position, s16, 0x0A) - 0x20));
    FIELD(position, s16, 8) = 0;
    FIELD(motion, s32, 0x7C) = 0;
    FIELD(motion, s32, 0x70) = 0;
    FIELD(motion, s32, 0x78) = 0;
    FIELD(motion, s32, 0x6C) = 0;
    FIELD(motion, s16, 0x2C) = (s16)((u16)FIELD(motion, s16, 0x2C) + 1);
    if ((func_800A7234(FIELD(motion, s8, 0x5C), FIELD(motion, s8, 0x5D),
                       (s16)((u16)FIELD(position, s16, 0x0A) - 0x20),
                       &FIELD(position, s16, 0x0E), &FIELD(position, s16, 0x12),
                       &FIELD(position, s16, 0x16)) << 16) != 0)
        goto epilogue;
    FIELD(motion, s16, 0x2C) = 2;
    FIELD(motion, s32, 0x74) = (s32)0xFFF80000;
    goto epilogue;
repeat_move:
    if (FIELD(display, u16, 0x14) & 0x8000)
        goto move;
epilogue:
    return;
}
