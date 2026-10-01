#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_8016CC70_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_8016CC70_0;   /* obj in func_8016CC70 */

typedef struct S_8016CC70_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_8016CC70_1;   /* target_arg in func_8016CC70 */

typedef struct S_8016CC70_2 {
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
} S_8016CC70_2;   /* actor_arg in func_8016CC70 */


s32 func_80042900(void *, s32);
void func_80042B68(void *, s32);
void func_80047784(void *, s32, s32);
s32 func_8009A180(void *, void *);
s16 func_8009FD40(void *, void *);
s32 func_800A2C34(void *);
s32 func_800A6D30(void);
void func_800A9A04(void *);
void func_800A9A0C(void *);
void func_800AA258(void *, s32, void *, void *);
s32 func_800AA6B4(void *, s32, void *, s32);
void func_800AA79C(void *, s32, void *, void *);
void func_800AA888(void *, s32, void *, void *);
void func_8016D4B8(void *, s32, void *, void *);
extern M2C_UNK D_8016A36C;
extern u8 D_80173AC8[];
extern u8 D_80173AD0[];

/* Processes object action states, dispatches actor_arg actions, and updates directional tiles. */
void func_8016CC70(void *obj_arg, s32 context_arg, void *target_arg, void *actor_arg) {
    void *target;

    DungeonGlobalStatus *held_base;
    void *callback;
    TileObject *room_base;
    DungeonGlobalStatus *counter_base;
    s32 counter_value;
    s32 action_state;
    s32 obj_kind;
    s32 actor_flags;
    s8 target_room;

    action_state = ((S_8016CC70_0 *)obj_arg)->unk_9B;
    switch (action_state) {
    case 0:
        if (!(((S_8016CC70_1 *)target_arg)->unk_14 & 0xE000)) {
            return;
        }
        obj_kind = ((S_8016CC70_0 *)obj_arg)->unk_AC;
        if (obj_kind == 0xE || (obj_kind < 0xF ? obj_kind == 0xD : obj_kind == 0xF)) {
            (*(u8 **)((u8 *)target_arg + 0x2C)) = D_80173AC8;
            func_80047784(target_arg, D_80173AC8[((gameWork.view.viewAngle + ((S_8016CC70_2 *)actor_arg)->unk_2A + 0x100)
                >> 9) & 7], 0);
        }
        counter_base = &dungeonStatus;
        counter_value = *(u16 *)&counter_base->unk_0A;
        counter_value--;
        *(u16 *)&counter_base->unk_0A = counter_value;
        ((S_8016CC70_0 *)obj_arg)->unk_9B++;
        return;

    case 1:
        obj_kind = ((S_8016CC70_0 *)obj_arg)->unk_AC;
        if (obj_kind == 0xE || (obj_kind < 0xF ? obj_kind == 0xD : obj_kind == 0xF)) {
            if (((S_8016CC70_1 *)target_arg)->unk_2C != D_80173AC8) {
                (*(u8 **)((u8 *)target_arg + 0x2C)) = D_80173AC8;
                func_80047784(target_arg, D_80173AC8[((gameWork.view.viewAngle + ((S_8016CC70_2 *)actor_arg)->unk_2A + 0x100)
                    >> 9) & 7], 0);
            }
        }
        target = target_arg;
        if ((func_80042900(actor_arg, 1) << 0x10) == 0) {
            obj_kind = ((S_8016CC70_0 *)obj_arg)->unk_AC;
            if (obj_kind == 0xE || (obj_kind < 0xF ? obj_kind == 0xD : obj_kind == 0xF)) {
                (*(u8 **)((u8 *)target + 0x2C)) = D_80173AD0;
                func_80047784(target, D_80173AD0[((gameWork.view.viewAngle + ((S_8016CC70_2 *)actor_arg)->unk_2A + 0x100)
                    >> 9) & 7], 0);
            }
        } else {
            held_base = &dungeonStatus;
            if (held_base->flags & 0x1000) {
                return;
            }
            if (((S_8016CC70_2 *)actor_arg)->unk_64 != 0) {
                if (func_800AA6B4(obj_arg, context_arg, target, 0) != 0) {
                    return;
                }
            }
            if (((S_8016CC70_2 *)actor_arg)->unk_25 == 0) {
                if (held_base->flags & 0x2008) {
                    return;
                }
                func_800AA79C(obj_arg, context_arg, target, actor_arg);
                return;
            }
            if ((func_800A2C34(actor_arg) << 0x10) != 0) {
                return;
            }
            actor_flags = ((S_8016CC70_2 *)actor_arg)->unk_1C;
            if (actor_flags & 0x100) {
                func_800AA258(obj_arg, context_arg, target, actor_arg);
                return;
            }
            if (actor_flags & 0x80000) {
                func_800AA888(obj_arg, context_arg, target, actor_arg);
                func_8016D4B8(obj_arg, context_arg, target, actor_arg);
                return;
            }
            if (((S_8016CC70_2 *)actor_arg)->unk_6D == 0) {
                return;
            }
            if ((func_800A2C34(actor_arg) << 0x10) != 0) {
                if ((func_8009A180(actor_arg, (u8 *)D_800814A8->unk_58 + 0x20) << 0x10) != 0) {
                    return;
                }
            }
            func_800A9A0C(actor_arg);
            func_800A9A04(actor_arg);
            if ((func_80042900(actor_arg, 1) << 0x10) != 0) {
                room_base = &D_80082E80;
                target_room = ((S_8016CC70_1 *)target)->unk_26;
                if (!(((target_room != room_base->unk_026) || (target_room < 0))
                      && func_8009FD40(room_base, target) >= 2)) {
                    if ((func_800A6D30() & 7) == 0) {
                        func_80042B68(actor_arg, 1);
                    }
                }
            }
            if ((func_80042900(actor_arg, 1) << 0x10) != 0) {
                return;
            }
            obj_kind = ((S_8016CC70_0 *)obj_arg)->unk_AC;
            if (obj_kind == 0xE || (obj_kind < 0xF ? obj_kind == 0xD : obj_kind == 0xF)) {
                (*(u8 **)((u8 *)target + 0x2C)) = D_80173AD0;
                func_80047784(target, D_80173AD0[((gameWork.view.viewAngle + ((S_8016CC70_2 *)actor_arg)->unk_2A + 0x100)
                    >> 9) & 7], 0);
            }
        }
        if (((S_8016CC70_1 *)target)->unk_14 & 0x8000) {
            break;
        }
        counter_base = &dungeonStatus;
        counter_value = *(u16 *)&counter_base->unk_0A;
        counter_value++;
        *(u16 *)&counter_base->unk_0A = counter_value;
        ((S_8016CC70_0 *)obj_arg)->unk_9B++;
        return;

    case 2:
        target = target_arg;
        if (!(((S_8016CC70_1 *)target)->unk_14 & 0xE000)) {
            return;
        }
        counter_base = &dungeonStatus;
        counter_value = *(u16 *)&counter_base->unk_0A;
        counter_value--;
        *(u16 *)&counter_base->unk_0A = counter_value;
        break;

    default:
        return;
    }
    callback = &D_8016A36C;
    ((S_8016CC70_0 *)obj_arg)->unk_8C = callback;
}
