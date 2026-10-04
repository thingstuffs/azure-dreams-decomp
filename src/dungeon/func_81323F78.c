#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

typedef struct S_8016B778_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    union { u8 * p; void * p2; } unk_2C;   /* accessed as both */
} S_8016B778_2;   /* arg2 in func_8016B778 */

typedef struct S_8016B778_3 {
    u8 pad_00[0x58];
    s32 unk_58;
} S_8016B778_3;   /* *D_800814A8 in func_8016B778 */

typedef struct S_8016B778_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_8016B778_4;   /* global_814A8 in func_8016B778 */

typedef struct S_8016B778_5 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_8016B778_5;   /* entry in func_8016B778 */

extern u8 D_801746A4[];
extern u8 D_80174684[];
extern u8 D_801746C4[];
extern u8 D_8017467C[];
extern u8 D_8016B778[];
s8 func_8009FB34();
s32 func_8009FD7C();
s32 func_800A1C58();
void func_800A9A0C();
extern void func_800AA258(void *, void *, void *, void *);
s32 func_800AA6B4();
void func_800AA888();
s32 func_800AA924();
M2C_UNK func_800AAF00();
void func_8016BD14();
void func_8016BF74();
s32 func_8016C720();
void func_8016C8AC();
s32 func_8016C98C();
M2C_UNK func_8016DAA4();
s32 func_8016EF10();
extern M2C_UNK D_8017469C;
extern M2C_UNK D_801746BC;

