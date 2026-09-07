#include "common.h"


typedef s32 Any;

typedef struct S_801737B0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801737B0_0;   /* arg0 in func_801737B0 */

typedef struct S_801737B0_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    s8 unk_72;
    s8 unk_73;
} S_801737B0_1;   /* arg3 in func_801737B0 */

typedef struct S_801737B0_2_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_801737B0_2_pre;   /* the 0x14 bytes before ptr in func_801737B0, addressed as ptr[-1] */

typedef struct S_801737B0_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801737B0_3;   /* desc in func_801737B0 */

typedef struct S_801737B0_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_801737B0_4;   /* arg2 in func_801737B0 */

typedef struct S_801737B0_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801737B0_5;   /* arg1 in func_801737B0 */

typedef struct S_801737B0_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801737B0_6;   /* global in func_801737B0 */


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
    register s32 count ASM_REG("$18");   /* MATCH pin: retail keeps a computation the compiler would drop */
    s32 value;
    s32 nonflag_kind;
    register s32 particle_zero ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 particle_color ASM_REG("$6");   /* MATCH pin: retail immediate-load split depends on it */
    register s32 rand_x ASM_REG("$17");   /* MATCH pin: retail register colouring depends on it */
    register s32 rand_y ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    u16 half;
    u16 flags;
    u16 kind_raw;
    u32 kind_index;
    u8 state;
    u8 *kind_ptr;
    u8 *global;
    u8 *particle_ptr;
    register void *ptr ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */

    state = ((S_801737B0_0 *)arg0)->unk_9B;
    flag = 0;
    if ((u32)state >= 5U) {
        goto done;
    }
    (void)state_jt;
    goto *D_80170888[(u32)state];

