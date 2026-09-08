#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80174F24_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_80174F24_0;   /* arg0 in func_80174F24 */

typedef struct S_80174F24_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80174F24_1;   /* arg2 in func_80174F24 */


typedef struct S_80174F24_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174F24_3;   /* arg1 in func_80174F24 */



extern void func_80047784(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_80173B98;
extern u8 D_80176338[];
extern u8 D_80176340[];

/* Updates the actor's movement animation and finishes the timed action. */
void func_80174F24(void *action, void *motion_arg, void *unit_arg, void *actor)
{
    register void *motion ASM_REG("$18") = motion_arg;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *unit ASM_REG("$19") = unit_arg;   /* MATCH pin: load-bearing for the whole function shape */
    s32 direction_aux;
    u8 move_state;

    move_state = ((S_80174F24_0 *)action)->unk_9B;
    switch (move_state) {
    case 0:
        if (((S_80174F24_1 *)unit)->unk_14 & 0x6000) {
            u8 *direction_table = D_80176338;

            (*(u8 * *)((u8 *)unit + 0x2C)) = direction_table;
            func_80047784(unit,
                direction_table[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((S_80174F24_0 *)action)->unk_98 |= 8;
            ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 &= ~0x08000000;
            ((S_80174F24_0 *)action)->unk_9E.s = 5;
            ((S_80174F24_0 *)action)->unk_A0 = 0;
            ((S_80174F24_0 *)action)->unk_9B++;
        } else {
            goto check_timeout;
        }
        /* fall through */

    case 1:
        {
            s16 move_ticks;
            s32 target_delta;
            s32 axis_pos;
            s32 x_velocity;

            ((S_80174F24_0 *)action)->unk_90 -= ((S_80174F24_0 *)action)->unk_A0;
            move_ticks = ((S_80174F24_0 *)action)->unk_9E.s;
            if (move_ticks != 0) {
                target_delta = ((S_80174F24_1 *)unit)->unk_24 << 6;
                axis_pos = ((S_80174F24_3 *)motion)->unk_02 - 0x20;
                target_delta -= axis_pos;
                x_velocity = (target_delta << 16) / move_ticks;

                axis_pos = ((S_80174F24_3 *)motion)->unk_06;
                ((S_80174F24_3 *)motion)->unk_0C = x_velocity;
                axis_pos -= 0x20;
                target_delta = ((S_80174F24_1 *)unit)->unk_25 << 6;
                target_delta -= axis_pos;
                ((S_80174F24_3 *)motion)->unk_10 =
                    (target_delta << 16) / ((S_80174F24_0 *)action)->unk_9E.s;

                ((S_80174F24_0 *)action)->unk_A0 =
                    (-func_800644B8(((S_80174F24_0 *)action)->unk_9E.s * 409)) << 9;
            }

            ((S_80174F24_0 *)action)->unk_90 += ((S_80174F24_0 *)action)->unk_A0;
            move_ticks = ((S_80174F24_0 *)action)->unk_9E.u - 1;
            ((S_80174F24_0 *)action)->unk_9E.s = move_ticks;
            if (move_ticks >= 0) {
                goto check_landing;
            }
            ((S_80174F24_0 *)action)->unk_90 = 0;
            ((S_80174F24_0 *)action)->unk_98 &= 0xFFF7;
            ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 |= 0x08000000;
            ((S_80174F24_0 *)action)->unk_9B++;
        }
        /* fall through */

    case 2:
check_landing:
        if (((Rec_D_800E3D7C *)actor)->unk_1C.as_u32 & 0x08000000) {
            u8 *direction_table;

            ((S_80174F24_0 *)action)->unk_98 &= 0xFFF7;
            ((S_80174F24_3 *)motion)->unk_14 = 0;
            ((S_80174F24_3 *)motion)->unk_10 = 0;
            ((S_80174F24_3 *)motion)->unk_0C = 0;
            func_800A2B04(motion,
                ((S_80174F24_1 *)unit)->unk_24, ((S_80174F24_1 *)unit)->unk_25);
            direction_table = D_80176340;
            (*(u8 * *)((u8 *)unit + 0x2C)) = direction_table;
            func_80047784(unit,
                direction_table[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((S_80174F24_0 *)action)->unk_9B++;
        }
        break;

    default:
        break;
    }

check_timeout:
    {
        s16 action_ticks;
        s16 *global_counts;
        u32 actor_flags;

        action_ticks = ((S_80174F24_0 *)action)->unk_96.s - 1;
        ((S_80174F24_0 *)action)->unk_96.u = action_ticks;
        if (action_ticks > 0) {
            return;
        }

        ((S_80174F24_3 *)motion)->unk_14 = 0;
        ((S_80174F24_3 *)motion)->unk_10 = 0;
        ((S_80174F24_3 *)motion)->unk_0C = 0;
        func_800A2B04(motion,
            ((S_80174F24_1 *)unit)->unk_24, ((S_80174F24_1 *)unit)->unk_25);
        func_800AD594(actor, 4);
        func_800A4ACC(actor);

        global_counts = (s16 *)&D_80083460;
        if (global_counts[4] != 0) {
            global_counts[4]--;
        }

        actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_u32;
        if (actor_flags & 0x2000) {
            if (((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000) {
                ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
            }
            goto update_actor;
        }
        if (actor_flags & 0x410) {
            goto update_actor;
        }
        if (actor_flags & 0x20000) {
            ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = func_800A0818(
                ((S_80174F24_1 *)unit)->unk_24, ((S_80174F24_1 *)unit)->unk_25,
                D_80082E80[0x24], D_80082E80[0x25], &direction_aux);
        }

update_actor:
        if ((func_800AD9B4(unit, actor) << 16) > 0) {
            ((S_80174F24_0 *)action)->unk_8C = &D_80173B98;
            func_800A9A04(actor);
        }
        ASM_KEEP(motion);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_KEEP(unit);   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
}
