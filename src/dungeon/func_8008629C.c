#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_8008B9FC_1 {
    u8 pad_00[0x8C];
    union { s32 s; void * u; } unk_8C;   /* accessed as both */
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
} S_8008B9FC_1;   /* arg0 in func_8008B9FC */


typedef struct S_8008B9FC_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0xBC];
    s16 unk_C8;
} S_8008B9FC_3;   /* state in func_8008B9FC */

typedef struct S_8008B9FC_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008B9FC_4;   /* tail_word_obj in func_8008B9FC */

typedef struct S_8008B9FC_5 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008B9FC_5;   /* callback_obj in func_8008B9FC */

typedef struct S_8008B9FC_6 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8008B9FC_6;   /* callback_obj_f0 in func_8008B9FC */

typedef struct S_8008B9FC_7_pre {
    s16 unk_00;
    u8 pad_02[0x23A];
} S_8008B9FC_7_pre;   /* the 0x23C bytes before D_80083464 in func_8008B9FC, addressed as D_80083464[-1] */



extern u8 D_8006CCD8[16];
extern u8 D_8006CCE8[16];
extern volatile u16 D_80013714[];
extern u8 D_80083160[];
extern s16 D_80083228[];
extern u16 D_80083460[];
extern s16 D_80083464[];
extern u8 D_800DCFB0[];
extern u8 D_800DCFB8[];
extern u8 D_800DCFC0[];
extern u8 D_800DCFE8[];
extern u8 D_800DD030[];
extern u8 D_800DD0D0[];
extern u8 D_800E3544[];

extern void D_8008ACDC(void);
extern void func_80048A44();
extern void func_8008CD4C();
extern void func_8008E264();
extern void func_80094ED4();
extern void func_80099F04();
extern void func_80099F70();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s16 func_8009ABA0();
extern void func_8009F644();
extern s32 func_800A5C70();
extern void func_800A67F4();

