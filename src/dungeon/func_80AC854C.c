#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80173D4C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173D4C_0;   /* arg0 in func_80173D4C */

typedef struct S_80173D4C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_80173D4C_1;   /* arg2 in func_80173D4C */

typedef struct S_80173D4C_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80173D4C_2;   /* arg3 in func_80173D4C */




extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801743E8(void *, void *, void *, void *);

extern s32 D_80171728;
extern u8 D_80174E4C[];
extern u8 D_80174E54[];

/* Advances the actor action state and updates its directional animation. */
void func_80173D4C(void *action_in, void *context_in, void *sprite_in, void *actor_in)
{
    void *action;
    register void *context ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *sprite;
    void *actor;
    s32 state;
    void *actor_to_check;
    DungeonGlobalStatus *status;
    s32 actor_flags;
    register DungeonGlobalStatus *counter_base_m ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    action = action_in;
    context = context_in;
    sprite = sprite_in;
    state = ((S_80173D4C_0 *)action)->unk_9B;
    actor = actor_in;
    switch (state) {
    case 0:
        if (!(((S_80173D4C_1 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174E4C;
        func_80047784(sprite,
            D_80174E4C[((gameWork.view.viewAngle + ((S_80173D4C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        {
            DungeonGlobalStatus *counter_base;

            counter_base = &dungeonStatus;
            counter_base->unk_0A =
                ((u16)counter_base->unk_0A) - 1;
        }
        ((S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 1:
        if ((func_80042900(actor, 1) << 16) != 0) {
            status = &dungeonStatus;
            if (status->flags & 0x1000) {
                return;
            }
            if (((S_80173D4C_2 *)actor)->unk_64 != 0) {
                if (func_800AA6B4(action, context, sprite, 0) != 0) {
                    return;
                }
            }
            if (((S_80173D4C_2 *)actor)->unk_25 == 0) {
                if (status->flags & 0x2008) {
                    return;
                }
                func_800AA79C(action, context, sprite, actor);
                return;
            }
            if ((func_800A2C34(actor) << 16) != 0) {
                return;
            }
            actor_flags = ((S_80173D4C_2 *)actor)->unk_1C;
            if (actor_flags & 0x100) {
                func_800AA258(action, context, sprite, actor);
                return;
            }
            if (actor_flags & 0x80000) {
                func_800AA888(action, context, sprite, actor);
                func_801743E8(action, context, sprite, actor);
                return;
            }
            if (((S_80173D4C_2 *)actor)->unk_6D == 0) {
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
                s8 coordinate = ((S_80173D4C_1 *)sprite)->unk_26;
                TileObject *origin = &D_80082E80;
                s32 probe_result;

                if ((coordinate != origin->unk_026) || (coordinate < 0)) {
                    probe_result = func_8009FD40(origin, sprite);
                    actor_to_check = actor;
                    if (probe_result >= 2) {
                        goto final_check_call;
                    }
                    if (!(func_800A6D30(actor) & 7)) {
                        func_80042B68(actor, 1);
                    }
                } else {
                    if (!(func_800A6D30(origin) & 7)) {
                        func_80042B68(actor, 1);
                    }
                }
            }

            actor_to_check = actor;
final_check_call:
            if ((func_80042900(actor_to_check, 1) << 16) != 0) {
                return;
            }

        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174E54;
        func_80047784(sprite,
            D_80174E54[((gameWork.view.viewAngle + ((S_80173D4C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (((S_80173D4C_1 *)sprite)->unk_14 & 0x8000) {
            ((S_80173D4C_0 *)action)->unk_8C = &D_80171728;
            return;
        }
        {

            counter_base_m = &dungeonStatus;
            (*(u16 *)&counter_base_m->unk_0A)++;
        }

        ((S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 2:
        if (!(((S_80173D4C_1 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {

            counter_base_m = &dungeonStatus;
            (*(u16 *)&counter_base_m->unk_0A)--;
        }

        ((S_80173D4C_0 *)action)->unk_8C = &D_80171728;

        return;
    }
}

/* MECHANISM: Removing value-rewriting arg/table keeps recovered the 40-byte frame,
   retail save order, and v0-destination symbolic indexing. Nonvolatile counter RMW
   lets sh fill the jump delay; duplicated A6D30 paths merge with predecessor-held a0.
   A pinned $a0 final-check local exposes the call-only label needed by word 160. */