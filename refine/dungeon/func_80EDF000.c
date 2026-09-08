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

extern u8 D_80170808[];
extern FlagBlock D_800814A0;
extern u32 D_80170828[];
__asm__(".set D_80170828, 0x80170828");

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80170800")
    __attribute__((section(".text.func_80170800"), aligned(4))) = {
    0x80171718, 0x801718E0, 0x00000001, 0x00010001,
    0x00010000, 0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFF0000, 0xFFFF0001, 0x801709E8, 0x801709F0,
    0x801709F8, 0x80170A00, 0x80170A08, 0x00000000,
    0x801720CC, 0x801720CC, 0x801720CC, 0x801720F8,
    0x80172078, 0x80172078, 0x80172078, 0x80172024,
    0x8017205C, 0x801720F8, 0x801720F8, 0x801720BC,
    0x8017355C, 0x801735E8, 0x8017362C, 0x8017368C,
    0x80173750, 0x00000000, 0x80173810, 0x80173A48,
    0x80173A90, 0x80173BE4, 0x80173BF8, 0x00000000,
    0x801738C0, 0x801738B8, 0x801738B0, 0x801738C8,
    0x8017386C, 0x80173864, 0x8017385C,
};
__asm__(".globl func_80170800\n"
        ".size func_80170800, 1752");
#define BODY_NAME func_801708BC
#else
#define BODY_NAME func_80170800
#endif

void BODY_NAME(void *motion, void *position, void *render)
#ifdef __mips__
    __attribute__((section(".text.func_80170800")))
#endif
;

