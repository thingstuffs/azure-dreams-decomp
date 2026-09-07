#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef s32 Any;

extern void *D_80170888[];
extern void *D_801708A0[];
extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80171CE8[];
extern u8 D_80174EB8[];

extern s32 func_8003F270();
extern Any func_80047784();
extern s32 func_80069EF8();
extern void *func_800A05A4();
extern Any func_800A2B04();
extern Any func_800A4ACC();
extern Any func_800A56E0();
extern s32 func_800A94A0();
extern Any func_80171498();

void func_801737B0(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const state_jt[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4
    };
    static void *const kind_jt[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_bad,
        &&kind_5, &&kind_6, &&kind_7
    };
    s32 flag;
    register s32 count ASM_REG("$18");
    s32 value;
    s32 nonflag_kind;
    register s32 particle_zero ASM_REG("$5");
    register s32 particle_color ASM_REG("$6");
    register s32 rand_x ASM_REG("$17");
    register s32 rand_y ASM_REG("$16");
    u16 half;
    u16 flags;
    u16 kind_raw;
    u32 kind_index;
    u8 state;
    u8 *kind_ptr;
    u8 *global;
    u8 *particle_ptr;
    register void *ptr ASM_REG("$2");

    state = FIELD(arg0, u8, 0x9B);
    flag = 0;
    if ((u32)state >= 5U) {
        goto done;
    }
    (void)state_jt;
    goto *D_80170888[(u32)state];

state_0:
    if (FIELD(arg3, s32, 0x1C) & 0x2000) {
        kind_raw = FIELD(arg3, u16, 0x46) & 0x3FFF;
        kind_index = kind_raw - 1;
        if (kind_index >= 7U) {
            goto kind_bad;
        }
        (void)kind_jt;
        goto *D_801708A0[kind_index];
kind_7:
        flag = 1;
        goto kind_3;
kind_6:
        flag = 1;
        goto kind_2;
kind_5:
        flag = 1;
        goto kind_1;
    }

    nonflag_kind = FIELD(arg3, u16, 0x46) & 0x3FFF;
    if (nonflag_kind == 2) {
        goto kind_2;
    }
    if (nonflag_kind < 3) {
        kind_ptr = 0;
        if (nonflag_kind == 1) {
            goto kind_1;
        }
        goto kind_ready;
    }
    kind_ptr = 0;
    if (nonflag_kind == 3) {
        goto kind_3;
    }
    goto kind_ready;

kind_3:
    kind_ptr = (u8 *)arg3 + 0xE;
    goto kind_ready;
kind_2:
    kind_ptr = (u8 *)arg3 + 0xB;
    goto kind_ready;
kind_1:
    kind_ptr = (u8 *)arg3 + 8;
    goto kind_ready;
kind_bad:
    kind_ptr = 0;

kind_ready:
    if (*kind_ptr == 0) {
        goto remove_actor;
    }

    FIELD(arg0, u16, 0x98) &= 0xFF7F;
    ASM_SCHED_BARRIER();
    ptr = (void *)flag;
    ASM_USE(ptr);
    if (ptr != 0) {
        ptr = D_800814A8;
        FIELD(arg3, void *, 0x60) = ptr;
        goto copy_facing;
    }

    if (D_8006DE24[*kind_ptr * 0x14 + 0x12] == 2) {
        ptr = FIELD(arg3, void *, 0x60);
        if (ptr != 0) {
copy_facing:
            {
                u8 *desc;
                u8 facing;

                desc = FIELD(ptr, u8 *, -0x14);
                ASM_USE(ptr);
                facing = FIELD(desc, u8, 0x24);
                FIELD(arg3, s8, 0x72) = facing;
                facing = FIELD(desc, u8, 0x25);
                FIELD(arg3, s8, 0x73) = facing;
            }
        }
    } else {
        register s32 facing_y ASM_REG("$3");

        FIELD(arg3, void *, 0x60) = func_800A05A4(
            arg3,
            FIELD(arg2, u8, 0x24),
            FIELD(arg2, u8, 0x25),
            FIELD(arg3, s16, 0x2A),
            0x10);
        ASM_SCHED_BARRIER();

        value = FIELD(arg3, s8, 0x72);
        facing_y = FIELD(arg3, s8, 0x73);
        if (value < 0) {
            value = -value;
        }
        if (facing_y < 0) {
            facing_y = -facing_y;
        }
        FIELD(arg3, s8, 0x72) = value;
        FIELD(arg3, s8, 0x73) = facing_y;
    }

    if (func_800A94A0(arg3, kind_ptr, flag, (u8 *)arg0 + 0x98) == 0) {
        goto done;
    }
    FIELD(arg0, u8, 0x9B)++;
    goto done;

remove_actor:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C = 0;
    FIELD(D_800814A8, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = D_80171CE8;
    FIELD(arg3, s8, 0x73) = 0;
    FIELD(arg3, s8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    goto done;

state_1:
    if (func_8003F270(arg1) != 0) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        goto done;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;
    func_800A56E0(0x703);

state_2:
    flags = FIELD(arg2, u16, 0x14);
    if (flags & 0x8000) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B)++;
        FIELD(arg0, u16, 0x98) |= 0x80;
        goto done;
    }

    if ((FIELD(arg2, s8, 4) == 2) && (flags & 0x1000)) {
        FIELD(arg2, u16, 0x14) = flags | 0x800;
        FIELD(arg0, u16, 0x96) = 0x16;
    }
    if (FIELD(arg2, s8, 4) < 2) {
        goto done;
    }

    half = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = half;
    if ((s16)half <= 0) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B)++;
    }
    if (FIELD(arg0, s16, 0x96) == 2) {
        FIELD(arg0, u16, 0x98) |= 0x80;
    }
    if (FIELD(arg0, s16, 0x96) < 0xA) {
        goto done;
    }

    count = 0;
