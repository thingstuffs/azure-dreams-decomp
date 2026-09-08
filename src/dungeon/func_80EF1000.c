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

void BODY_NAME(void *arg0, void *arg1, void *arg2)
#ifdef __mips__
    __attribute__((section(".text.func_8015E800")))
#endif
;

void BODY_NAME(void *arg0, void *arg1, void *arg2)
{
    s8 command[4];
    GridPoint grid[8];
    GridPoint *grid_base;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v0;
    s32 var_v1;
    s32 temp_a0;
    u16 temp_v0;
    u16 temp_v0_2;
    u32 temp_v1;

#ifdef __mips__
    static void *const switch_keepalive[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4
    };
#endif

    __builtin_memcpy(grid, D_8015E808, 32);

loop_1:
    if (FIELD(arg0, s16, 0x2C) != 1)
        goto block_25;
    if (FIELD(arg0, s16, 0x2E) != 0)
        goto block_18;
    FIELD(arg0, s16, 0x2E) = (s16)((u16)FIELD(arg0, s16, 0x2E) + 1);
    {
        s32 abs_x;
        s32 abs_y;
        s32 map_y;

        abs_x = FIELD(arg1, s16, 0x0E);
        abs_y = FIELD(arg0, s8, 0x5C);
        map_y = FIELD(arg0, s8, 0x5D);
        abs_x -= abs_y;
        abs_y = FIELD(arg1, s16, 0x12);
        if (abs_x < 0)
            abs_x = -abs_x;
        abs_y -= map_y;
        if (abs_y < 0)
            abs_y = -abs_y;
        temp_v1 = abs_x + abs_y;
    }
    if (temp_v1 >= 5U)
        goto block_17;
    goto *(void *)D_8015E828[temp_v1];
case_0:
    temp_v0 = 4;
    goto block_16;
case_1:
    temp_v0 = 8;
    goto block_16;
case_2:
    temp_v0 = 12;
    goto block_16;
case_3:
    temp_v0 = 14;
    goto block_16;
case_4:
block_17:
    temp_v0 = 16;
block_16:
    FIELD(arg0, s16, 0x36) = temp_v0;
block_18:
    {
        u32 countdown_raw;
        s32 countdown;
        s32 shifted_countdown;

        countdown_raw = (u16)FIELD(arg0, s16, 0x36) - 1;
        FIELD(arg0, s16, 0x36) = countdown_raw;
        ASM_KEEP(countdown_raw);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        shifted_countdown = (s32)(countdown_raw << 16);
        countdown = shifted_countdown >> 16;
        if (countdown == 0)
            goto block_20;
        {
            register s32 interp_goal ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            s32 interp_current;

            interp_goal = FIELD(arg1, s16, 0x0E);
            ASM_KEEP(interp_goal);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            interp_current = FIELD(arg1, s16, 2) - 32;
            interp_goal =
                (interp_goal * 64 - interp_current) / countdown;
            FIELD(arg1, s16, 2) += interp_goal;

            interp_goal = FIELD(arg1, s16, 0x12);
            ASM_KEEP(interp_goal);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            interp_current = FIELD(arg1, s16, 6);
            countdown = FIELD(arg0, s16, 0x36);
            ASM_KEEP(countdown);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            interp_goal = interp_goal * 64;
            interp_current -= 32;
            interp_goal -= interp_current;
            interp_goal /= countdown;

            interp_current = FIELD(arg1, u16, 6);
            countdown = FIELD(arg1, s16, 0x0A);
            interp_current += interp_goal;

            interp_goal = FIELD(arg1, s16, 0x16);
            FIELD(arg1, s16, 6) = interp_current;
            interp_goal = (interp_goal - countdown) /
                (s16)FIELD(arg0, s16, 0x36);
            FIELD(arg1, s16, 0x0A) += interp_goal;
        }
    }
block_20:
    if ((s16)FIELD(arg0, s16, 0x36) > 0)
        goto block_23;
    command[0] = 6;
    command[1] = 12;
    command[2] = 0;
    command[3] = 0;
    func_800A7A7C(FIELD(arg1, s16, 0x0E), FIELD(arg1, s16, 0x12),
                  FIELD(arg1, s16, 0x16), FIELD(arg2, s32 *, 8), command);
    goto after_a7;
block_23:
    if (FIELD(arg2, u16, 0x14) & 0x8000)
        goto loop_1;

block_25:
    if (FIELD(arg0, s16, 0x2C) != 2)
        goto loop_30;
    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x74);
    FIELD(arg0, s32, 0x74) += FIELD(arg0, s32, 0x80);
    temp_v0_2 = FIELD(arg2, u16, 0x1E) - 0xC8;
    FIELD(arg2, u16, 0x1E) = temp_v0_2;
    FIELD(arg2, u16, 0x1C) = temp_v0_2;
    temp_s0 = FIELD(arg1, s16, 0x0A);
    if (func_800BCB04((FIELD(arg0, s8, 0x5C) << 6) & 0xFFC0,
                      (FIELD(arg0, s8, 0x5D) << 6) & 0xFFC0,
                      (s16)((u16)FIELD(arg1, s16, 0x0A) - 0x20)) - 7 >=
        temp_s0)
        goto block_29;
    FIELD(arg1, s16, 0x0A) = func_800BCB04(
        (FIELD(arg0, s8, 0x5C) << 6) & 0xFFC0,
        (FIELD(arg0, s8, 0x5D) << 6) & 0xFFC0,
        (s16)((u16)FIELD(arg1, s16, 0x0A) - 0x20));
    FIELD(arg1, s16, 8) = 0;