state_0:
    if (((S_801737B0_1 *)arg3)->unk_1C & 0x2000) {
        kind_raw = ((S_801737B0_1 *)arg3)->unk_46 & 0x3FFF;
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

    nonflag_kind = ((S_801737B0_1 *)arg3)->unk_46 & 0x3FFF;
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

    ((S_801737B0_0 *)arg0)->unk_98 &= 0xFF7F;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ptr = (void *)flag;
    if (ptr != 0) {
        ptr = D_800814A8;
        ((S_801737B0_1 *)arg3)->unk_60 = ptr;
        goto copy_facing;
    }

    if (D_8006DE24[*kind_ptr * 0x14 + 0x12] == 2) {
        ptr = ((S_801737B0_1 *)arg3)->unk_60;
        if (ptr != 0) {
copy_facing:
            {
                u8 *desc;
                u8 facing;

                desc = ((S_801737B0_2_pre *)ptr)[-1].unk_00;
                ASM_USE(ptr);   /* MATCH pin: load-bearing for the whole function shape */
                facing = ((S_801737B0_3 *)desc)->unk_24;
                ((S_801737B0_1 *)arg3)->unk_72 = facing;
                facing = ((S_801737B0_3 *)desc)->unk_25;
                ((S_801737B0_1 *)arg3)->unk_73 = facing;
            }
        }
    } else {
        s32 facing_y;

        ((S_801737B0_1 *)arg3)->unk_60 = func_800A05A4(
            arg3,
            ((S_801737B0_4 *)arg2)->unk_24,
            ((S_801737B0_4 *)arg2)->unk_25,
            ((S_801737B0_1 *)arg3)->unk_2A,
            0x10);
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

        value = ((S_801737B0_1 *)arg3)->unk_72;
        facing_y = ((S_801737B0_1 *)arg3)->unk_73;
        if (value < 0) {
            value = -value;
        }
        if (facing_y < 0) {
            facing_y = -facing_y;
        }
        ((S_801737B0_1 *)arg3)->unk_72 = value;
        ((S_801737B0_1 *)arg3)->unk_73 = facing_y;
    }

    if (func_800A94A0(arg3, kind_ptr, flag, (u8 *)arg0 + 0x98) == 0) {
        goto done;
    }
    ((S_801737B0_0 *)arg0)->unk_9B++;
    goto done;

remove_actor:
    ((S_801737B0_5 *)arg1)->unk_14 = 0;
    ((S_801737B0_5 *)arg1)->unk_10 = 0;
    ((S_801737B0_5 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_801737B0_4 *)arg2)->unk_24, ((S_801737B0_4 *)arg2)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(arg3);
    ((S_801737B0_1 *)arg3)->unk_6D--;
    ((S_801737B0_0 *)arg0)->unk_8C = D_80171CE8;
    ((S_801737B0_1 *)arg3)->unk_73 = 0;
    ((S_801737B0_1 *)arg3)->unk_72 = 0;
    ((S_801737B0_1 *)arg3)->unk_46 &= 0x7FFF;
    goto done;

state_1:
    if (func_8003F270(arg1) != 0) {
        ((S_801737B0_4 *)arg2)->unk_14 |= 0x800;
        goto done;
    }
    ((S_801737B0_4 *)arg2)->unk_14 &= 0xF7FF;
    ((S_801737B0_0 *)arg0)->unk_9B++;
    func_800A56E0(0x703);

state_2:
    flags = ((S_801737B0_4 *)arg2)->unk_14;
    if (flags & 0x8000) {
        ((S_801737B0_0 *)arg0)->unk_96.s = 0;
        ((S_801737B0_0 *)arg0)->unk_9B++;
        ((S_801737B0_0 *)arg0)->unk_98 |= 0x80;
        goto done;
    }

    if ((((S_801737B0_4 *)arg2)->unk_04 == 2) && (flags & 0x1000)) {
        ((S_801737B0_4 *)arg2)->unk_14 = flags | 0x800;
        ((S_801737B0_0 *)arg0)->unk_96.s = 0x16;
    }
    if (((S_801737B0_4 *)arg2)->unk_04 < 2) {
        goto done;
    }

    half = ((S_801737B0_0 *)arg0)->unk_96.s - 1;
    ((S_801737B0_0 *)arg0)->unk_96.s = half;
    if ((s16)half <= 0) {
        ((S_801737B0_0 *)arg0)->unk_96.s = 0;
        ((S_801737B0_0 *)arg0)->unk_9B++;
    }
    if (((S_801737B0_0 *)arg0)->unk_96.u == 2) {
        ((S_801737B0_0 *)arg0)->unk_98 |= 0x80;
    }
    if (((S_801737B0_0 *)arg0)->unk_96.u < 0xA) {
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
    ASM_USE(particle_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
    particle_zero = 0;
    particle_color = 0xC0C0C0;
    ASM_USE(particle_color);   /* MATCH pin: retail schedule: same instructions, different order without it */
    value = (s16)((value & 0x3F) - 0x20);
    func_80171498(
        particle_ptr,
        particle_zero,
        particle_color,
        (s16)(((S_801737B0_0 *)arg0)->unk_96.s - 2),
        rand_x,
        rand_y,
        value);
    if ((u32)(count & 0xFFFF) >= 3U) {
        goto done;
    }
    goto particle_loop;

state_3:
    ((S_801737B0_0 *)arg0)->unk_96.s = 0x14;
    ((S_801737B0_0 *)arg0)->unk_9B++;

state_4:
    global = (u8 *)&D_80083460;
    if (((S_801737B0_6 *)global)->unk_0C == 0) {
        ((S_801737B0_0 *)arg0)->unk_96.s = 0;
    }
    half = ((S_801737B0_0 *)arg0)->unk_96.s - 1;
    ((S_801737B0_0 *)arg0)->unk_96.s = half;
    if ((s16)half <= 0) {
        ((S_801737B0_0 *)arg0)->unk_96.s = 0;
        ((S_801737B0_4 *)arg2)->unk_14 &= 0xF7FF;
    }
    if (!(((S_801737B0_4 *)arg2)->unk_14 & 0xE000)) {
        goto done;
    }

    ((S_801737B0_5 *)arg1)->unk_14 = 0;
    ((S_801737B0_5 *)arg1)->unk_10 = 0;
    ((S_801737B0_5 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_801737B0_4 *)arg2)->unk_24, ((S_801737B0_4 *)arg2)->unk_25);

    if (((S_801737B0_4 *)arg2)->unk_2C != D_80174EB8) {
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174EB8;
        value = ((D_80083228 + ((S_801737B0_1 *)arg3)->unk_2A + 0x100) >> 9) & 7;
        func_80047784(arg2, D_80174EB8[value], 0);
    }
    if (((S_801737B0_6 *)global)->unk_0C != 0) {
        goto done;
    }

    ((S_801737B0_6 *)global)->unk_0A--;
    ((S_801737B0_0 *)arg0)->unk_8C = D_80171CE8;
    func_800A4ACC(arg3);
    ((S_801737B0_1 *)arg3)->unk_73 = 0;
    ((S_801737B0_1 *)arg3)->unk_72 = 0;
    ((S_801737B0_1 *)arg3)->unk_6D--;
    ((S_801737B0_1 *)arg3)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);

done:
    return;
}
