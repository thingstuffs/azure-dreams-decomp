#include "common.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

extern s32 func_8009A180();
extern void func_8009A21C();
extern void func_8009A3D0();
extern s32 func_8009A540();
extern s32 func_8009A66C();
extern s32 func_8009FD7C();
extern void *func_800A02AC();
extern void *func_800A04F0();
extern u16 func_800A0818();
extern void func_800A0E6C();
extern void func_800A19E4();
extern s32 func_800A6D30();
extern void func_800A9A0C();
extern s16 func_800BCB04();
extern s32 func_80171F24();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_8006CD00[8];
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s32 D_80083460;
extern s8 D_800E2970[];

/* Updates actor movement, choosing a direction and recording its path. */
void func_80171768(u8 *move_work_in, void *entry_context, u8 *position_in, u8 *actor_in)
{
    register u8 *move_work ASM_REG("$21") = move_work_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *position ASM_REG("$19") = position_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *actor ASM_REG("$18") = actor_in;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 limit_turn;
    s16 step_index;
    s16 *angle_steps;
    u8 *state;
    void *target_link;
    u16 state_flags;
    s32 actor_flags;
    s32 random_turn;
    register s32 current_angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 turn_limit;
    s32 trial_angle;

    state = (u8 *)&D_80083460;
    state_flags = U16_AT(state, 2);
    ASM_KEEP(move_work);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    limit_turn = 0;

    if (state_flags & 0x4000) {
        goto check_entry;
    }
    if (S8_AT(actor, 0x71) < 0) {
        goto negative_entry;
    }

check_entry:
    if (U8_AT(actor, 0x12) >= 2) {
        goto reject_entry;
    }
    if ((func_80171F24(move_work, entry_context, position, actor) << 16) != 0) {
        goto accepted_entry;
    }

reject_entry:
    func_800A9A0C(actor);
    goto done;

accepted_entry:
    if (PTR_AT(state, 0xC) == actor) {
        U16_AT(actor, 0x46) = 0xC008;
    }
    goto done;

negative_entry:
    if (!(state_flags & 0x2000)) {
        goto done;
    }

    func_800A19E4(position, actor, 3, 6, move_work + 0x9C);
    actor_flags = S32_AT(actor, 0x1C);
    if (!(actor_flags & 0x410)) {
        goto check_mode_2000;
    }
    if (!(actor_flags & 0x400)) {
        goto mode_410_without_400;
    }

    target_link = func_800A02AC(actor, U8_AT(position, 0x24), U8_AT(position, 0x25));
    if (target_link != 0) {
        goto found_actor;
    }
    {
        register s32 turn_flags ASM_REG("$2") = S32_AT(actor, 0x14);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        if (turn_flags < 0) {
            goto zero_counter;
        }
        S32_AT(actor, 0x14) = turn_flags | 0x80000000;
    }
    random_turn = func_800A6D30();
    U16_AT(actor, 0x2A) += (random_turn & 7) << 9;
    goto zero_counter;

mode_410_without_400:
    if (func_800A04F0(actor, U8_AT(position, 0x24), U8_AT(position, 0x25),
                      S16_AT(actor, 0x2A)) == 0) {
        goto loop_setup;
    }
    goto clear_path;

check_mode_2000:
    if (!(actor_flags & 0x2000)) {
        goto check_tile_kind;
    }
    if (U16_AT(actor, 0x46) & 0x8000) {
        goto loop_setup;
    }
    if (!(actor_flags & 0x20000)) {
        goto invoke_fallback;
    }

    {
        s32 direction;
        s32 offset;
        s32 target_x;
        s32 target_y;
        u8 *target = D_80082E80;

        direction = (U8_AT(actor, 0x45) +
                     ((s32)(U16_AT(D_800814A8, 0x2A) << 16) >> 25)) & 7;
        offset = direction * 2;
        target_x = U8_AT(target, 0x24) + U16_AT(&D_8006CCD8, offset);
        target_y = U8_AT(target, 0x25) + U16_AT(&D_8006CCE8, offset);
        if ((U8_AT(position, 0x24) == (u16)target_x) &&
            (U8_AT(position, 0x25) == (u16)target_y)) {
            goto clear_path;
        }

        {
            u8 *angle_work = move_work + 0x98;
            s16 next_angle = func_800A0818(
                U8_AT(position, 0x24), U8_AT(position, 0x25),
                (s16)target_x, (s16)target_y, angle_work);

            U16_AT(actor, 0x2A) = next_angle;
            if ((func_8009A66C(next_angle, position, actor, 0x20) << 16) <= 0) {
                u8 *fallback = (u8 *)&D_80082EA4 - 0x24;

                U16_AT(actor, 0x2A) = func_800A0818(
                    U8_AT(position, 0x24), U8_AT(position, 0x25),
                    U8_AT(fallback, 0x24), U8_AT(fallback, 0x25), angle_work);
            }
        }
    }
    {
        u8 *target = (u8 *)&D_80082EA4 - 0x24;

        if ((func_8009FD7C(
                 U8_AT(position, 0x24), U8_AT(position, 0x25),
                 U8_AT(target, 0x24), U8_AT(target, 0x25)) << 16) != 0) {
            limit_turn = 1;
        }
    }
    goto loop_setup;

check_tile_kind:
    {
        s32 tile_kind;
        s32 offset;
        u8 *tile_table;

        tile_kind = S8_AT(position, 0x26);
        if (tile_kind >= 0) {
            tile_table = (u8 *)&D_800E2970;
            offset = tile_kind * 0x14;
            offset += (s32)tile_table;
            if (U16_AT((u8 *)offset, 0xC) & 2) {
                goto invoke_fallback;
            }
        }
    }
    if (U16_AT(actor, 0x46) & 0x8000) {
        goto loop_setup;
    }

    target_link = func_800A02AC(actor, U8_AT(position, 0x24), U8_AT(position, 0x25));
    if (!(U16_AT(move_work, 0x98) & 0x8000)) {
        goto zero_counter;
    }
    if (target_link == 0) {
        goto loop_setup;
    }
    if ((func_8009A540(
             ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
             U8_AT(position, 0x24), U8_AT(position, 0x25),
             (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) != 0) {
        goto found_actor;
    }
    goto found_retry;

found_actor:
    {
        u8 *target_actor = PTR_AT(target_link, -0x14);
        register u8 *angle_work ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(target_actor);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        angle_work = move_work + 0x98;

        U16_AT(actor, 0x2A) = func_800A0818(
            U8_AT(position, 0x24), U8_AT(position, 0x25),
            U8_AT(target_actor, 0x24), U8_AT(target_actor, 0x25), angle_work);
        U8_AT(actor, 0x71) &= 0x7F;
        goto done;
    }

found_retry:
    if (func_800A04F0(actor, U8_AT(position, 0x24), U8_AT(position, 0x25),
                      S16_AT(actor, 0x2A)) != 0) {
        if ((func_8009A540(
                 ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
                 U8_AT(position, 0x24), U8_AT(position, 0x25),
                 (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) != 0) {
            goto clear_path;
        }
    }
    if (!(S32_AT(actor, 0x1C) & 0x20000)) {
        goto invoke_fallback;
    }
    {
        u8 *goal = (u8 *)&D_80082EA4 - 0x24;
        u8 *angle_work = move_work + 0x98;

        U16_AT(actor, 0x2A) = func_800A0818(
            U8_AT(position, 0x24), U8_AT(position, 0x25),
            U8_AT(goal, 0x24), U8_AT(goal, 0x25), angle_work);
        if ((func_8009FD7C(
                 U8_AT(position, 0x24), U8_AT(position, 0x25),
                 U8_AT(goal, 0x24), U8_AT(goal, 0x25)) << 16) == 0) {
            goto loop_setup;
        }
        if ((func_8009A540(
                 ((S16_AT(actor, 0x2A) >> 9) & 0xFFFF),
                 U8_AT(position, 0x24), U8_AT(position, 0x25),
                 (s16)(U16_AT(actor, 0x88) - 0x20)) << 16) == 0) {
            goto loop_setup;
        }
    }
    goto clear_path;

invoke_fallback:
    func_800A0E6C(position, S8_AT(move_work, 0x9C), actor, move_work + 0x98);

zero_counter:

loop_setup:
    step_index = 0;
    angle_steps = D_8006CD00;

    for (; step_index < 8; step_index++) {
        current_angle = S16_AT(actor, 0x2A);
        if (U16_AT(move_work, 0x98) & 2) {
            trial_angle = current_angle - angle_steps[step_index];
        } else {
            trial_angle = current_angle + angle_steps[step_index];
        }
        if ((func_8009A66C((s16)trial_angle, position, actor, 0x20) << 16) > 0) {
            if (step_index >= 3) {
                turn_limit = limit_turn;
                ASM_KEEP(turn_limit);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                if (turn_limit != 0) {
                    goto clear_path;
                }
            }
            U16_AT(actor, 0x2A) = trial_angle;
            {
                u8 *path_slot;

                path_slot = actor;
                path_slot += U8_AT(actor, 0x71) & 0x7F;
                U8_AT(path_slot, 0x74) = U8_AT(position, 0x24);
                path_slot = actor;
                path_slot += U8_AT(actor, 0x71) & 0x7F;
                U8_AT(path_slot, 0x7C) = U8_AT(position, 0x25);
            }
            U8_AT(actor, 0x71)++;

            func_8009A3D0(
                U8_AT(position, 0x24), U8_AT(position, 0x25),
                (S32_AT(actor, 0x1C) & 0x2000) ? 0x300 : 0x3000);

            {
                s32 move_offset = (U16_AT(actor, 0x2A) >> 8) & 0xE;
                register u8 *x_steps ASM_REG("$3") = (u8 *)&D_8006CCD8;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                U8_AT(position, 0x24) += U8_AT(x_steps, move_offset);
                U8_AT(position, 0x25) += U8_AT(&D_8006CCE8, move_offset);
            }
            func_8009A21C(
                U8_AT(position, 0x24), U8_AT(position, 0x25),
                (S32_AT(actor, 0x1C) & 0x2000) ? 0x300 : 0x3000);
            break;
        }

        if ((step_index == 0) &&
            (U16_AT(&D_80082EA4, 0) != U16_AT(position, 0x24)) &&
            ((func_8009A180(
                  actor, S32_AT(D_800814A8, 0x58) + 0x20) << 16) != 0)) {
            goto done;
        }
    }

post_loop_test:
    if (step_index >= 8) {
        U8_AT(actor, 0x71) &= 0x7F;
        U16_AT(actor, 0x46) &= 0x7FFF;
        func_800A9A0C(actor);
        goto done;
    }

    U16_AT(actor, 0x46) &= 0x7FFF;
    U8_AT(move_work, 0x9C) = U8_AT(position, 0x26);
    U8_AT(actor, 0x6D)--;
    {
        u8 *move_state = (u8 *)&D_80083460;

        U16_AT(move_state, 8)++;
    }
    if (S8_AT(actor, 0x6D) != 0) {
        goto actor_survives;
    }

clear_path:
    U8_AT(actor, 0x71) &= 0x7F;
    goto done;

actor_survives:
    step_index = func_800BCB04(
        (U8_AT(position, 0x24) << 6) | 0x20,
        (U8_AT(position, 0x25) << 6) | 0x20,
        (s16)(U16_AT(actor, 0x88) - 0x20));
    if (step_index < 0x200) {
        U16_AT(actor, 0x88) = step_index;
    }
    goto done;

done:
    return;
}