after_a7:
    FIELD(FIELD(arg0, void **, 0x40), s16, 0xA4) = 0;
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0.value |= 0x8000;
    goto epilogue;
block_29:
    if (FIELD(arg2, u16, 0x14) & 0x8000)
        goto block_25;

loop_30:
    grid_base = grid;
    if (FIELD(arg0, s16, 0x2C) != 0)
        goto epilogue;
    FIELD(arg1, s32, 0) += FIELD(arg0, s32, 0x6C);
    FIELD(arg0, s32, 0x6C) += FIELD(arg0, s32, 0x78);
    FIELD(arg1, s32, 4) += FIELD(arg0, s32, 0x70);
    {
        s32 coord;
        register s32 map_sum ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        s32 rounded;
        GridPoint *point;

        coord = FIELD(arg0, s32, 0x70);
        map_sum = FIELD(arg0, s16, 0x34);
        ASM_KEEP(map_sum);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        rounded = FIELD(arg0, s32, 0x7C);
        ASM_KEEP(rounded);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        point = &grid_base[map_sum];
        ASM_KEEP(point);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        map_sum = FIELD(arg0, s8, 0x5C);
        coord += rounded;
        FIELD(arg0, s32, 0x70) = coord;

        coord = point->x;
        rounded = FIELD(arg1, s16, 2);
        map_sum += coord;
        if (rounded < 0)
            rounded += 0x3F;
        coord = rounded >> 6;
        if (map_sum != coord)
            goto block_42;

        coord = FIELD(point, u16, 2);
        rounded = FIELD(arg1, s16, 6);
        map_sum = FIELD(arg0, s8, 0x5D);
        ASM_KEEP(map_sum);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        coord = (s16)coord;
        map_sum += coord;
        if (rounded < 0)
            rounded += 0x3F;
        coord = rounded >> 6;
        if (map_sum != coord)
            goto block_42;
    }
    if ((func_800A45D8(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                       FIELD(arg1, s16, 0x0A)) << 16) != 0)
        goto block_39;
    if (func_800BCB04(FIELD(arg1, u16, 2), FIELD(arg1, u16, 6),
                      FIELD(arg1, s16, 0x0A)) < 0x200)
        goto block_41;
block_39:
    FIELD(arg1, s32, 0) -= FIELD(arg0, s32, 0x6C);
    FIELD(arg0, s32, 0x6C) = 0;
    FIELD(arg0, s32, 0x78) = 0;
    FIELD(arg1, s32, 4) -= FIELD(arg0, s32, 0x70);
    FIELD(arg0, s32, 0x70) = 0;
    FIELD(arg0, s32, 0x7C) = 0;
    goto block_41_cleanup;
block_41:
    FIELD(arg0, s8, 0x5C) +=
        FIELD((u8 *)grid_base + (FIELD(arg0, s16, 0x34) << 2), u8, 0);
    FIELD(arg0, s8, 0x5D) +=
        FIELD((u8 *)grid_base + (FIELD(arg0, s16, 0x34) << 2), u8, 2);
block_41_cleanup:
    FIELD(arg2, s16, 6) = 0;
block_42:
    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x74);
    FIELD(arg0, s32, 0x74) += FIELD(arg0, s32, 0x80);
    temp_s0_2 = FIELD(arg1, s16, 0x0A);
    if (func_800BCB04((FIELD(arg0, s8, 0x5C) << 6) & 0xFFC0,
                      (FIELD(arg0, s8, 0x5D) << 6) & 0xFFC0,
                      (s16)((u16)FIELD(arg1, s16, 0x0A) - 0x20)) - 0x10 >=
        temp_s0_2)
        goto block_46;
    FIELD(arg1, s16, 0x0A) = func_800BCB04(
        (FIELD(arg0, s8, 0x5C) << 6) & 0xFFC0,
        (FIELD(arg0, s8, 0x5D) << 6) & 0xFFC0,
        (s16)((u16)FIELD(arg1, s16, 0x0A) - 0x20));
    FIELD(arg1, s16, 8) = 0;
    FIELD(arg0, s32, 0x7C) = 0;
    FIELD(arg0, s32, 0x70) = 0;
    FIELD(arg0, s32, 0x78) = 0;
    FIELD(arg0, s32, 0x6C) = 0;
    FIELD(arg0, s16, 0x2C) = (s16)((u16)FIELD(arg0, s16, 0x2C) + 1);
    if ((func_800A7234(FIELD(arg0, s8, 0x5C), FIELD(arg0, s8, 0x5D),
                       (s16)((u16)FIELD(arg1, s16, 0x0A) - 0x20),
                       &FIELD(arg1, s16, 0x0E), &FIELD(arg1, s16, 0x12),
                       &FIELD(arg1, s16, 0x16)) << 16) != 0)
        goto epilogue;
    FIELD(arg0, s16, 0x2C) = 2;
    FIELD(arg0, s32, 0x74) = (s32)0xFFF80000;
    goto epilogue;
block_46:
    if (FIELD(arg2, u16, 0x14) & 0x8000)
        goto loop_30;
epilogue:
    return;
}
