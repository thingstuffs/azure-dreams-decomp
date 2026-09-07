#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} LocalVector;

typedef struct {
    u32 words[8];
} __attribute__((packed)) LocalTable;

#define monster arg2
#define motion arg1

extern void func_80047784(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8009A028(void *);
extern void func_8009A3D0(u8, u8, s32);
extern s32 func_800A2FE0(void *);
extern s32 func_800A32A4(void *);
extern s32 func_800A45D8(u16, u16, s16);
extern void func_800A56E0(s32);
extern void func_800ACF88(void *);
extern s16 func_800BCB04(u16, u16, s16);
extern s32 func_8017165C(s32);

extern s32 D_800814A0;
extern u8 D_80083160[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800E2368[];
extern s32 D_800E296C;
extern LocalTable D_8017088C;
extern void *const D_801708B0[];
extern void *const D_801708C8[];

void func_8017450C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    LocalVector vector;
    LocalTable table;
    s16 initial_angle;
    s32 value;
    s32 product;
    s32 counter;
    s32 random_x;
    s32 random_y;
    s32 x_offset;
    s32 y_offset;
    s32 x;
    s32 y;
    s32 lookup_index;
    u32 actor;
    u8 *globals;
    u8 tile_x;
    u8 tile_y;

    table = D_8017088C;
    actor = (u32)arg3;

    {
        static void *const sw_keep[] = {
            &&state_0, &&state_1, &&state_2, &&state_3, &&state_4
        };
        u32 swi = FIELD(arg0, u8, 0x9B);

        if (swi >= 5) {
            return;
        }
        (void)sw_keep;
        goto *D_801708B0[swi];
    }

state_0:
    if (FIELD(monster, u16, 0x14) & 0x8000) {
        goto cleanup;
    }

    initial_angle = 0;
    globals = D_80083160;
    do {
        if (((FIELD(globals, s16, 0xC8) + initial_angle + 0x100) >> 9 & 7) == 2) {
            FIELD(actor, s16, 0x2A) = initial_angle;
        }
        initial_angle += 0x200;
    } while (initial_angle < 0x1000);

    {
        register u8 *table_base ASM_REG("$5") = D_800E2368;
        FIELD(monster, u8 *, 0x2C) = table_base;
        lookup_index = (D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9 & 7;
        func_80047784(monster, table_base[lookup_index], 0);
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(actor, u32, 0x1C) &= 0xFFFBFFFF;
        FIELD(arg0, u16, 0x92) += FIELD(actor, u16, 0x88);
        FIELD(actor, u16, 0x88) = 0;
    }
    {
        register u16 motion_angle ASM_REG("$2") = FIELD(arg0, u8, 0x9B);
        register u16 final_angle ASM_REG("$5") = FIELD(arg0, u16, 0x92);
        register s32 *sound_flags ASM_REG("$6") = &D_800E296C;
        register s32 flags_value ASM_REG("$3");

        FIELD(arg0, s32, 0xA0) = 0;
        FIELD(arg0, u8, 0x9B) = motion_angle + 1;
        motion_angle = FIELD(motion, u16, 0xA);
        flags_value = *sound_flags;
        motion_angle += final_angle;
        flags_value |= 0x40;
        FIELD(arg0, u16, 0xB6) = motion_angle;
        *sound_flags = flags_value;
        func_800A56E0(0x807);
    }

state_1:
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(monster, u16, 0x22) = 0xFFEC;
    FIELD(monster, s16, 0x1C) = 0x800;

state_2:
    {
        static void *const sw_keep[] = {
            &&angle_default,
            &&angle_12, &&angle_12,
            &&angle_3_8, &&angle_3_8, &&angle_3_8,
            &&angle_3_8, &&angle_3_8, &&angle_3_8,
            &&angle_9_10, &&angle_9_10,
            &&angle_11_14, &&angle_11_14, &&angle_11_14, &&angle_11_14,
            &&angle_15_17, &&angle_15_17, &&angle_15_17,
            &&angle_18_21, &&angle_18_21, &&angle_18_21, &&angle_18_21
        };
        u32 swi = (u32)(s16)FIELD(arg0, s16, 0x96);

        if (swi >= 0x16) {
            goto angle_default;
        }
        (void)sw_keep;
        goto *D_801708C8[swi];
    }

angle_12:
    FIELD(arg0, s16, 0xAE) = 0x30;
    FIELD(monster, u16, 0x1A) += 0x100;
    goto angle_store;

angle_3_8:
    FIELD(arg0, s16, 0xAE) = 0x28;
    FIELD(monster, u16, 0x1A) += 0x200;
    goto angle_store;

angle_9_10:
    FIELD(arg0, s16, 0xAE) = 0x30;
    FIELD(monster, u16, 0x1A) += 0x100;
    goto angle_store;

angle_11_14:
    FIELD(arg0, s16, 0xAE) = 0x70;
    FIELD(monster, u16, 0x1A) += 0x100;
    goto angle_store;

angle_15_17:
    FIELD(arg0, s16, 0xAE) = 0x60;
    FIELD(monster, u16, 0x1A) += 0x200;
    goto angle_store;

angle_18_21:
    FIELD(arg0, s16, 0xAE) = 0x50;
    FIELD(monster, u16, 0x1A) += 0x80;
    goto angle_store;

angle_default:
    FIELD(monster, u16, 0x1A) += 0x20;

angle_store:
    if (FIELD(monster, u16, 0x1A) >= 0x1000) {
        FIELD(monster, u16, 0x1A) -= 0x1000;
    }

    {
        register s32 angle ASM_REG("$16");
        s32 diff;

        angle = FIELD(monster, u16, 0x1A);
        diff = angle - 0x400;
        angle = diff;
        if ((s16)diff < 0) {
            angle = diff + 0x1000;
        }
        angle = (s16)angle;

        value = func_80064584(angle);
        product = FIELD(arg0, s16, 0xAE) * value;
        {
            s32 original_angle = angle;

            angle = product << 4;
            value = func_800644B8(original_angle);
        }

        product = FIELD(arg0, s16, 0xAE) * value;
        {
            register u8 *table_base ASM_REG("$5") = (u8 *)&table;
            vector.x = FIELD(table_base, u16,
                ((FIELD(actor, s16, 0x2A) - 0x400) >> 7) & 0x1C);
            table_base +=
                ((FIELD(actor, s16, 0x2A) - 0x400) >> 7) & 0x1C;
            vector.y = FIELD(table_base, u16, 2);

            FIELD(arg0, s32, 0x90) += product << 4;
            FIELD(motion, s32, 0xC) = (vector.x * angle) >> 4;
            FIELD(motion, s32, 0x10) = (vector.y * angle) >> 4;
        }
    }

    if ((s16)(FIELD(arg0, u16, 0x96)++) < 0x2D) {
        return;
    }

    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(monster, s16, 0x1A) = 0x800;
    FIELD(motion, s32, 0x10) = 0;
    FIELD(motion, s32, 0xC) = 0;
    FIELD(motion, s16, 2) = (FIELD(monster, u8, 0x24) << 6) + 0x20;
    FIELD(motion, s16, 6) = (FIELD(monster, u8, 0x25) << 6) + 0x20;
    FIELD(motion, u16, 0xA) = FIELD(arg0, u16, 0xB6);
    FIELD(motion, s32, 0x14) = 0x280000;
    FIELD(arg0, s32, 0xA0) = 0;
    FIELD(arg0, u16, 0x92) = FIELD(arg0, u16, 0xB6) - 0x12C;
    FIELD(monster, s16, 0x1C) = 0x600;

    counter = 0;
    do {
        random_x = func_8017165C(7) - 3;
        random_y = func_8017165C(6) - 2;
        x_offset = random_x << 6;
        x = FIELD(motion, s16, 2) + x_offset;
        if (x >= 0x1020) {
            goto next_try;
        }
        if (x <= 0) {
            goto next_try;
        }

        y_offset = random_y << 6;
        y = FIELD(motion, s16, 6) + y_offset;
        if (y >= 0x1020) {
            goto next_try;
        }
        if (y <= 0) {
            goto next_try;
        }

        actor = (u16)x;
        y = (u16)y;
        if ((func_800A45D8(actor, y, -0x200) << 16) != 0) {
            goto next_try;
        }
        if (func_800BCB04(actor, y, -0x200) < 0x200) {
            counter++;
            continue;
        }

        random_x = 0xB;
        counter = random_x;
        FIELD(motion, u16, 2) += x_offset;
        FIELD(motion, u16, 6) += y_offset;

next_try:
        counter++;
    } while (counter < 0xA);

    if (random_x == 0xB) {
        return;
    }

    FIELD(arg0, u8, 0x9B) = 4;
    FIELD(motion, s32, 0x14) = 0;
    FIELD(monster, u16, 0x14) |= 0x80;
    return;

state_3:
    if ((s16)(FIELD(arg0, u16, 0x96)++) < 0x1E) {
        return;
    }
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    return;

state_4:
    if ((s16)(FIELD(arg0, u16, 0x96)++) < 0xA) {
        return;
    }
    if (FIELD(actor, u32, 0x14) & 0x4000) {
        if (!(FIELD(actor, u32, 0x14) & 0x20000000)) {
            func_800ACF88((void *)actor);
        }
    }

cleanup:
{
    u8 *cleanup_base = (u8 *)&D_80083460;
    u32 cleanup_value;

    cleanup_value = FIELD(cleanup_base, u32, 0x10);
    if (cleanup_value == actor - 0x20) {
        FIELD(cleanup_base, u32, 0x10) = cleanup_value & 0x7FFFFFFF;
    }
    func_800A2FE0((void *)actor);
    func_800A32A4((void *)actor);
    tile_x = FIELD(monster, u8, 0x24);
    tile_y = FIELD(monster, u8, 0x25);
    if (FIELD(actor, u32, 0x1C) & 0x2000) {
        value = 0x300;
    } else {
        value = 0x3000;
    }
    func_8009A3D0(tile_x, tile_y, value);
    func_8009A028((void *)actor);
    FIELD(actor, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
}
}
