#include "common.h"
#include "records/Rec_D_800E3D7C.h"

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

typedef struct S_8017472C_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 unk_48;
    u8 pad_49[0x17];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_8017472C_1;   /* arg3 in func_8017472C */

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
extern void func_80047784();
extern void *func_800A05A4();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A56E0();
extern s32 func_800A94A0();
extern void func_80171790();
extern void func_80171928();

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern void *D_80170850[];
extern u8 D_801724BC[];
extern u8 D_80175E24[];
extern u8 D_80175E2C[];
extern u8 D_80175E34[];

/* Updates an actor's action state, target coordinates, animation, and completion. */
void func_8017472C(void *action, void *transform, void *sprite, void *actor)
{
    static void *const kind_labels[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_none,
        &&special_1, &&special_2, &&special_3
    };
    s32 state;
    register s32 use_player_target;
    s32 kind;
    u8 *move;
    void *target;
    s32 target_x;
    s32 target_y;
    u16 ticks_left;
    s32 step;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
    if (((S_8017472C_1 *)actor)->unk_1C & 0x2000) {
        kind = (((S_8017472C_1 *)actor)->unk_46 & 0x3FFF) - 1;
        if ((u32)kind >= 7U) {
            goto kind_none;
        }
        (void)kind_labels;
        goto *D_80170850[kind];

special_3:
        use_player_target = 1;
        goto kind_3;
special_2:
        use_player_target = 1;
        goto kind_2;
special_1:
        use_player_target = 1;
        goto kind_1;
    }

    kind = ((S_8017472C_1 *)actor)->unk_46 & 0x3FFF;
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
            ((S_8017472C_1 *)actor)->unk_60 = target;
            goto record_setup;
        }

        if (D_8006DE24[*move * 20 + 0x12] == 2) {
            target = ((S_8017472C_1 *)actor)->unk_60;
            if (target == 0) {
                goto move_setup;
            }
record_setup:
            state = ((S_8017472C_2_pre *)target)[-1].unk_00;
            ((S_8017472C_1 *)actor)->unk_72.s = ((S_8017472C_3 *)state)->unk_24;
            ((S_8017472C_1 *)actor)->unk_73.s = ((S_8017472C_3 *)state)->unk_25;
            goto move_setup;
        }

        target = func_800A05A4(
            actor,
            ((S_8017472C_4 *)sprite)->unk_24,
            ((S_8017472C_4 *)sprite)->unk_25,
            ((S_8017472C_1 *)actor)->unk_2A,
            0x10);
        ((S_8017472C_1 *)actor)->unk_60 = target;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        target_x = ((S_8017472C_1 *)actor)->unk_72.u;
        target_y = ((S_8017472C_1 *)actor)->unk_73.u;
        if (target_x < 0) {
            target_x = -target_x;
        }
        if (target_y < 0) {
            target_y = -target_y;
        }
        ((S_8017472C_1 *)actor)->unk_72.s = target_x;
        ((S_8017472C_1 *)actor)->unk_73.s = target_y;

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

    ((Rec_D_800E3D7C *)transform)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)transform)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)transform)->unk_0C.as_s32 = 0;
    func_800A2B04(transform, ((S_8017472C_4 *)sprite)->unk_24, ((S_8017472C_4 *)sprite)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(actor);
    ((S_8017472C_1 *)actor)->unk_6D--;
    ((S_8017472C_0 *)action)->unk_8C = D_801724BC;
    ((S_8017472C_1 *)actor)->unk_73.s = 0;
    ((S_8017472C_1 *)actor)->unk_72.s = 0;
    ((S_8017472C_1 *)actor)->unk_46 &= 0x7FFF;
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
       /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
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

    ((Rec_D_800E3D7C *)transform)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)transform)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)transform)->unk_0C.as_s32 = 0;
    func_800A2B04(transform, ((S_8017472C_4 *)sprite)->unk_24, ((S_8017472C_4 *)sprite)->unk_25);

    kind = ((S_8017472C_1 *)actor)->unk_48;
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
            *(u8 *)((((D_80083228 + ((S_8017472C_1 *)actor)->unk_2A + 0x100) >> 9) & 7) + (u32)anim_table),
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
    ((S_8017472C_1 *)actor)->unk_73.s = 0;
    ((S_8017472C_1 *)actor)->unk_72.s = 0;
    ((S_8017472C_1 *)actor)->unk_6D--;
    ((S_8017472C_1 *)actor)->unk_46 &= 0x7FFF;
    func_800A56E0(0xB4);
}
