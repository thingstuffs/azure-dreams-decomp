#include "common.h"


typedef s32 M2C_UNK;

extern s32 func_8003F270(void);
extern s32 func_80047784();
extern void *func_800A05A4();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern s32 func_800A94A0();
extern void func_80170E18();

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170838[];
extern void *D_80170860[];
extern M2C_UNK D_80171514;
extern u8 D_80173E8C[8];
extern u8 D_80173EDC[8];


typedef struct S_8017256C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
} S_8017256C_0;   /* arg0 in func_8017256C */

typedef struct S_8017256C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    union { void * p; u8 * p2; } unk_60;   /* accessed as both */
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 u; s8 s; } unk_72;   /* accessed as both */
    union { u8 u; s8 s; } unk_73;   /* accessed as both */
} S_8017256C_1;   /* arg3 in func_8017256C */

typedef struct S_8017256C_2_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_8017256C_2_pre;   /* the 0x14 bytes before linked in func_8017256C, addressed as linked[-1] */

typedef struct S_8017256C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017256C_3;   /* src in func_8017256C */

typedef struct S_8017256C_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8017256C_4;   /* arg2 in func_8017256C */

typedef struct S_8017256C_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017256C_5;   /* arg1 in func_8017256C */

typedef struct S_8017256C_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8017256C_6;   /* global in func_8017256C */

