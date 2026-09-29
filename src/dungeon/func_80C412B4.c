#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
extern int abs(int);

typedef struct S_80172AB4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172AB4_0;   /* arg0 in func_80172AB4 */

typedef struct S_80172AB4_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    union { u8 s; s8 u; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_80172AB4_1;   /* arg3 in func_80172AB4 */

typedef struct S_80172AB4_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172AB4_2_pre;   /* the 0x14 bytes before object in func_80172AB4, addressed as object[-1] */

typedef struct S_80172AB4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172AB4_3;   /* record in func_80172AB4 */

typedef struct S_80172AB4_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172AB4_4;   /* arg2 in func_80172AB4 */

typedef struct S_80172AB4_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172AB4_5;   /* arg1 in func_80172AB4 */

typedef struct S_80172AB4_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_80172AB4_6;   /* globals in func_80172AB4 */



extern s32 func_8003F270();
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800DA840(u16 *, s32);

extern u8 D_80170E7C;
extern u8 D_80174D4C[];
extern u8 D_80174D94[];
extern u8 D_80174D9C[];
extern u8 D_80174DA4[];

/* Updates the actor's move, animation, and recovery state. */
void func_80172AB4(void *action_in, void *motion_in, void *sprite_in, void *actor_in)
{
    u8 *move_id;
    s32 state;
    s16 use_player;
    s32 move_kind;
    void *target;
    void *action = action_in;
    register void *motion ASM_REG("$20") = motion_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *sprite ASM_REG("$18") = sprite_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *actor ASM_REG("$17") = actor_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 target_x;
    u16 position[3];
    u16 ticks_left;

    ASM_KEEP4_NV(action, motion, sprite, actor);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

    state = ((S_80172AB4_0 *)action)->unk_9B;
    use_player = 0;
    if (state == 3) {
        goto state_3;
    }
    if (state < 4) {
        if (state == 1) {
            goto state_1;
        }
        if (state >= 2) {
            goto state_2;
        }
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    {
        s32 finish_state = 5;

        if (state == finish_state) {
            goto state_5;
        }
    }
    if ((s16)state < 5) {
        goto state_4;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    return;

state_0:
    if (((S_80172AB4_1 *)actor)->unk_1C & 0x2000) {
        move_kind = (((S_80172AB4_1 *)actor)->unk_46 & 0x3FFF) - 1;
        switch (move_kind) {
        case 0:
            goto kind_1;
        case 1:
            goto kind_2;
        case 2:
            goto kind_3;
        case 6:
            use_player = 1;
            goto kind_3;
        case 5:
            use_player = 1;
            goto kind_2;
        case 4:
            use_player = 1;
            goto kind_1;
        default:
            goto kind_none;
        }
    }

    move_kind = ((S_80172AB4_1 *)actor)->unk_46 & 0x3FFF;
    if (move_kind == 2) {
        goto kind_2;
    }
    if (move_kind < 3) {
        if (move_kind == 1) {
            goto kind_1;
        }
        move_id = 0;
        goto have_choice;
    }
    if (move_kind != 3) {
        move_id = 0;
        goto have_choice;
    }

kind_3:
    move_id = (u8 *)actor + 0xE;
    goto have_choice;
kind_2:
    move_id = (u8 *)actor + 0xB;
    goto have_choice;
kind_1:
    move_id = (u8 *)actor + 8;
    goto have_choice;
kind_none:
    move_id = 0;

have_choice:
    if (*move_id != 0) {
        ((S_80172AB4_0 *)action)->unk_98 &= 0xFF7F;
        {
            s32 player_target = use_player;

            if (player_target != 0) {
                target = D_800814A8;
                ((S_80172AB4_1 *)actor)->unk_60 = target;
                goto copy_existing;
            }
        }

        if (D_8006DE24[*move_id].kind == 2) {
            target = ((S_80172AB4_1 *)actor)->unk_60;
            if (target == 0) {
                goto move_setup;
            }
copy_existing:
            move_kind = (s32)((S_80172AB4_2_pre *)target)[-1].unk_00;
            ((S_80172AB4_1 *)actor)->unk_72.s = ((S_80172AB4_3 *)(void *)move_kind)->unk_24;
            ((S_80172AB4_1 *)actor)->unk_73.s = ((S_80172AB4_3 *)(void *)move_kind)->unk_25;
            goto apply_move;
        }

        ((S_80172AB4_1 *)actor)->unk_60 =
            func_800A05A4(actor,
                          ((S_80172AB4_4 *)sprite)->unk_24,
                          ((S_80172AB4_4 *)sprite)->unk_25,
                          ((S_80172AB4_1 *)actor)->unk_2A, 0x10);
        ((S_80172AB4_1 *)actor)->unk_72.s = abs(((S_80172AB4_1 *)actor)->unk_72.u);
        ((S_80172AB4_1 *)actor)->unk_73.s = abs(((S_80172AB4_1 *)actor)->unk_73.u);

move_setup:
apply_move:
        position[0] = ((S_80172AB4_5 *)motion)->unk_02;
        position[1] = ((S_80172AB4_5 *)motion)->unk_06;
        position[2] = ((S_80172AB4_5 *)motion)->unk_0A;
        if (func_800A94A0(actor, move_id, use_player,
                          (u16 *)((u8 *)action + 0x98)) == 0) {
            return;
        }
        ((S_80172AB4_4 *)sprite)->unk_14 &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DA840(position, (s16)(((s32)*move_id - 1) % 3));
        goto advance_state;
    }

    ((S_80172AB4_5 *)motion)->unk_14 = 0;
    ((S_80172AB4_5 *)motion)->unk_10 = 0;
    ((S_80172AB4_5 *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((S_80172AB4_4 *)sprite)->unk_24, ((S_80172AB4_4 *)sprite)->unk_25);
    dungeonStatus.unk_0C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(actor);
    ((S_80172AB4_1 *)actor)->unk_6D.s--;
    ((S_80172AB4_0 *)action)->unk_8C = &D_80170E7C;
    ((S_80172AB4_1 *)actor)->unk_73.s = 0;
    ((S_80172AB4_1 *)actor)->unk_72.s = 0;
    ((S_80172AB4_1 *)actor)->unk_46 &= 0x7FFF;
    return;

state_1:
    if (((S_80172AB4_4 *)sprite)->unk_14 & 0x8000) {
        ((S_80172AB4_0 *)action)->unk_9B = 3;
        return;
    }
    if (!(((S_80172AB4_4 *)sprite)->unk_14 & 0x6000)) {
        return;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174D9C;
    func_80047784(
        sprite,
        D_80174D9C[((gameWork.view.viewAngle + ((S_80172AB4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80172AB4_0 *)action)->unk_98 |= 8;
    ((S_80172AB4_1 *)actor)->unk_1C &= 0xF7FFFFFF;
    ((S_80172AB4_0 *)action)->unk_96 = 8;
    ((S_80172AB4_5 *)motion)->unk_14 = 0xFFF00000;
    goto advance_state;

state_2:
    ((S_80172AB4_5 *)motion)->unk_14 += 0x10000;
    ticks_left = ((S_80172AB4_0 *)action)->unk_96 - 1;
    ((S_80172AB4_0 *)action)->unk_96 = ticks_left;
    if ((s32)(ticks_left << 16) > 0) {
        return;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174DA4;
    func_80047784(
        sprite,
        D_80174DA4[((gameWork.view.viewAngle + ((S_80172AB4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80172AB4_5 *)motion)->unk_14 = 0;
    goto advance_state;

state_3:
    if (func_8003F270() != 0) {
        ((S_80172AB4_4 *)sprite)->unk_14 |= 0x800;
        return;
    }
    ((S_80172AB4_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_80172AB4_0 *)action)->unk_9B++;

state_4:
    if (!(((((S_80172AB4_4 *)sprite)->unk_04 == 1) &&
           (((S_80172AB4_4 *)sprite)->unk_14 & 0x1000)) ||
          (((S_80172AB4_4 *)sprite)->unk_14 & 0xE000))) {
        return;
    }
    ((S_80172AB4_0 *)action)->unk_96 = 3;
    ((S_80172AB4_0 *)action)->unk_98 |= 0x80;
    if (!(((S_80172AB4_4 *)sprite)->unk_14 & 0xE000)) {
        return;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174D9C;
    func_80047784(
        sprite,
        D_80174D9C[((gameWork.view.viewAngle + ((S_80172AB4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80172AB4_0 *)action)->unk_98 &= 0xFFF7;
    ((S_80172AB4_1 *)actor)->unk_1C |= 0x08000000;

advance_state:
    ((S_80172AB4_0 *)action)->unk_9B++;
    return;

state_5:
    if (!(((S_80172AB4_4 *)sprite)->unk_14 & 0xE000)) {
        return;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174D94;
    func_80047784(
        sprite,
        D_80174D94[((gameWork.view.viewAngle + ((S_80172AB4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80172AB4_0 *)action)->unk_9B = 0xFF;
    return;

state_ff:
    if (!(((S_80172AB4_4 *)sprite)->unk_14 & 0xE000)) {
        return;
    }
    ((S_80172AB4_5 *)motion)->unk_14 = 0;
    ((S_80172AB4_5 *)motion)->unk_10 = 0;
    ((S_80172AB4_5 *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((S_80172AB4_4 *)sprite)->unk_24, ((S_80172AB4_4 *)sprite)->unk_25);
    if (((S_80172AB4_4 *)sprite)->unk_2C != D_80174D4C) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174D4C;
        func_80047784(
            sprite,
            D_80174D4C[((gameWork.view.viewAngle + ((S_80172AB4_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
    {

        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A--;
    }
    ((S_80172AB4_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_80172AB4_0 *)action)->unk_8C = &D_80170E7C;
    func_800A4ACC(actor);
    if (((S_80172AB4_1 *)actor)->unk_6D.u > 0) {
        ((S_80172AB4_1 *)actor)->unk_6D.s--;
    }
    ((S_80172AB4_1 *)actor)->unk_73.s = 0;
    ((S_80172AB4_1 *)actor)->unk_72.s = 0;
    ((S_80172AB4_1 *)actor)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);

    return;
}