/* Update the actor's dungeon action, animation, and facing direction. */
void func_8016B778(Rec_func_800A9E70_arg0 *actor, s32 context, S_8016B778_2 *map_actor, EntityRec *entity) {
    u16 target_distance;
    s32 entity_flags;
    s32 state_flags;
    s32 override_flag;
    s16 target_angle;
    s32 action_id;
    s8 tile_index;
    u16 action_flags;
    u8 *action_data;
    register void *current_anim;
    u8 *idle_anim;
    void *action_actor;
    s32 flag_mask_hi;
    u8 *tile_table;
    u8 *tile_entry;
    u8 *active_actor;
    if (dungeonStatus.flags & 0x1000) {
        actor->unk_9A.as_u8 = 0xEU;
        func_8016BD14(actor, context, map_actor, entity);
        return;
    }
    if (entity->flags1C & 0x200) {
        if (map_actor->unk_2C.p == D_801746A4) {
            flag_mask_hi = (s32)0xFFFB0000;
            actor->unk_9A.as_u8 = 0xDU;
            actor->unk_9B.as_s8 = 1;
            actor->unk_8C = 0;
            entity->flags1C &= flag_mask_hi | 0xFFFF;
            return;
        }
        if (func_800AA924(actor, context, map_actor, &D_8017469C) != 0) {
            return;
        }
    }
    if (!(dungeonStatus.flags & 0x2000)) {
        state_flags = entity->flags1C;
        override_flag = state_flags & 0x100;
        action_actor = actor;
        if (override_flag) {
            func_800AA258(action_actor, context, map_actor, entity);
            return;
        }
        if (actor->unk_9A.as_u8 != 0xE) {
            if (actor->unk_B3 == 0) {
                current_anim = map_actor->unk_2C.p2;
                idle_anim = (u8 *)&D_8017467C;
            } else {
                current_anim = map_actor->unk_2C.p2;
                idle_anim = D_80174684;
            }
            if (current_anim != idle_anim) {
                map_actor->unk_2C.p = idle_anim;
                action_data = (u8 *)(((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7);
                action_data += (u32)idle_anim;
                func_80047784(map_actor, *action_data, 0);
            }
            actor->unk_9A.as_u8 = 0xEU;
        }
        actor->unk_98 = (u16) (actor->unk_98 & 0xFFF3);
        if (actor->unk_B4 == 0) {
            if (!((u16)*((s16 *)&D_80013714) & 8)) {
                if (entity->unk_64 != 0) {
                    if (func_800AA6B4(actor, context, map_actor, D_801746C4) != 0) {
                        return;
                    }
                }
            } else {
                if (entity->unk_64 != 0) {
                    if (((s32)dungeonStatus.unk_10) == ((u8 *)entity - 0x20)) {
                        *(s32 *)&dungeonStatus.unk_10 &= 0x7FFFFFFF;
                    }
                }
            }
        } else {
            if (entity->unk_64 != 0) {
                if (((s32)dungeonStatus.unk_10) == ((u8 *)entity - 0x20)) {
                    *(s32 *)&dungeonStatus.unk_10 &= 0x7FFFFFFF;
                }
            }
        }
        if (entity->flags1C & 0x80000) {
            func_800AA888(actor, context, map_actor, entity);
            func_8016DAA4(actor, context, map_actor, entity);
            map_actor->unk_2C.p = D_8017467C;
            func_80047784(map_actor, D_8017467C[((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7], 0);
            actor->unk_90.at00_s32.v = 0;
            return;
        }
        if ((func_800A1C58(entity) << 0x10) != 0) {
            entity->unk_18 = 0;
            dungeonStatus.unk_0C = 0;
        }
    }
    tile_index = func_8009FB34(map_actor->unk_24.at00.v, map_actor->unk_24.at01.v);
    map_actor->unk_26 = tile_index;
    if (entity->unk_6D > 0) {
        if (entity->flags1C & 0x20) {
            func_800A9A0C(entity);
            return;
        }
        if (map_actor->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_8016BF74(actor, context, map_actor, entity);
            return;
        }
        if (!(entity->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((func_8009A180(entity, ((S_8016B778_3 *)(((int)D_800814A8)))->unk_58 + 0x20) << 0x10) != 0) {
                    return;
                }
            }
            if ((u16) *((s16 *)&D_80013714) & 8) {
                func_8016EF10(actor, context, map_actor);
                entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
                func_800A9A0C(entity);
                entity->unk_46 &= 0x7FFF;
                return;
            }
            if ((func_8016C98C(actor, context, map_actor, 0) << 0x10) == 0) {
                return;
            }
            action_flags = entity->unk_46 | 0x4000;
            entity->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                func_8016BF74(actor, context, map_actor, entity);
                return;
            }
        }
        action_id = entity->unk_46 & 0x3FFF;
        switch (action_id) {
        case 8:
        case 9:
            if ((func_8016C720(actor, context, map_actor, entity) << 0x10) != 0) {
                return;
            }
            func_8016C8AC(actor, context, map_actor, entity);
            return;
        case 12:
            func_800A9A0C(entity);
            return;
        case 5:
        case 6:
        case 7:
            target_angle = func_800A0818(map_actor->unk_24.at00.v, map_actor->unk_24.at01.v, D_80082E80.tileX,
                D_80082E80.tileY, &target_distance);
            active_actor = (u8 *)*((int *)(&D_800814A8));
            entity->facing = target_angle;
            if (((S_8016B778_4 *)active_actor)->unk_9A != 0x11) {
                func_800A9A0C(entity);
                return;
            }
            /* Fall through to install the action handler. */
        case 1:
        case 2:
        case 3:
            action_data = D_8016B778;
            func_800AAF00(actor, context, map_actor, &D_801746BC, action_data);
            return;
        case 11:
        default:
            func_8016BF74(actor, context, map_actor, entity);
            return;
        }
    }
    entity_flags = entity->flags1C;
    if (entity_flags & 0x2000) {
        return;
    }
    if (*(u16 *)0x80013714 & 8) {
        return;
    }
    if (tile_index >= 0) {
        tile_table = D_800E2970;
        tile_entry = (tile_index * 0x14) + tile_table;
        if (((S_8016B778_5 *)tile_entry)->unk_0C & 2) {
            return;
        }
    }
    if (entity_flags & 0x430) {
        return;
    }
    if ((func_8009FD7C(map_actor->unk_24.at00.v, map_actor->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY) << 0x10)
        == 0) {
        return;
    }
    entity->facing = func_800A0818(map_actor->unk_24.at00.v, map_actor->unk_24.at01.v, D_80082E80.tileX,
        D_80082E80.tileY, &target_distance);
    return;
}
