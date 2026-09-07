#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef s32 M2C_UNK;

typedef struct S_80172998_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    s16 unk_A4;
} S_80172998_0;   /* arg0 in func_80172998 */


typedef struct S_80172998_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172998_2;   /* arg2 in func_80172998 */



extern s32 func_800644B8(s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s32 D_80083460;
extern M2C_UNK D_80170E94;

/* Animate movement to the target tile and finalize the actor when the timer expires. */
void func_80172998(S_80172998_0 *motion, Rec_D_800E3D7C *position, S_80172998_2 *target, Rec_D_800E3D7C *actor)
{
    s32 tile_query_out;
    s32 motion_phase;
    u32 actor_flags;

    motion_phase = motion->unk_9B;
    switch (motion_phase) {
    case 0:
        motion->unk_98 |= 8;
        actor->unk_1C.u &= 0xF7FFFFFF;
        motion->unk_A4 = 7;
        motion->unk_A0 = 0;
        motion->unk_9B++;

    case 1:
        motion->unk_90 -= motion->unk_A0;
        if (motion->unk_A4 != 0) {
            {
                s32 target_x = target->unk_24 << 6;
                s32 current_x = position->unk_00.at02.v - 32;

                position->unk_0C.n =
                    ((target_x - current_x) << 16) / motion->unk_A4;
            }
            {
                s32 target_y = target->unk_25 << 6;
                s32 current_y = position->unk_04.at02.v - 32;

                position->unk_10.at00.v =
                    ((target_y - current_y) << 16) / motion->unk_A4;
            }
            motion->unk_A0 =
                (-func_800644B8(motion->unk_A4 * 292)) << 9;
        }

        motion->unk_90 += motion->unk_A0;
        actor->unk_1C.u &= 0xF7FFFFFF;
        motion->unk_A4--;
        if (motion->unk_A4 >= 0) {
            goto phase_two;
        }

        motion->unk_90 = 0;
        motion->unk_98 &= 0xFFF7;
        actor->unk_1C.u |= 0x08000000;
        motion->unk_9B++;

    case 2:
phase_two:
        if (actor->unk_1C.u & 0x08000000) {
            motion->unk_98 &= 0xFFF7;
            position->unk_14.s32 = 0;
            position->unk_10.at00.v = 0;
            position->unk_0C.n = 0;
            func_800A2B04(position, target->unk_24, target->unk_25);
            motion->unk_9B++;
        }

    default:
        break;
    }

    motion->unk_96--;
    if (motion->unk_96 > 0) {
        return;
    }

    position->unk_14.s32 = 0;
    position->unk_10.at00.v = 0;
    position->unk_0C.n = 0;
    func_800A2B04(position, target->unk_24, target->unk_25);
    func_800AD594(actor, 5);
    func_800A4ACC(actor);

    {
        s16 *global_counters = (s16 *)&D_80083460;

        if (global_counters[4] != 0) {
            ((u16 *)global_counters)[4]--;
        }
    }

    actor_flags = actor->unk_1C.u;
    if (actor_flags & 0x2000) {
        if (actor->unk_44.at02.v & 0x8000) {
            actor->unk_44.at02.v &= 0x7FFF;
        }
    } else {
        if (actor_flags & 0x410) {
            goto actor_check;
        }
        if (!(actor_flags & 0x20000)) {
            goto actor_check;
        }
        actor->unk_2A.s = func_800A0818(
            target->unk_24, target->unk_25,
            D_80082E80[0x24], D_80082E80[0x25], &tile_query_out);
    }

actor_check:
    if ((func_800AD9B4(target, actor) << 16) > 0) {
        motion->unk_8C = &D_80170E94;
        func_800A9A04(actor);
    }
}
