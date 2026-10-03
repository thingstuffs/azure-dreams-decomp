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

/* Advances the actor_in action state and updates its directional animation. */
void func_80173D4C(void *action, void *context, void *sprite_in, void *actor_in)
{
    s32 state;
    void *actor_to_check;
    DungeonGlobalStatus *status;
    s32 actor_flags;

    state = ((S_80173D4C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80174E4C;
        func_80047784(sprite_in,
            D_80174E4C[((gameWork.view.viewAngle + ((S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
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
        if ((func_80042900(actor_in, 1) << 16) != 0) {
            status = &dungeonStatus;
            if (status->flags & 0x1000) {
                return;
            }
            if (((S_80173D4C_2 *)actor_in)->unk_64 != 0) {
                if (func_800AA6B4(action, context, sprite_in, 0) != 0) {
                    return;
                }
            }
            if (((S_80173D4C_2 *)actor_in)->unk_25 == 0) {
                if (status->flags & 0x2008) {
                    return;
                }
                func_800AA79C(action, context, sprite_in, actor_in);
                return;
            }
            if ((func_800A2C34(actor_in) << 16) != 0) {
                return;
            }
            actor_flags = ((S_80173D4C_2 *)actor_in)->unk_1C;
            if (actor_flags & 0x100) {
                func_800AA258(action, context, sprite_in, actor_in);
                return;
            }
            if (actor_flags & 0x80000) {
                func_800AA888(action, context, sprite_in, actor_in);
                func_801743E8(action, context, sprite_in, actor_in);
                return;
            }
            if (((S_80173D4C_2 *)actor_in)->unk_6D == 0) {
                return;
            }
            if ((func_800A2C34(actor_in) << 16) != 0) {
                if ((func_8009A180(actor_in,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            func_800A9A0C(actor_in);
            func_800A9A04(actor_in);
            if ((func_80042900(actor_in, 1) << 16) != 0) {
                s8 coordinate = ((S_80173D4C_1 *)sprite_in)->unk_26;
                TileObject *origin = &D_80082E80;
                s32 probe_result;

                if ((coordinate != origin->unk_026) || (coordinate < 0)) {
                    probe_result = func_8009FD40(origin, sprite_in);
                    actor_to_check = actor_in;
                    if (probe_result >= 2) {
                        goto final_check_call;
                    }
                    if (!(func_800A6D30(actor_in) & 7)) {
                        func_80042B68(actor_in, 1);
                    }
                } else {
                    if (!(func_800A6D30(origin) & 7)) {
                        func_80042B68(actor_in, 1);
                    }
                }
            }

            actor_to_check = actor_in;
final_check_call:
            if ((func_80042900(actor_to_check, 1) << 16) != 0) {
                return;
            }

            (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80174E54;
            func_80047784(sprite_in,
                D_80174E54[((gameWork.view.viewAngle + ((S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
                0);
            if (((S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
                ((S_80173D4C_0 *)action)->unk_8C = &D_80171728;
                return;
            }
            dungeonStatus.unk_0A++;

            ((S_80173D4C_0 *)action)->unk_9B++;
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80174E54;
        func_80047784(sprite_in,
            D_80174E54[((gameWork.view.viewAngle + ((S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (((S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
            ((S_80173D4C_0 *)action)->unk_8C = &D_80171728;
            return;
        }
        dungeonStatus.unk_0A++;

        ((S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 2:
        if (!(((S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        dungeonStatus.unk_0A--;

        ((S_80173D4C_0 *)action)->unk_8C = &D_80171728;

        return;
    }
}
