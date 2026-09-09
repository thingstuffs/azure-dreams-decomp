#include "common.h"

typedef struct GridPoint {
    union {
        s16 unk_00;
        u8 unk_00_u8;
    } x;
    union {
        s16 unk_02;
        u16 unk_02_u16;
        u8 unk_02_u8;
    } y;
} GridPoint;

typedef struct GridData {
    GridPoint point[8];
} GridData __attribute__((packed));

typedef struct FlagBlock {
    s32 value;
    s32 pad[2];
} FlagBlock;

typedef struct S_func_80EF7000_1 {
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
} S_func_80EF7000_1;

typedef struct S_func_80EF7000_2 {
    union {
        s32 unk_00;
        struct {
            u8 pad_00[2];
            union {
                s16 unk_02;
                u16 unk_02_u16;
            } unk_02;
        } half;
    } unk_00;
    union {
        s32 unk_04;
        struct {
            u8 pad_04[2];
            union {
                s16 unk_06;
                u16 unk_06_u16;
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
} S_func_80EF7000_2;

typedef struct S_func_80EF7000_3 {
    u8 pad_00[6];
    s16 unk_06;
    void *unk_08;
    u8 pad_0C[8];
    u16 unk_14;
    u8 pad_16[6];
    u16 unk_1C;
    u16 unk_1E;
} S_func_80EF7000_3;

typedef struct S_func_80EF7000_4 {
    u8 pad_00[0xA4];
    s16 unk_A4;
} S_func_80EF7000_4;

typedef struct S_func_80EF7000_5 {
    u16 unk_00;
} S_func_80EF7000_5;

extern s32 func_800A45D8(u16, u16, s16);
extern s32 func_800A7234(s8, s8, s16, s16 *, s16 *, s16 *);
extern void func_800A7A7C(s16, s16, s16, s32, s8 *);
extern s16 func_800BCB04(s32, s32, s16);

extern u8 D_80158808[];
extern FlagBlock D_800814A0;
extern u32 D_80158828[];
__asm__(".set D_80158828, 0x80158828");

#ifdef __mips__
static const u32 data_prefix[] __asm__("func_80158800")
    __attribute__((section(".text.func_80158800"), aligned(4))) = {
    0x80159718, 0x801598E0,
    0x00000001, 0x00010001, 0x00010000, 0x0001FFFF,
    0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001,
    0x801589E8, 0x801589F0, 0x801589F8, 0x80158A00, 0x80158A08,
    0x00000000,
    0x8015A0CC, 0x8015A0CC, 0x8015A0CC, 0x8015A0F8,
    0x8015A078, 0x8015A078, 0x8015A078, 0x8015A024,
    0x8015A05C, 0x8015A0F8, 0x8015A0F8, 0x8015A0BC,
    0x8015B55C, 0x8015B5E8, 0x8015B62C, 0x8015B68C, 0x8015B750,
    0x00000000,
    0x8015B810, 0x8015BA48, 0x8015BA90, 0x8015BBE4, 0x8015BBF8,
    0x00000000,
    0x8015B8C0, 0x8015B8B8, 0x8015B8B0, 0x8015B8C8,
    0x8015B86C, 0x8015B864, 0x8015B85C,
};
__asm__(".globl func_80158800\n"
        ".size func_80158800, 1752");
#define BODY_NAME func_801588BC
#else
#define BODY_NAME func_80158800
#endif

void BODY_NAME(S_func_80EF7000_1 *motion, S_func_80EF7000_2 *position, S_func_80EF7000_3 *animation)
#ifdef __mips__
    __attribute__((section(".text.func_80158800")))
#endif
;

/* Advance motion through travel, landing interpolation, and falling. */
void BODY_NAME(S_func_80EF7000_1 *motion, S_func_80EF7000_2 *position, S_func_80EF7000_3 *animation)
{
    s8 command[4];
    GridPoint directions[8];
    GridPoint *direction_base;
    s32 fall_height;
    s32 height;
    u16 duration;
    u16 scale;
    u32 distance;

#ifdef __mips__
    static void *const switch_keepalive[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4
    };
#endif

    __builtin_memcpy(directions, D_80158808, 32);

interpolate:
    if (motion->unk_2C != 1)
        goto fall;
    if (motion->unk_2E != 0)
        goto interpolate_step;
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
        distance = abs_x + abs_y;
    }
    if (distance >= 5U)
        goto max_duration;
    goto *(void *)D_80158828[distance];
case_0:
    duration = 4;
    goto set_duration;
case_1:
    duration = 8;
    goto set_duration;
case_2:
    duration = 12;
    goto set_duration;
case_3:
    duration = 14;
    goto set_duration;
case_4:
max_duration:
    duration = 16;
set_duration:
    motion->unk_36 = duration;
interpolate_step:
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
            interp_current = position->unk_00.half.unk_02.unk_02 - 32;
            interp_goal =
                (interp_goal * 64 - interp_current) / countdown;
            position->unk_00.half.unk_02.unk_02 += interp_goal;

            interp_goal = position->unk_12;
            ASM_KEEP(interp_goal);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            interp_current = position->unk_04.half.unk_06.unk_06;
            countdown = motion->unk_36;
            ASM_KEEP(countdown);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            interp_goal = interp_goal * 64;
            interp_current -= 32;
            interp_goal -= interp_current;
            interp_goal /= countdown;

            interp_current = position->unk_04.half.unk_06.unk_06_u16;
            countdown = position->unk_08.half.unk_0A;
            interp_current += interp_goal;

            interp_goal = position->unk_16;
            position->unk_04.half.unk_06.unk_06 = interp_current;
            interp_goal = (interp_goal - countdown) /
                (s16)motion->unk_36;
            position->unk_08.half.unk_0A += interp_goal;
        }
    }
check_arrival:
    if ((s16)motion->unk_36 > 0)
        goto repeat_interpolation;
    command[0] = 6;
    command[1] = 12;
    command[2] = 0;
    command[3] = 0;
    func_800A7A7C(position->unk_0E, position->unk_12,
                  position->unk_16, animation->unk_08, command);
    goto finish_motion;
repeat_interpolation:
    if (animation->unk_14 & 0x8000)
        goto interpolate;

fall:
    if (motion->unk_2C != 2)
        goto move;
    position->unk_08.unk_08 += motion->unk_74;
    motion->unk_74 += motion->unk_80;
    scale = animation->unk_1E - 0xC8;
    animation->unk_1E = scale;
    animation->unk_1C = scale;
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
    ((S_func_80EF7000_4 *)motion->unk_40)->unk_A4 = 0;
    ((S_func_80EF7000_5 *)((u8 *)motion - 2))->unk_00 |= 0x8000;
    D_800814A0.value |= 0x8000;
    goto epilogue;
repeat_fall:
    if (animation->unk_14 & 0x8000)
        goto fall;

move:
    direction_base = directions;
    if (motion->unk_2C != 0)
        goto epilogue;
    position->unk_00.unk_00 += motion->unk_6C;
    motion->unk_6C += motion->unk_78;
    position->unk_04.unk_04 += motion->unk_70;
    {
        s32 coord;
        register s32 map_sum ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        s32 rounded;
        GridPoint *step;

        coord = motion->unk_70;
        map_sum = motion->unk_34;
        ASM_KEEP(map_sum);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        rounded = motion->unk_7C;
        ASM_KEEP(rounded);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        step = &direction_base[map_sum];
        ASM_KEEP(step);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        map_sum = motion->unk_5C;
        coord += rounded;
        motion->unk_70 = coord;

        coord = step->x.unk_00;
        rounded = position->unk_00.half.unk_02.unk_02;
        map_sum += coord;
        if (rounded < 0)
            rounded += 0x3F;
        coord = rounded >> 6;
        if (map_sum != coord)
            goto update_height;

        coord = step->y.unk_02_u16;
        rounded = position->unk_04.half.unk_06.unk_06;
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
    if ((func_800A45D8(position->unk_00.half.unk_02.unk_02_u16, position->unk_04.half.unk_06.unk_06_u16,
                       position->unk_08.half.unk_0A) << 16) != 0)
        goto stop_horizontal;
    if (func_800BCB04(position->unk_00.half.unk_02.unk_02_u16, position->unk_04.half.unk_06.unk_06_u16,
                      position->unk_08.half.unk_0A) < 0x200)
        goto advance_tile;
stop_horizontal:
    position->unk_00.unk_00 -= motion->unk_6C;
    motion->unk_6C = 0;
    motion->unk_78 = 0;
    position->unk_04.unk_04 -= motion->unk_70;
    motion->unk_70 = 0;
    motion->unk_7C = 0;
    goto clear_animation;
advance_tile:
    motion->unk_5C +=
        ((GridPoint *)((u8 *)direction_base + (motion->unk_34 << 2)))->x.unk_00_u8;
    motion->unk_5D +=
        ((GridPoint *)((u8 *)direction_base + (motion->unk_34 << 2)))->y.unk_02_u8;
clear_animation:
    animation->unk_06 = 0;
update_height:
    position->unk_08.unk_08 += motion->unk_74;
    motion->unk_74 += motion->unk_80;
    height = position->unk_08.half.unk_0A;
    if (func_800BCB04((motion->unk_5C << 6) & 0xFFC0,
                      (motion->unk_5D << 6) & 0xFFC0,
                      (s16)((u16)position->unk_08.half.unk_0A - 0x20)) - 0x10 >=
        height)
        goto repeat_move;
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
repeat_move:
    if (animation->unk_14 & 0x8000)
        goto move;
epilogue:
    return;
}