/* Advance motion, resolve tile collisions, and settle at the landing position. */
void BODY_NAME(void *motion, void *position, void *render)
{
    s8 command[4];
    GridPoint tile_steps[8];
    GridPoint *step_table;
    s32 fall_height;
    s32 move_height;
    u16 travel_frames;
    u16 scale;
    u32 tile_distance;

#ifdef __mips__
    static void *const switch_keepalive[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4
    };
#endif

    __builtin_memcpy(tile_steps, D_80170808, 32);

interpolate:
    if (FIELD(motion, s16, 0x2C) != 1)
        goto fall;
    if (FIELD(motion, s16, 0x2E) != 0)
        goto advance_interpolation;
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
        goto max_travel_time;
    goto *(void *)D_80170828[tile_distance];
case_0:
    travel_frames = 4;
    goto set_travel_time;
case_1:
    travel_frames = 8;
    goto set_travel_time;
case_2:
    travel_frames = 12;
    goto set_travel_time;
case_3:
    travel_frames = 14;
    goto set_travel_time;
case_4:
max_travel_time:
    travel_frames = 16;
set_travel_time:
    FIELD(motion, s16, 0x36) = travel_frames;
advance_interpolation:
    {
        u32 countdown_raw;
        s32 countdown;
        s32 shifted_countdown;

        countdown_raw = (u16)FIELD(motion, s16, 0x36) - 1;
        FIELD(motion, s16, 0x36) = countdown_raw;
        ASM_KEEP(countdown_raw);   /* MATCH pin: retail delay-slot fill depends on it */
        shifted_countdown = (s32)(countdown_raw << 16);
        countdown = shifted_countdown >> 16;
        if (countdown == 0)
            goto check_arrival;
        {
            register s32 interp_goal ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
            s32 interp_current;

            interp_goal = FIELD(position, s16, 0x0E);
            ASM_KEEP(interp_goal);   /* MATCH pin: retail schedule: same instructions, different order without it */
            interp_current = FIELD(position, s16, 2) - 32;
            interp_goal =
                (interp_goal * 64 - interp_current) / countdown;
            FIELD(position, s16, 2) += interp_goal;

            interp_goal = FIELD(position, s16, 0x12);
            ASM_KEEP(interp_goal);   /* MATCH pin: retail schedule: same instructions, different order without it */
            interp_current = FIELD(position, s16, 6);
            countdown = FIELD(motion, s16, 0x36);
            ASM_KEEP(countdown);   /* MATCH pin: retail schedule: same instructions, different order without it */
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
check_arrival:
    if ((s16)FIELD(motion, s16, 0x36) > 0)
        goto repeat_interpolation;
    command[0] = 6;
    command[1] = 12;
    command[2] = 0;
    command[3] = 0;
    func_800A7A7C(FIELD(position, s16, 0x0E), FIELD(position, s16, 0x12),
                  FIELD(position, s16, 0x16), FIELD(render, s32 *, 8), command);
    goto finish_motion;
repeat_interpolation:
    if (FIELD(render, u16, 0x14) & 0x8000)
        goto interpolate;

fall:
    if (FIELD(motion, s16, 0x2C) != 2)
        goto move;
    FIELD(position, s32, 8) += FIELD(motion, s32, 0x74);
    FIELD(motion, s32, 0x74) += FIELD(motion, s32, 0x80);
    scale = FIELD(render, u16, 0x1E) - 0xC8;
    FIELD(render, u16, 0x1E) = scale;
    FIELD(render, u16, 0x1C) = scale;
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
finish_motion:
    FIELD(FIELD(motion, void **, 0x40), s16, 0xA4) = 0;
    FIELD(motion, u16, -2) |= 0x8000;
    D_800814A0.value |= 0x8000;
    goto epilogue;
repeat_fall:
    if (FIELD(render, u16, 0x14) & 0x8000)
        goto fall;

move:
    step_table = tile_steps;
    if (FIELD(motion, s16, 0x2C) != 0)
        goto epilogue;
    FIELD(position, s32, 0) += FIELD(motion, s32, 0x6C);
    FIELD(motion, s32, 0x6C) += FIELD(motion, s32, 0x78);
    FIELD(position, s32, 4) += FIELD(motion, s32, 0x70);
    {
        s32 coord;
        register s32 next_tile ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
        s32 world_coord;
        GridPoint *step;

        coord = FIELD(motion, s32, 0x70);
        next_tile = FIELD(motion, s16, 0x34);
        ASM_KEEP(next_tile);   /* MATCH pin: load-bearing for the whole function shape */
        world_coord = FIELD(motion, s32, 0x7C);
        ASM_KEEP(world_coord);   /* MATCH pin: load-bearing for the whole function shape */
        step = &step_table[next_tile];
        ASM_KEEP(step);   /* MATCH pin: load-bearing for the whole function shape */
        next_tile = FIELD(motion, s8, 0x5C);
        coord += world_coord;
        FIELD(motion, s32, 0x70) = coord;

        coord = step->x;
        world_coord = FIELD(position, s16, 2);
        next_tile += coord;
        if (world_coord < 0)
            world_coord += 0x3F;
        coord = world_coord >> 6;
        if (next_tile != coord)
            goto update_height;

        coord = FIELD(step, u16, 2);
        world_coord = FIELD(position, s16, 6);
        next_tile = FIELD(motion, s8, 0x5D);
        ASM_KEEP(next_tile);   /* MATCH pin: load-bearing for the whole function shape */
        coord = (s16)coord;
        next_tile += coord;
        if (world_coord < 0)
            world_coord += 0x3F;
        coord = world_coord >> 6;
        if (next_tile != coord)
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
    goto clear_direction;
advance_tile:
    FIELD(motion, s8, 0x5C) +=
        FIELD((u8 *)step_table + (FIELD(motion, s16, 0x34) << 2), u8, 0);
    FIELD(motion, s8, 0x5D) +=
        FIELD((u8 *)step_table + (FIELD(motion, s16, 0x34) << 2), u8, 2);
clear_direction:
    FIELD(render, s16, 6) = 0;
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
    if (FIELD(render, u16, 0x14) & 0x8000)
        goto move;
epilogue:
    return;
}