/* Update movement state, position, and animation from the movement result. */
void func_8008B9FC(S_8008B9FC_1 *move_state, s32 actor_id, Rec_D_80082E80 *sprite, Rec_D_800E3D7C *actor) {
    u8 *dungeon_state = D_80083160;
    u8 *alt_anim;
    u16 *flags;
    u16 *check_flags;
    s16 move_result;
    u16 direction_index;
    register s32 update_mask;
    s32 actor_flags;
    u16 blocked_ticks;

    move_result = func_8009ABA0(actor->unk_2A.as_s16, actor_id, sprite,
                            actor->unk_88.as_s16, 0x20);
    if (move_result > 0) {
        move_state->unk_9B = 0;
        func_8009A3D0(sprite->unk_24, sprite->unk_25, 0x300);
        direction_index = ((u16)actor->unk_2A.as_s16 >> 8) & 0xE;
        {
            u8 x = sprite->unk_24;
            u8 *movement_x = D_8006CCD8;
            x = (u8)(x + movement_x[direction_index]);
            sprite->unk_24 = x;
        }
        sprite->unk_25 =
            (u8)(sprite->unk_25 + D_8006CCE8[direction_index]);
        func_8009A21C(sprite->unk_24, sprite->unk_25, 0x300);
        flags = D_80083460;
        flags[1] |= 8;
        move_state->unk_8C.s = 0;

        if (move_result != 4) {
            if ((D_80013714[0] & 2) ||
                (((((S_8008B9FC_3 *)dungeon_state)->unk_08 & 0x20) != 0) &&
                 ((move_state->unk_A2 & 0x100) == 0) &&
                 func_800A5C70())) {
                flags[1] |= 0x80;
                if (sprite->unk_2C.as_pu8 != D_800DCFC0) {
                    sprite->unk_2C.as_pu8 = D_800DCFC0;
                    func_80048A44(
                        sprite,
                        D_800DCFC0[((s32)(((S_8008B9FC_3 *)dungeon_state)->unk_C8 +
                                         actor->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0, 1);
                }
            }
        }

        check_flags = D_80083460;
        if ((check_flags[1] & 0x80) || (move_result == 1)) {
            func_80099F70(actor->unk_5C);
            func_80099F04(actor->unk_5C);
            if (!(check_flags[1] & 0x80) &&
                ((D_800E3544[0] == 8) || (D_800E3544[0] == 0))) {
                if (sprite->unk_2C.as_pu8 != D_800DCFB8) {
                    void *anim_sprite;
                    anim_sprite = sprite;
                    sprite->unk_2C.as_pu8 = D_800DCFB8;
                    func_80048A44(
                        anim_sprite,
                        D_800DCFB8[((s32)(D_80083228[0] +
                                         actor->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0, 1);
                }
            }
            move_state->unk_9A = 0xF;
            D_80083464[0] = 8;
            goto finish_step;
        }

        move_state->unk_98 |= 0xC;
        if (move_result < 4) {
            move_state->unk_A2 |= 1;
        } else if ((move_result == 2) || (move_result == 4)) {
            move_state->unk_9B = 8;
        }
        func_80094ED4(move_state, actor_id, sprite, actor);
        D_80083464[0] = 8;
        if (sprite->unk_2C.as_pu8 == D_800DCFB8) {
            sprite->unk_14.at00_u16.v |= 0x6000;
            func_8008E264(move_state, actor_id, sprite, actor);
        } else {
            sprite->unk_2C.as_pu8 = D_800DD030;
            func_80048A44(
                sprite,
                D_800DD030[((s32)(D_80083228[0] + actor->unk_2A.as_s16 +
                                  0x100) >> 9) & 7],
                0, 1);
        }
        move_state->unk_9A = 0x10;
        {
            register void *flag_actor;
            flag_actor = actor;
            ((S_8008B9FC_4 *)flag_actor)->unk_1C |= 0x40000000;
        }
        func_8009F644(actor, 8, 0, 0);
        return;

finish_step:
        func_8009F644(actor, 8, 0, 0);
        update_mask = 0x40000000;
        goto update_step;
    }

    if (move_result < 0) {
        if ((D_80013714[0] & 1) ||
            (blocked_ticks = move_state->unk_96 + 1,
             move_state->unk_96 = blocked_ticks,
             (s16)blocked_ticks >= 0x15)) {
            func_8008CD4C(move_state, actor_id, sprite, actor, (s32)move_result);
            if (move_state->unk_9B >= 0x10) {
                actor->unk_1C.as_s32 |= 0x40000000;
                return;
            }
        }
        return;
    }

    {
        register void *idle_sprite;
        idle_sprite = sprite;
        ((S_8008B9FC_5 *)idle_sprite)->unk_2C = D_800DCFB0;
        func_80048A44(
            idle_sprite,
            D_800DCFB0[((s32)(((S_8008B9FC_3 *)dungeon_state)->unk_C8 +
                              actor->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0, 1);
    }
    move_state->unk_8C.u = D_8008ACDC;
    return;

update_step:
    actor_flags = actor->unk_1C.as_s32 | update_mask;
    actor->unk_1C.as_s32 = actor_flags;
    ASM_KEEP(actor_flags);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    flags = D_80083460;
    flags[1] |= 0x812;
    func_800A67F4();
    func_80094ED4(move_state, actor_id, sprite, actor);
    if (!(D_80013714[0] & 8)) {
        return;
    }

    if (D_800E3544[0] == 0xF0) {
        if (sprite->unk_2C.as_pu8 == D_800DCFC0) {
            goto halve_flags;
        }
        {
            void *turn_sprite;
            turn_sprite = sprite;
            ((S_8008B9FC_6 *)turn_sprite)->unk_2C = D_800DCFC0;
            func_80048A44(
                turn_sprite,
                *(volatile u8 *)(D_800DCFC0 +
                    (((s32)(((S_8008B9FC_7_pre *)D_80083464)[-1].unk_00 +
                              actor->unk_2A.as_s16 + 0x100) >> 9) & 7)),
                0, 1);
        }
        ASM_SCHED_BARRIER(); /* MATCH: keep the F0 callback call separate from the F8 arm. */
        goto halve_flags;
    }

    if (D_800E3544[0] == 0xF8) {
        alt_anim = D_800DCFB8 + 8;
        move_state->unk_A2 |= 0x100;
        flags[5]++;
        if (sprite->unk_2C.as_pu8 == alt_anim) {
            goto halve_flags;
        }
        sprite->unk_2C.as_pu8 = alt_anim;
        func_80048A44(
            sprite,
            alt_anim[((s32)(D_80083228[0] + actor->unk_2A.as_s16 +
                                 0x100) >> 9) & 7],
            0, 1);
        goto halve_flags;
    }

    if (D_800E3544[0] == 0xE8) {
        sprite->unk_2C.as_pu8 = D_800DCFE8;
        func_80048A44(
            sprite,
            D_800DCFE8[((s32)(D_80083228[0] + actor->unk_2A.as_s16 +
                               0x100) >> 9) & 7],
            1, 1);
        func_8009A3D0(sprite->unk_24, sprite->unk_25, 0x300);
        direction_index = ((u16)actor->unk_2A.as_s16 >> 8) & 0xE;
        sprite->unk_24 -= ((s16 *)(void *)D_8006CCD8)[direction_index / 2] * 2;
        sprite->unk_25 -= ((s16 *)(void *)D_8006CCE8)[direction_index / 2] * 2;
        func_8009A21C(sprite->unk_24, sprite->unk_25, 0x300);
halve_flags:
        flags[2] = (s16)flags[2] >> 1;
        return;
    }

    if (D_800E3544[0] == 0xE0) {
        sprite->unk_2C.as_pu8 = D_800DD0D0;
        func_80048A44(
            sprite,
            D_800DD0D0[((s32)(D_80083228[0] + actor->unk_2A.as_s16 +
                               0x100) >> 9) & 7],
            1, 1);
        func_8009A3D0(sprite->unk_24, sprite->unk_25, 0x300);
        direction_index = ((u16)actor->unk_2A.as_s16 >> 8) & 0xE;
        {
            u8 x = sprite->unk_24;
            u8 *movement_x = D_8006CCD8;
            x = (u8)(x - movement_x[direction_index]);
            sprite->unk_24 = x;
        }
        sprite->unk_25 -= D_8006CCE8[direction_index];
        func_8009A21C(sprite->unk_24, sprite->unk_25, 0x300);
    }
}