/* Advances an actor's action state, updating its target, animation, and completion. */
void func_8017256C(void *action_data, void *motion_data, void *sprite_data, void *actor_data)
{
    static void *const state_labels[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4,
        &&state5, &&state6, &&state7, &&state8
    };
    static void *const kind_labels[] = {
        &&kind8_special, &&kind11_special, &&kind14_special,
        &&kind8_special, &&kind11_special, &&kind14_special,
        &&kind8_special
    };
    register void *action ASM_REG("$18") = action_data;
    void *motion = motion_data;
    void *sprite = sprite_data;
    void *actor = actor_data;
    register s32 is_special;
    register u8 *action_entry ASM_REG("$17");
    u32 state;
    u32 prior_state;
    s32 kind;
    u32 kind_index;
    u16 ticks;
    u16 next_ticks;
    u8 *target_link;

    ASM_KEEP(action);

    state = ((S_8017256C_0 *)action)->unk_9B;
    if (state >= 9) {
        return;
    }
    is_special = 0;
    ASM_KEEP(is_special);
    (void)state_labels;
    goto *D_80170838[state];

state0:
    if (!(((S_8017256C_1 *)actor)->unk_1C & 0x2000)) {
        goto kind_normal;
    }
    kind_index = (((S_8017256C_1 *)actor)->unk_46 & 0x3FFF) - 1;
    if (kind_index >= 7) {
        goto kind_default;
    }
    (void)kind_labels;
    goto *D_80170860[kind_index];

kind14_special:
    is_special = 1;
    goto kind3;
kind11_special:
    is_special = 1;
    goto kind2;
kind8_special:
    is_special = 1;
    goto kind1;

kind_normal:
    kind = ((S_8017256C_1 *)actor)->unk_46 & 0x3FFF;
    if (kind == 2) {
        goto kind2;
    }
    if (kind < 3) {
        if (kind == 1) {
            goto kind1;
        }
        action_entry = 0;

        goto kind_chosen;
    }
    if (kind != 3) {
        action_entry = 0;
        goto kind_chosen;
    }

kind3:
    action_entry = (u8 *)actor + 0xE;
    goto kind_chosen;
kind2:
    action_entry = (u8 *)actor + 0xB;
    goto kind_chosen;
kind1:
    action_entry = (u8 *)actor + 8;
    goto kind_chosen;

kind_default:
    action_entry = 0;
kind_chosen:
    if (*action_entry == 0) {
        goto state0_empty;
    }

    ((S_8017256C_0 *)action)->unk_98 &= 0xFF7F;
    {
        s32 use_player_target = is_special;

        ASM_KEEP(use_player_target);
        if (use_player_target) {
            target_link = D_800814A8;
            ((S_8017256C_1 *)actor)->unk_60.p = target_link;
            goto state0_linked;
        }
    }


    if (D_8006DE24[*action_entry * 20 + 0x12] == 2) {
        target_link = ((S_8017256C_1 *)actor)->unk_60.p2;
        if (target_link != 0) {
state0_linked:
            motion_data = ((S_8017256C_2_pre *)target_link)[-1].unk_00;

            ((S_8017256C_1 *)actor)->unk_72.u = ((S_8017256C_3 *)motion_data)->unk_24;
            ((S_8017256C_1 *)actor)->unk_73.u = ((S_8017256C_3 *)motion_data)->unk_25;
            goto state0_copy;
        }
    } else {
        register s32 x ASM_REG("$2");
        s32 y;

        ((S_8017256C_1 *)actor)->unk_60.p = func_800A05A4(
            actor,
            ((S_8017256C_4 *)sprite)->unk_24,
            ((S_8017256C_4 *)sprite)->unk_25,
            ((S_8017256C_1 *)actor)->unk_2A,
            0x10);
        x = ((S_8017256C_1 *)actor)->unk_72.s;
        y = ((S_8017256C_1 *)actor)->unk_73.s;
        if (x < 0) {
            x = -x;
        }
        if (y < 0) {
            y = -y;
        }
        ((S_8017256C_1 *)actor)->unk_72.u = x;
        ((S_8017256C_1 *)actor)->unk_73.u = y;
    }

state0_copy:
    if (func_800A94A0(actor, action_entry, is_special, (u8 *)action + 0x98) == 0) {
        return;
    }
    ((S_8017256C_0 *)action)->unk_96 = 0;
    ((S_8017256C_0 *)action)->unk_9B++;
    ((S_8017256C_5 *)motion)->unk_14 = 0;
    ((S_8017256C_5 *)motion)->unk_10 = 0;
    ((S_8017256C_5 *)motion)->unk_0C = 0;
    return;

state0_empty:
    ((S_8017256C_5 *)motion)->unk_14 = 0;
    ((S_8017256C_5 *)motion)->unk_10 = 0;
    ((S_8017256C_5 *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((S_8017256C_4 *)sprite)->unk_24, ((S_8017256C_4 *)sprite)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + (0xA6)))--;
    func_800A4ACC(actor);
    ((S_8017256C_1 *)actor)->unk_6D--;
    ((S_8017256C_0 *)action)->unk_8C = &D_80171514;
    ((S_8017256C_1 *)actor)->unk_73.u = 0;
    ((S_8017256C_1 *)actor)->unk_72.u = 0;
    ((S_8017256C_1 *)actor)->unk_46 &= 0x7FFF;
    return;

state1:
    if (func_8003F270() != 0) {
        ((S_8017256C_4 *)sprite)->unk_14 |= 0x800;
        return;
    }
    ((S_8017256C_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_8017256C_0 *)action)->unk_9B++;
    func_800A56E0(0x703);
    ticks = ((S_8017256C_0 *)action)->unk_96;
    next_ticks = ticks + 1;
    ASM_KEEP(next_ticks);
    ((S_8017256C_0 *)action)->unk_96 = next_ticks;
    if ((s16)ticks < 8 && !(((S_8017256C_4 *)sprite)->unk_14 & 0x8000)) {
        return;
    }
    prior_state = ((S_8017256C_0 *)action)->unk_9B;

    ((S_8017256C_0 *)action)->unk_96 = 0;
    goto increment_state;

state2:
    if (((S_8017256C_0 *)action)->unk_A2 != 0) {
        ticks = ((S_8017256C_0 *)action)->unk_96;
        next_ticks = ticks + 1;
        ASM_KEEP(next_ticks);
        ((S_8017256C_0 *)action)->unk_96 = next_ticks;
        if ((s16)ticks < 15 && !(((S_8017256C_4 *)sprite)->unk_14 & 0x8000)) {
            return;
        }
    }
    ((S_8017256C_0 *)action)->unk_96 = 0;
    ((S_8017256C_0 *)action)->unk_9B++;
    func_800A56E0(0x703);
    (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80173EDC;
    func_80047784(
        sprite,
        D_80173EDC[((D_80083228 + ((S_8017256C_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    return;

state3:
    func_80170E18(action, motion, sprite, actor);
    ticks = ((S_8017256C_0 *)action)->unk_96;
    next_ticks = ticks + 1;
    ASM_KEEP(next_ticks);
    ((S_8017256C_0 *)action)->unk_96 = next_ticks;
    if ((s16)ticks < 3 && !(((S_8017256C_4 *)sprite)->unk_14 & 0xE000)) {
        return;
    }
    ((S_8017256C_4 *)sprite)->unk_14 |= 0x800;
    prior_state = ((S_8017256C_0 *)action)->unk_9B;
increment_state:
    ((S_8017256C_0 *)action)->unk_9B = prior_state + 1;
    return;

state4:
    ((S_8017256C_4 *)sprite)->unk_14 |= 0x800;
    ticks = ((S_8017256C_0 *)action)->unk_96;
    next_ticks = ticks + 1;
    ASM_KEEP(next_ticks);
    ((S_8017256C_0 *)action)->unk_96 = next_ticks;
    if ((s16)ticks < 10 && !(((S_8017256C_4 *)sprite)->unk_14 & 0x8000)) {
        return;
    }
    ((S_8017256C_0 *)action)->unk_96 = 0;
    ((S_8017256C_0 *)action)->unk_9B++;
    ((S_8017256C_4 *)sprite)->unk_14 &= 0xF7FF;
    return;

state5:
state6:
    ((S_8017256C_0 *)action)->unk_98 |= 0x80;
    ((S_8017256C_0 *)action)->unk_96 = 0;
    ((S_8017256C_0 *)action)->unk_9B++;
    return;

state7:
    if (!(((S_8017256C_4 *)sprite)->unk_14 & 0xE000)) {
        return;
    }
    ((S_8017256C_5 *)motion)->unk_14 = 0;
    ((S_8017256C_5 *)motion)->unk_10 = 0;
    ((S_8017256C_5 *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((S_8017256C_4 *)sprite)->unk_24, ((S_8017256C_4 *)sprite)->unk_25);
    ((S_8017256C_0 *)action)->unk_9B++;
    if (((S_8017256C_4 *)sprite)->unk_2C == D_80173E8C) {
        return;
    }
    (*(u8 * *)((u8 *)sprite + (0x2C))) = D_80173E8C;
    func_80047784(
        sprite,
        D_80173E8C[((D_80083228 + ((S_8017256C_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_8017256C_0 *)action)->unk_9E = 0;
    ((S_8017256C_0 *)action)->unk_92 = -0x20;
    return;

state8:
    {
        u8 *action_status = (u8 *)&D_80083460;

        if (((S_8017256C_6 *)action_status)->unk_0C != 0) {
            return;
        }
        ((S_8017256C_6 *)action_status)->unk_0A--;
        ((S_8017256C_0 *)action)->unk_8C = &D_80171514;
        func_800A4ACC(actor);
        ((S_8017256C_1 *)actor)->unk_6D--;
        ((S_8017256C_1 *)actor)->unk_73.u = 0;
        ((S_8017256C_1 *)actor)->unk_72.u = 0;
        ((S_8017256C_1 *)actor)->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
    }
}

