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

void func_80171768(u8 *in0, void *arg1, u8 *in2, u8 *in3)
{
    register u8 *arg0 ASM_REG("$21") = in0;
    register u8 *arg2 ASM_REG("$19") = in2;
    register u8 *arg3 ASM_REG("$18") = in3;
    register s32 special ASM_REG("$22");
    s16 counter;
    s16 *angle_steps;
    u8 *state;
    void *found;
    u16 state_flags;
    s32 actor_flags;
    s32 call_result;
    register s32 current_angle ASM_REG("$3");
    register s32 special_test ASM_REG("$2");
    s32 trial;

    state = (u8 *)&D_80083460;
    state_flags = U16_AT(state, 2);
    ASM_KEEP(arg0);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);
    special = 0;

    if (state_flags & 0x4000) {
        goto check_entry;
    }
    if (S8_AT(arg3, 0x71) < 0) {
        goto negative_entry;
    }

check_entry:
    if (U8_AT(arg3, 0x12) >= 2) {
        goto reject_entry;
    }
    if ((func_80171F24(arg0, arg1, arg2, arg3) << 16) != 0) {
        goto accepted_entry;
    }

reject_entry:
    func_800A9A0C(arg3);
    goto done;

accepted_entry:
    if (PTR_AT(state, 0xC) == arg3) {
        U16_AT(arg3, 0x46) = 0xC008;
    }
    goto done;

negative_entry:
    if (!(state_flags & 0x2000)) {
        goto done;
    }

    func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
    actor_flags = S32_AT(arg3, 0x1C);
    if (!(actor_flags & 0x410)) {
        goto check_mode_2000;
    }
    if (!(actor_flags & 0x400)) {
        goto mode_410_without_400;
    }

    found = func_800A02AC(arg3, U8_AT(arg2, 0x24), U8_AT(arg2, 0x25));
    if (found != 0) {
        goto found_actor;
    }
    {
        register s32 field_value ASM_REG("$2") = S32_AT(arg3, 0x14);

        if (field_value < 0) {
            goto zero_counter;
        }
        S32_AT(arg3, 0x14) = field_value | 0x80000000;
    }
    call_result = func_800A6D30();
    U16_AT(arg3, 0x2A) += (call_result & 7) << 9;
    goto zero_counter;

mode_410_without_400:
    if (func_800A04F0(arg3, U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
                      S16_AT(arg3, 0x2A)) == 0) {
        goto loop_setup;
    }
    goto clear_path;

check_mode_2000:
    if (!(actor_flags & 0x2000)) {
        goto check_tile_kind;
    }
    if (U16_AT(arg3, 0x46) & 0x8000) {
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
        register u8 *target ASM_REG("$5") = D_80082E80;

        direction = (U8_AT(arg3, 0x45) +
                     ((s32)(U16_AT(D_800814A8, 0x2A) << 16) >> 25)) & 7;
        offset = direction * 2;
        target_x = U8_AT(target, 0x24) + U16_AT(&D_8006CCD8, offset);
        target_y = U8_AT(target, 0x25) + U16_AT(&D_8006CCE8, offset);
        if ((U8_AT(arg2, 0x24) == (u16)target_x) &&
            (U8_AT(arg2, 0x25) == (u16)target_y)) {
            goto clear_path;
        }

        {
            u8 *buffer = arg0 + 0x98;
            s16 next_angle = func_800A0818(
                U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
                (s16)target_x, (s16)target_y, buffer);

            U16_AT(arg3, 0x2A) = next_angle;
            if ((func_8009A66C(next_angle, arg2, arg3, 0x20) << 16) <= 0) {
                u8 *fallback = (u8 *)&D_80082EA4 - 0x24;

                U16_AT(arg3, 0x2A) = func_800A0818(
                    U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
                    U8_AT(fallback, 0x24), U8_AT(fallback, 0x25), buffer);
            }
        }
    }
    {
        u8 *target = (u8 *)&D_80082EA4 - 0x24;

        if ((func_8009FD7C(
                 U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
                 U8_AT(target, 0x24), U8_AT(target, 0x25)) << 16) != 0) {
            special = 1;
        }
    }
    goto loop_setup;

check_tile_kind:
    {
        s32 kind;
        s32 offset;
        u8 *entry;

        kind = S8_AT(arg2, 0x26);
        if (kind >= 0) {
            entry = (u8 *)&D_800E2970;
            offset = kind * 0x14;
            offset += (s32)entry;
            if (U16_AT((u8 *)offset, 0xC) & 2) {
                goto invoke_fallback;
            }
        }
    }
    if (U16_AT(arg3, 0x46) & 0x8000) {
        goto loop_setup;
    }

    found = func_800A02AC(arg3, U8_AT(arg2, 0x24), U8_AT(arg2, 0x25));
    if (!(U16_AT(arg0, 0x98) & 0x8000)) {
        goto zero_counter;
    }
    if (found == 0) {
        goto loop_setup;
    }
    if ((func_8009A540(
             ((S16_AT(arg3, 0x2A) >> 9) & 0xFFFF),
             U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
             (s16)(U16_AT(arg3, 0x88) - 0x20)) << 16) != 0) {
        goto found_actor;
    }
    goto found_retry;

