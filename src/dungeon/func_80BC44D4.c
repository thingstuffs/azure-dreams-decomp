#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80173CD4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { u32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_A4;   /* overlapping accesses */
    u32 unk_A8;
    u32 unk_AC;
    u32 unk_B0;
    u8 pad_B4[0x4];
    u16 unk_B8;
} S_80173CD4_0;   /* arg0 in func_80173CD4 */

typedef struct S_80173CD4_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_80173CD4_1;   /* arg2 in func_80173CD4 */

typedef struct S_80173CD4_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80173CD4_2;   /* arg3 in func_80173CD4 */

typedef struct S_80173CD4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80173CD4_4;   /* global in func_80173CD4 */


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801743F0(void *, void *, void *, void *);

extern s32 D_801719DC;
extern u8 D_80174684[];
extern u8 D_8017468C[];

/* Advance the actor action state, handle status flags, and update directional animation. */
void func_80173CD4(void *action_in, void *context_in, void *sprite_in, void *actor_in)
{
    s32 state;
    void *action = action_in;
    register void *context ASM_REG("$19") = context_in;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *sprite = sprite_in;
    void *actor;
    u8 *world_state;
    u16 counter_value;

    state = ((S_80173CD4_0 *)action)->unk_9B;
    actor = actor_in;
    switch (state) {
    case 0:
    {
        DungeonGlobalStatus *world_counters;
        u8 *direction_anims;
        if (!(((S_80173CD4_1 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        direction_anims = D_80174684;
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
        func_80047784(sprite,
            direction_anims[((gameWork.view.viewAngle + ((S_80173CD4_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        world_counters = &dungeonStatus;
        (*(u16 *)&world_counters->unk_0A)--;
    }
        ((S_80173CD4_0 *)action)->unk_9B++;
        return;
    case 1:
    {
        u32 world_page;
        u32 actor_flags;

        if ((func_80042900(actor, 1) << 16) != 0) {
            world_page = 0x80080000;
            world_state = (u8 *)((u32)&dungeonStatus.unk_00);
            if (((S_80173CD4_4 *)world_state)->unk_02 & 0x1000) {
                return;
            }

            if (((S_80173CD4_2 *)actor)->unk_64 != 0) {
                if (func_800AA6B4(action, context, sprite, 0) != 0) {
                    return;
                }
            }

            if (((S_80173CD4_2 *)actor)->unk_25 == 0) {
                if (((S_80173CD4_4 *)world_state)->unk_02 & 0x2008) {
                    return;
                }
                func_800AA79C(action, context, sprite, actor);
                return;
            }

            if ((func_800A2C34(actor) << 16) != 0) {
                return;
            }

            actor_flags = ((S_80173CD4_2 *)actor)->unk_1C;
            if (actor_flags & 0x100) {
                func_800AA258(action, context, sprite, actor);
                return;
            }

            if (actor_flags & 0x80000) {
                u16 current_amount;
                u16 pending_amount;
                u32 packed_adjustment;

                func_800AA888(action, context, sprite, actor);
                current_amount = ((S_80173CD4_0 *)action)->unk_92;
                pending_amount = ((S_80173CD4_0 *)action)->unk_A4.at02.v;
                packed_adjustment = ((S_80173CD4_0 *)action)->unk_A4.at00.v;
                ((S_80173CD4_0 *)action)->unk_A4.at02.v = 0;
                ((S_80173CD4_0 *)action)->unk_B8 = 0;
                ((S_80173CD4_0 *)action)->unk_AC = 0;
                ((S_80173CD4_0 *)action)->unk_B0 = 0;
                ((S_80173CD4_0 *)action)->unk_92 = current_amount - pending_amount;
                ((S_80173CD4_0 *)action)->unk_A8 = packed_adjustment;
                func_801743F0(action, context, sprite, actor);
                return;
            }

            if (((S_80173CD4_2 *)actor)->unk_6D == 0) {
                return;
            }
            if ((func_800A2C34(actor) << 16) != 0) {
                if ((func_8009A180(actor,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }

            func_800A9A0C(actor);
            func_800A9A04(actor);
            if ((func_80042900(actor, 1) << 16) != 0) {
                TileObject *reference_pos;
                s8 room_id;

                reference_pos = &D_80082E80;
                room_id = ((S_80173CD4_1 *)sprite)->unk_26;
                if ((((room_id == reference_pos->unk_026) &&
                      (room_id >= 0)) ||
                     (func_8009FD40(reference_pos, sprite) < 2)) &&
                    !(func_800A6D30() & 7)) {
                    func_80042B68(actor, 1);
                }
            }

            if ((func_80042900(actor, 1) << 16) != 0) {
                return;
            }
        }
    }
        {
            u8 *direction_anims;

            direction_anims = D_8017468C;
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
            func_80047784(sprite,
                direction_anims[((gameWork.view.viewAngle + ((S_80173CD4_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_80173CD4_2 *)actor)->unk_1C |= 0x40000;
            if (((S_80173CD4_1 *)sprite)->unk_14 & 0x8000) {
                ((S_80173CD4_0 *)action)->unk_8C = &D_801719DC;
                return;
            }

            {
                counter_value = (u16)dungeonStatus.unk_0A;
                counter_value++;
                dungeonStatus.unk_0A = counter_value;
            }
        }
        ((S_80173CD4_0 *)action)->unk_9B++;
        return;
    case 2:
        if (((S_80173CD4_1 *)sprite)->unk_14 & 0xE000) {
            counter_value = (u16)dungeonStatus.unk_0A;
            counter_value--;
            dungeonStatus.unk_0A = counter_value;
        } else {
            return;
        }
        ((S_80173CD4_0 *)action)->unk_8C = &D_801719DC;
        return;
    }
}

