#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/entity.h"

typedef struct S_8017472C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x12];
    union { s16 s; u16 u; } unk_AE;   /* accessed as both */
} S_8017472C_0;   /* arg0 in func_8017472C */

typedef struct S_8017472C_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017472C_2_pre;   /* the 0x14 bytes before object in func_8017472C, addressed as object[-1] */

typedef struct S_8017472C_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017472C_3;   /* record in func_8017472C */

typedef struct S_8017472C_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8017472C_4;   /* arg2 in func_8017472C */


typedef struct S_8017472C_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_8017472C_6;   /* control in func_8017472C */



extern s32 func_8003F270();
extern int abs(int);
extern void func_80047784();
extern void *func_800A05A4();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern s32 func_800A94A0();
extern void func_80171790();
extern void func_80171928();

extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_801724BC[];
extern u8 D_80175E24[];
extern u8 D_80175E2C[];
extern u8 D_80175E34[];

/* Updates an actor's action state, target coordinates, animation, and completion. */
void func_8017472C(void *action, EntityRec *transform, void *sprite, EntityRec *actor)
{
    s32 state;
    register s32 use_player_target;
    s32 kind;
    u8 *move;
    void *target;
    s32 target_x;
    s32 target_y;
    u16 ticks_left;
    s32 step;
    u8 *anim_table;
    void *current_anim;
    s32 delay_slot;
    u8 *control;

    state = ((S_8017472C_0 *)action)->unk_9B;
    use_player_target = 0;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    return;

state_0:
    if (((u32)actor->flags1C) & 0x2000) {
        kind = (actor->unk_46 & 0x3FFF) - 1;
        switch (kind) {
        case 0:
            goto kind_1;
        case 1:
            goto kind_2;
        case 2:
            goto kind_3;
        case 6:
            use_player_target = 1;
            goto kind_3;
        case 5:
            use_player_target = 1;
            goto kind_2;
        case 4:
            use_player_target = 1;
            goto kind_1;
        default:
            goto kind_none;
        }
    }

    kind = actor->unk_46 & 0x3FFF;
    if (kind == 2) {
        goto kind_2;
    }
    if (kind < 3) {
        if (kind == 1) {
            goto kind_1;
        }
        move = 0;
        goto choice_ready;
    }
    if (kind != 3) {
        goto kind_none;
    }

kind_3:
    move = (u8 *)actor + 0xE;
    goto choice_ready;
kind_2:
    move = (u8 *)actor + 0xB;
    goto choice_ready;
kind_1:
    move = (u8 *)actor + 8;
    goto choice_ready;

kind_none:
    move = 0;

choice_ready:
    if (*move != 0) {
        ((S_8017472C_0 *)action)->unk_98 &= 0xFF7F;
        if (use_player_target != 0) {
            target = D_800814A8;
            actor->target = target;
            goto record_setup;
        }

        if (D_8006DE24[*move].kind == 2) {
            target = actor->target;
            if (target == 0) {
                goto move_setup;
            }
record_setup:
            state = ((S_8017472C_2_pre *)target)[-1].unk_00;
            actor->unk_72 = ((S_8017472C_3 *)state)->unk_24;
            actor->unk_73 = ((S_8017472C_3 *)state)->unk_25;
            goto move_setup;
        }

        target = func_800A05A4(
            actor,
            ((S_8017472C_4 *)sprite)->unk_24,
            ((S_8017472C_4 *)sprite)->unk_25,
            actor->facing,
            0x10);
        actor->target = target;
        actor->unk_72 =
            abs(actor->unk_72);
        actor->unk_73 =
            abs(actor->unk_73);

move_setup:
        if (func_800A94A0(actor, move, use_player_target,
                          (u8 *)action + 0x98) == 0) {
            return;
        }
        ((S_8017472C_0 *)action)->unk_96.s = 0x16;
        ((S_8017472C_0 *)action)->unk_AE.s = 0xE;
        ((S_8017472C_0 *)action)->unk_9B++;
        return;
    }

    transform->flags14 = 0;
    transform->unk_10 = 0;
    transform->unk_0C = 0;
    func_800A2B04(transform, ((S_8017472C_4 *)sprite)->unk_24, ((S_8017472C_4 *)sprite)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(actor);
    (*(u8 *)&actor->unk_6D)--;
    ((S_8017472C_0 *)action)->unk_8C = D_801724BC;
    actor->unk_73 = 0;
    actor->unk_72 = 0;
    actor->unk_46 &= 0x7FFF;
    return;

state_1:
    if (func_8003F270() != 0) {
        ((S_8017472C_4 *)sprite)->unk_14 |= 0x800;
        return;
    }
    ((S_8017472C_4 *)sprite)->unk_14 &= 0xF7FF;
    ((S_8017472C_0 *)action)->unk_9B++;
    func_800A56E0(0x703);

state_2:
    step = 0;
    if (!(((S_8017472C_0 *)action)->unk_96.s & 1) &&
        ((S_8017472C_0 *)action)->unk_AE.s != 0) {
        ((S_8017472C_0 *)action)->unk_AE.u--;
    }
    for (step = 0; step < 10; step++) {
        func_80171790(action, transform, sprite, actor);
    }

    if (((S_8017472C_0 *)action)->unk_96.u == 0x16) {
        func_80171928(action, transform, sprite);
    }
    ticks_left = ((S_8017472C_0 *)action)->unk_96.s - 1;
    ((S_8017472C_0 *)action)->unk_96.s = ticks_left;
    if ((s32)(ticks_left << 16) > 0 &&
        !(((S_8017472C_4 *)sprite)->unk_14 & 0xE000)) {
        return;
    }
    ((S_8017472C_0 *)action)->unk_98 |= 0x80;
    ((S_8017472C_0 *)action)->unk_9B++;
    return;

state_3:
    if (D_8008346C == 0) {
        ((S_8017472C_0 *)action)->unk_96.s = 0;
    }
    if (!(((S_8017472C_4 *)sprite)->unk_14 & 0xE000)) {
        return;
    }

    transform->flags14 = 0;
    transform->unk_10 = 0;
    transform->unk_0C = 0;
    func_800A2B04(transform, ((S_8017472C_4 *)sprite)->unk_24, ((S_8017472C_4 *)sprite)->unk_25);

    kind = actor->unk_48;
    if (kind == 0xE) {
        goto state3_kind_e;
    }
    if (kind < 0xF) {
        if (kind == 0xD) {
            goto state3_kind_d;
        }
        {
            current_anim = (u8 *)&D_80083460;
            control = current_anim;
            goto control_ready;
        }
    }
    if (kind == 0xF) {
        goto state3_kind_f;
    }
    {
        current_anim = (u8 *)&D_80083460;
        control = current_anim;
        goto control_ready;
    }

state3_kind_d:
        current_anim = ((S_8017472C_4 *)sprite)->unk_2C;
        anim_table = D_80175E24;
        goto table_ready;
state3_kind_e:
        current_anim = ((S_8017472C_4 *)sprite)->unk_2C;
        anim_table = D_80175E2C;
        goto table_ready;
state3_kind_f:
        current_anim = ((S_8017472C_4 *)sprite)->unk_2C;
        anim_table = D_80175E34;

table_ready:
    if (current_anim != anim_table) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(
            sprite,
            *(u8 *)((((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7) + (u32)anim_table),
            0);
    }

    control = (u8 *)&D_80083460;
control_ready:
    if (((S_8017472C_6 *)control)->unk_0C != 0) {
        return;
    }
    ((S_8017472C_6 *)control)->unk_0A--;
    ((S_8017472C_0 *)action)->unk_8C = D_801724BC;
    func_800A4ACC(actor);
    actor->unk_73 = 0;
    actor->unk_72 = 0;
    (*(u8 *)&actor->unk_6D)--;
    actor->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);
}
