#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
extern int abs(int);

typedef struct S_80172970_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172970_0;   /* arg0 in func_80172970 */

typedef struct S_80172970_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80172970_2_pre;   /* the 0x14 bytes before object in func_80172970, addressed as object[-1] */

typedef struct S_80172970_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172970_3;   /* record in func_80172970 */

typedef struct S_80172970_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172970_4;   /* arg2 in func_80172970 */




extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4();
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);

extern u8 D_80170838[16];
extern u8 D_8017140C[];
extern u8 D_8017586C[];

/* Starts the selected move, waits for completion, and resets the actor's action state. */
void func_80172970(void *action, EntityRec *position, void *sprite, EntityRec *actor)
{
    static void *const switch_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_none,
        &&special_1, &&special_2, &&special_3
    };
    s32 phase;
    s16 is_special;
    s32 special_check;
    s32 move_kind;
    u8 *move_data;
    void *target;
    s8 target_x;
    s8 target_y;
    u16 recovery_ticks;

    phase = ((S_80172970_0 *)action)->unk_9B;
    is_special = 0;
    if (phase == 1) {
        goto state_1;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto state_0;
        }
        return;
    }
    if (phase == 2) {
        goto state_2;
    }
    return;

state_0:
    if (((u32)actor->flags1C) & 0x2000) {
        move_kind = (actor->unk_46 & 0x3FFF) - 1;
        if ((u32)move_kind >= 7U) {
            goto kind_none;
        }
        (void)switch_keep;
        goto *(((void **)D_80170838)[move_kind]);

special_3:
        is_special = 1;
        goto kind_3;
special_2:
        is_special = 1;
        goto kind_2;
special_1:
        is_special = 1;
        goto kind_1;
    }

    move_kind = actor->unk_46 & 0x3FFF;
    if (move_kind == 2) {
        goto kind_2;
    }
    if (move_kind < 3) {
        if (move_kind == 1) {
            goto kind_1;
        }
        move_data = 0;
        goto have_choice;
    }
    if (move_kind != 3) {
        move_data = 0;
        goto have_choice;
    }

kind_3:
    move_data = (u8 *)actor + 0xE;
    goto have_choice;
kind_2:
    move_data = (u8 *)actor + 0xB;
    goto have_choice;
kind_1:
    move_data = (u8 *)actor + 8;
    goto have_choice;
kind_none:
    move_data = 0;

have_choice:
    if (*move_data != 0) {
        ((S_80172970_0 *)action)->unk_98 &= 0xFF7F;
        special_check = is_special;
        if (special_check != 0) {
            target = D_800814A8;
            actor->target = target;
            goto copy_existing;
        }

        if (D_8006DE24[*move_data].kind == 2) {
            target = actor->target;
            if (target == 0) {
                goto move_setup;
            }
copy_existing:
            phase = ((S_80172970_2_pre *)target)[-1].unk_00;
            actor->unk_72 = ((S_80172970_3 *)phase)->unk_24;
            actor->unk_73 = ((S_80172970_3 *)phase)->unk_25;
            goto apply_move;
        }

        actor->target =
            func_800A05A4(actor,
                          ((S_80172970_4 *)sprite)->unk_24,
                          ((S_80172970_4 *)sprite)->unk_25,
                          actor->facing, 0x10);
        target_x = actor->unk_72;
        target_y = actor->unk_73;
        target_x = abs(target_x);
        target_y = abs(target_y);
        actor->unk_72 = target_x;
        actor->unk_73 = target_y;

move_setup:
apply_move:
        ((S_80172970_0 *)action)->unk_98 |= 0x1000;
        if (func_800A94A0(actor, move_data, is_special,
                          (u16 *)((u8 *)action + 0x98)) == 0) {
            return;
        }
        ((S_80172970_4 *)sprite)->unk_14 &= 0xF7FF;
        func_800A56E0(0x703);
        ((S_80172970_0 *)action)->unk_96 = 0xE;
        ((S_80172970_0 *)action)->unk_9B++;
        return;
    }

    position->flags14 = 0;
    position->unk_10 = 0;
    position->unk_0C = 0;
    func_800A2B04(position, ((S_80172970_4 *)sprite)->unk_24, ((S_80172970_4 *)sprite)->unk_25);
    dungeonStatus.unk_0C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(actor);
    (*(u8 *)&actor->unk_6D)--;
    ((S_80172970_0 *)action)->unk_8C = D_8017140C;
    actor->unk_73 = 0;
    actor->unk_72 = 0;
    actor->unk_46 &= 0x7FFF;
    return;

state_1:
    if (func_8003F270() != 0) {
        ((S_80172970_4 *)sprite)->unk_14 |= 0x800;
        return;
    }
    ((S_80172970_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_80172970_0 *)action)->unk_9B++;

state_2:
    recovery_ticks = ((S_80172970_0 *)action)->unk_96 - 1;
    ((S_80172970_0 *)action)->unk_96 = recovery_ticks;
    if ((s32)(recovery_ticks << 16) > 0) {
        if (!(((S_80172970_4 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
    }
    ((S_80172970_0 *)action)->unk_98 |= 0x80;
    if (!(((S_80172970_4 *)sprite)->unk_14 & 0xE000)) {
        return;
    }
    position->flags14 = 0;
    position->unk_10 = 0;
    position->unk_0C = 0;
    func_800A2B04(position, ((S_80172970_4 *)sprite)->unk_24, ((S_80172970_4 *)sprite)->unk_25);
    if (((S_80172970_4 *)sprite)->unk_2C != D_8017586C) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8017586C;
        func_80047784(
            sprite,
            D_8017586C[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    }
    {

        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A--;
    }
    ((S_80172970_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_80172970_0 *)action)->unk_8C = D_8017140C;
    func_800A4ACC(actor);
    if (actor->unk_6D > 0) {
        (*(u8 *)&actor->unk_6D)--;
    }
    actor->unk_73 = 0;
    actor->unk_72 = 0;
    actor->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);

    return;
}

/* MECHANISM: The 0x38 frame naturally holds args in s3/s4/s2/s1, with s5 state and s0 choice.
   Carrying the loaded object through the copy join removes a redundant lw+nop pair.
   A kept special-test copy restores move v0,s5; a schedule fence orders the result store.
   Holding the copied record in v1 closes the final four register-field substitutions. */