particle_loop:
    count++;
    rand_x = func_80069EF8() & 0x3F;
    rand_x -= 0x20;
    rand_x = (s16)rand_x;
    rand_y = func_80069EF8() & 0x3F;
    rand_y -= 0x20;
    rand_y = (s16)rand_y;
    value = func_80069EF8();
    particle_ptr = (u8 *)arg0 - 0x20;
    ASM_USE(particle_ptr);
    particle_zero = 0;
    ASM_USE(particle_zero);
    particle_color = 0xC0C0C0;
    ASM_USE(particle_color);
    value = (s16)((value & 0x3F) - 0x20);
    func_80171498(
        particle_ptr,
        particle_zero,
        particle_color,
        (s16)(FIELD(arg0, u16, 0x96) - 2),
        rand_x,
        rand_y,
        value);
    if ((u32)(count & 0xFFFF) >= 3U) {
        goto done;
    }
    goto particle_loop;

state_3:
    FIELD(arg0, u16, 0x96) = 0x14;
    FIELD(arg0, u8, 0x9B)++;

state_4:
    global = (u8 *)&D_80083460;
    if (FIELD(global, s32, 0xC) == 0) {
        FIELD(arg0, u16, 0x96) = 0;
    }
    half = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = half;
    if ((s16)half <= 0) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
    }
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

    if (FIELD(arg2, void *, 0x2C) != D_80174EB8) {
        FIELD(arg2, void *, 0x2C) = D_80174EB8;
        value = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
        func_80047784(arg2, D_80174EB8[value], 0);
    }
    if (FIELD(global, s32, 0xC) != 0) {
        goto done;
    }

    FIELD(global, u16, 0xA)--;
    FIELD(arg0, void *, 0x8C) = D_80171CE8;
    func_800A4ACC(arg3);
    FIELD(arg3, s8, 0x73) = 0;
    FIELD(arg3, s8, 0x72) = 0;
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    func_800A56E0(0xB4);

done:
    return;
}
