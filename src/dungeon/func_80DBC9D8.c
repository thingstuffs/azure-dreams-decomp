#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801741D8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801741D8_0;   /* arg0 in func_801741D8 */

typedef struct S_801741D8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} S_801741D8_1;   /* arg2 in func_801741D8 */

typedef struct S_801741D8_2 {
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
} S_801741D8_2;   /* arg3 in func_801741D8 */


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
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174890(void *, void *, void *, void *);

extern u8 D_80171E20[];
extern u8 D_80175404[];
extern u8 D_8017540C[];

/* Advance the actor action state and update its directional animation. */
void func_801741D8(void *controller, void *context, void *sprite, void *actor_in)
{
    void *actor;
    u8 state;
    DungeonGlobalStatus *global_state;
    void *check_target;
    void *active_actor;
    s8 tile;

    state = ((S_801741D8_0 *)controller)->unk_9B;
    actor = actor_in;
    switch (state) {
    case 0:
        if (((S_801741D8_1 *)sprite)->unk_14 & 0xE000) {
            DungeonGlobalStatus *counter;

            (*(void * *)((u8 *)sprite + 0x2C)) = D_80175404;
            func_80047784(sprite,
                D_80175404[((gameWork.view.viewAngle + ((S_801741D8_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            counter = &dungeonStatus;
            (*(u16 *)&counter->unk_0A)--;
            ((S_801741D8_0 *)controller)->unk_9B++;
            break;
        }
        break;

    case 1:
        if ((s16)func_80042900(actor, 1) == 0) {
            goto set_effect;
        }

        global_state = &dungeonStatus;
        if (global_state->flags & 0x1000) {
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_64 != 0) {
            if (func_800AA6B4(controller, context, sprite, 0) != 0) {
                break;
            }
        }

        if (((S_801741D8_2 *)actor)->unk_25 == 0) {
            if (global_state->flags & 0x2008) {
                break;
            }
            func_800AA79C(controller, context, sprite, actor);
            break;
        }

        if ((s16)func_800A2C34(actor) != 0) {
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_1C & 0x100) {
            func_800AA258(controller, context, sprite, actor);
            break;
        }

        if ((s16)func_800A2C34(actor) != 0) {
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_1C & 0x80000) {
            func_800AA888(controller, context, sprite, actor);
            func_80174890(controller, context, sprite, actor);
            break;
        }

        if (((S_801741D8_2 *)actor)->unk_6D == 0) {
            break;
        }

        if ((s16)func_800A2C34(actor) != 0) {
            if ((s16)func_8009A180(
                    actor, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                break;
            }
        }

        func_800A9A0C(actor);
        func_800A9A04(actor);
        if ((s16)func_80042900(actor, 1) != 0) {
            check_target = ((u8 *)(&D_80082E80));
            tile = ((S_801741D8_1 *)sprite)->unk_26;
            if (tile != ((Rec_D_80082E80 *)((u8 *)(&D_80082E80)))->unk_26.as_s8 || tile < 0) {
                s16 distance;

                distance = func_8009FD40(((u8 *)(&D_80082E80)), sprite);
                active_actor = actor;
                if (distance >= 2) {
                    goto final_call;
                }
                check_target = active_actor;
            }
            if ((func_800A6D30(check_target) & 7) == 0) {
                func_80042B68(actor, 1);
            }
        }

        active_actor = actor;
final_call:
        if ((s16)func_80042900(active_actor, 1) != 0) {
            break;
        }

set_effect:
        (*(void * *)((u8 *)sprite + 0x2C)) = D_8017540C;
        func_80047784(sprite,
            D_8017540C[((gameWork.view.viewAngle + ((S_801741D8_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (((S_801741D8_1 *)sprite)->unk_14 & 0x8000) {
            ((S_801741D8_0 *)controller)->unk_8C = D_80171E20;
            break;
        } else {
            DungeonGlobalStatus *counter_m = &dungeonStatus;
            counter_m->unk_0A++;
        }

increment_state:
        ((S_801741D8_0 *)controller)->unk_9B++;
        break;

    case 2:
        if (((S_801741D8_1 *)sprite)->unk_14 & 0xE000) {
            DungeonGlobalStatus *counter_m = &dungeonStatus;
            counter_m->unk_0A--;
set_owner:
            ((S_801741D8_0 *)controller)->unk_8C = D_80171E20;
        }
        break;

    default:
        break;
    }
    return;
}