found_actor:
    {
        u8 *other = PTR_AT(found, -0x14);
        register u8 *buffer ASM_REG("$2");
        ASM_KEEP(other);
        buffer = arg0 + 0x98;

        U16_AT(arg3, 0x2A) = func_800A0818(
            U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
            U8_AT(other, 0x24), U8_AT(other, 0x25), buffer);
        U8_AT(arg3, 0x71) &= 0x7F;
        goto done;
    }

found_retry:
    if (func_800A04F0(arg3, U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
                      S16_AT(arg3, 0x2A)) != 0) {
        if ((func_8009A540(
                 ((S16_AT(arg3, 0x2A) >> 9) & 0xFFFF),
                 U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
                 (s16)(U16_AT(arg3, 0x88) - 0x20)) << 16) != 0) {
            goto clear_path;
        }
    }
    if (!(S32_AT(arg3, 0x1C) & 0x20000)) {
        goto invoke_fallback;
    }
    {
        u8 *goal = (u8 *)&D_80082EA4 - 0x24;
        u8 *buffer = arg0 + 0x98;

        U16_AT(arg3, 0x2A) = func_800A0818(
            U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
            U8_AT(goal, 0x24), U8_AT(goal, 0x25), buffer);
        if ((func_8009FD7C(
                 U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
                 U8_AT(goal, 0x24), U8_AT(goal, 0x25)) << 16) == 0) {
            goto loop_setup;
        }
        if ((func_8009A540(
                 ((S16_AT(arg3, 0x2A) >> 9) & 0xFFFF),
                 U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
                 (s16)(U16_AT(arg3, 0x88) - 0x20)) << 16) == 0) {
            goto loop_setup;
        }
    }
    goto clear_path;

invoke_fallback:
    func_800A0E6C(arg2, S8_AT(arg0, 0x9C), arg3, arg0 + 0x98);

zero_counter:

loop_setup:
    counter = 0;
    ASM_USE(counter);
    angle_steps = D_8006CD00;

    for (; counter < 8; counter++) {
    current_angle = S16_AT(arg3, 0x2A);
    if (U16_AT(arg0, 0x98) & 2) {
        trial = current_angle - angle_steps[counter];
    } else {
        trial = current_angle + angle_steps[counter];
    }
    if ((func_8009A66C((s16)trial, arg2, arg3, 0x20) << 16) > 0) {
        if (counter >= 3) {
            special_test = special;
            ASM_KEEP(special_test);
            if (special_test != 0) {
                goto clear_path;
            }
        }
        U16_AT(arg3, 0x2A) = trial;
        {
            u8 *slot;

            slot = arg3;
            slot += U8_AT(arg3, 0x71) & 0x7F;
            U8_AT(slot, 0x74) = U8_AT(arg2, 0x24);
            slot = arg3;
            slot += U8_AT(arg3, 0x71) & 0x7F;
            U8_AT(slot, 0x7C) = U8_AT(arg2, 0x25);
        }
        U8_AT(arg3, 0x71)++;

        func_8009A3D0(
            U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
            (S32_AT(arg3, 0x1C) & 0x2000) ? 0x300 : 0x3000);

        {
            s32 move_offset = (U16_AT(arg3, 0x2A) >> 8) & 0xE;
            register u8 *x_steps ASM_REG("$3") = (u8 *)&D_8006CCD8;

            U8_AT(arg2, 0x24) += U8_AT(x_steps, move_offset);
            U8_AT(arg2, 0x25) += U8_AT(&D_8006CCE8, move_offset);
        }
        func_8009A21C(
            U8_AT(arg2, 0x24), U8_AT(arg2, 0x25),
            (S32_AT(arg3, 0x1C) & 0x2000) ? 0x300 : 0x3000);
        break;
    }

    if ((counter == 0) &&
        (U16_AT(&D_80082EA4, 0) != U16_AT(arg2, 0x24)) &&
        ((func_8009A180(
              arg3, S32_AT(D_800814A8, 0x58) + 0x20) << 16) != 0)) {
        goto done;
    }
    }

post_loop_test:
    if (counter >= 8) {
        U8_AT(arg3, 0x71) &= 0x7F;
        U16_AT(arg3, 0x46) &= 0x7FFF;
        func_800A9A0C(arg3);
        goto done;
    }

    U16_AT(arg3, 0x46) &= 0x7FFF;
    U8_AT(arg0, 0x9C) = U8_AT(arg2, 0x26);
    U8_AT(arg3, 0x6D)--;
    {
        u8 *global_count = (u8 *)&D_80083460;

        U16_AT(global_count, 8)++;
    }
    if (S8_AT(arg3, 0x6D) != 0) {
        goto actor_survives;
    }

clear_path:
    U8_AT(arg3, 0x71) &= 0x7F;
    goto done;

actor_survives:
    counter = func_800BCB04(
        (U8_AT(arg2, 0x24) << 6) | 0x20,
        (U8_AT(arg2, 0x25) << 6) | 0x20,
        (s16)(U16_AT(arg3, 0x88) - 0x20));
    if (counter < 0x200) {
        U16_AT(arg3, 0x88) = counter;
    }
    goto done;

done:
    return;
}
