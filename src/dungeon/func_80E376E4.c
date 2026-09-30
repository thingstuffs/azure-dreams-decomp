#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818(u8, u8, u8, u8, s16 *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_80171460(void *, void *, void *, void *);
extern void func_801716A4(void *, void *, void *, void *);
extern s32 func_80171E38(void *, void *, void *, void *);
extern void func_80171FFC(void *, void *, void *, void *);
extern s32 func_80172114(void *, void *, void *, s32);
extern void func_801737B8(void *, void *, void *, void *);
extern void func_80173C40(void *, void *, void *, void *);

extern u8 D_80170EE4[];
extern u8 D_801765D8[];
extern u8 D_801765E0[];
extern u8 D_80176650[];
extern u8 D_80176660[];
extern u8 D_80176678[];


typedef struct S_80170EE4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80170EE4_0;   /* arg0 in func_80170EE4 */

typedef struct S_80170EE4_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80170EE4_1;   /* arg3 in func_80170EE4 */

typedef struct S_80170EE4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_80170EE4_2;   /* arg2 in func_80170EE4 */


/* Update dungeon actor behavior, facing, and directional animation. */
void func_80170EE4(void *actor_state_in, void *update_context_in, void *map_object, void *actor_data)
{
    u32 dungeon_flags = dungeonStatus.flags;
    s16 distance;
    s32 status_flags;
    s8 tile_index;
    s16 facing_angle;
    u16 action_flags;
    u8 *animation_table;
    EntityRec *target_actor;

    if (dungeon_flags & 0x1000) {
        ((S_80170EE4_0 *)actor_state_in)->unk_9A = 14;
        func_80171460(actor_state_in, update_context_in, map_object, actor_data);
        return;
    }


    if (((S_80170EE4_1 *)actor_data)->unk_25 == 0) {
        func_800AA79C(actor_state_in, update_context_in, map_object, actor_data);
        if (((S_80170EE4_2 *)map_object)->unk_2C == D_80176650) {
            return;
        }
        (*(u8 * *)((u8 *)map_object + (0x2C))) = D_80176678;
        func_80047784(
            map_object,
            D_80176678[((gameWork.view.viewAngle + ((S_80170EE4_1 *)actor_data)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80170EE4_1 *)actor_data)->unk_1C & 0x200) {
        if (((S_80170EE4_2 *)map_object)->unk_2C == D_80176650) {
            ((S_80170EE4_0 *)actor_state_in)->unk_9A = 13;
            ((S_80170EE4_0 *)actor_state_in)->unk_9B = 1;
            ((S_80170EE4_0 *)actor_state_in)->unk_8C = 0;
            ((S_80170EE4_1 *)actor_data)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor_state_in, update_context_in, map_object, D_80176678) != 0) {
            return;
        }
    }

    if ((dungeonStatus.flags & 0x2000) == 0) {
        if (((S_80170EE4_1 *)actor_data)->unk_1C & 0x100) {
            func_800AA258(actor_state_in, update_context_in, map_object, actor_data);
            return;
        }

        {
            u8 default_state = 14;
            if (((S_80170EE4_0 *)actor_state_in)->unk_9A != default_state) {
                if (((S_80170EE4_2 *)map_object)->unk_2C != D_801765D8) {
                    (*(u8 * *)((u8 *)map_object + (0x2C))) = D_801765D8;
                    func_80047784(
                        map_object,
                        D_801765D8[((gameWork.view.viewAngle + ((S_80170EE4_1 *)actor_data)->unk_2A + 0x100) >> 9) & 7],
                        0);
                }
                ((S_80170EE4_0 *)actor_state_in)->unk_9A = default_state;
            }
        }

        ((S_80170EE4_0 *)actor_state_in)->unk_98 &= 0xFFF3;

        if (((S_80170EE4_1 *)actor_data)->unk_64 != 0) {
            if (func_800AA6B4(actor_state_in, update_context_in, map_object, D_801765E0) != 0) {
                return;
            }
        }

        if (((S_80170EE4_1 *)actor_data)->unk_1C & 0x80000) {
            func_800AA888(actor_state_in, update_context_in, map_object, actor_data);
            func_801737B8(actor_state_in, update_context_in, map_object, actor_data);
            return;
        }

        if ((s16)func_800A1C58(actor_data) != 0) {
            func_800AAB10(actor_state_in, update_context_in, map_object, actor_data);
        }
    }

    tile_index = func_8009FB34(((S_80170EE4_2 *)map_object)->unk_24.at00.v,
        ((S_80170EE4_2 *)map_object)->unk_24.at01.v);
    ((S_80170EE4_2 *)map_object)->unk_26 = tile_index;

    if (((S_80170EE4_1 *)actor_data)->unk_6D > 0) {
        if (((S_80170EE4_1 *)actor_data)->unk_1C & 0x20) {
            func_800A9A0C(actor_data);
            return;
        }
        if (((S_80170EE4_2 *)map_object)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_801716A4(actor_state_in, update_context_in, map_object, actor_data);
            return;
        }
        action_flags = ((S_80170EE4_1 *)actor_data)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(
                        actor_data, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172114(actor_state_in, update_context_in, map_object, 0) == 0) {
                return;
            }
            action_flags = ((S_80170EE4_1 *)actor_data)->unk_46 | 0x4000;
            ((S_80170EE4_1 *)actor_data)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_801716A4(actor_state_in, update_context_in, map_object, actor_data);
                return;
            }
        }

        switch (((S_80170EE4_1 *)actor_data)->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)func_80171E38(actor_state_in, update_context_in, map_object, actor_data) != 0) {
                return;
            }
            func_80171FFC(actor_state_in, update_context_in, map_object, actor_data);
            return;

        case 9:
            if (!(((S_80170EE4_1 *)actor_data)->unk_14 & 0x20000000)) {
                func_80173C40(actor_state_in, update_context_in, map_object, actor_data);
                return;
            }
            func_80171FFC(actor_state_in, update_context_in, map_object, actor_data);
            return;

        case 5:
        case 6:
        case 7:
            facing_angle = func_800A0818(
                ((S_80170EE4_2 *)map_object)->unk_24.at00.v, ((S_80170EE4_2 *)map_object)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY, &distance);
            target_actor = D_800814A8;
            ((S_80170EE4_1 *)actor_data)->unk_2A = facing_angle;
            if (target_actor->unk_9A == 0x11) {
                func_800AAF00(actor_state_in, update_context_in, map_object, D_80176660, D_80170EE4);
                return;
            }

        case 12:
            func_800A9A0C(actor_data);
            return;

        case 1:
        case 2:
        case 3:
            func_800AAF00(actor_state_in, update_context_in, map_object, D_80176660, D_80170EE4);
            return;

        case 11:
        default:
            func_801716A4(actor_state_in, update_context_in, map_object, actor_data);
            return;
        }
    }

    status_flags = ((S_80170EE4_1 *)actor_data)->unk_1C;
    if (!(status_flags & 0x2000)) {
        if ((tile_index < 0) ||
            !(D_800E2970[tile_index].flags & 2)) {
            if (!(status_flags & 0x430)) {
                if ((s16)func_8009FD7C(
                        ((S_80170EE4_2 *)map_object)->unk_24.at00.v, ((S_80170EE4_2 *)map_object)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) != 0) {
                    ((S_80170EE4_1 *)actor_data)->unk_2A = func_800A0818(
                        ((S_80170EE4_2 *)map_object)->unk_24.at00.v, ((S_80170EE4_2 *)map_object)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY, &distance);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_80170EE4_2 *)map_object)->unk_14 & 0x40) {
        return;
    }
    animation_table = D_801765D8;
    if (((S_80170EE4_2 *)map_object)->unk_2C == animation_table) {
        return;
    }
    (*(u8 * *)((u8 *)map_object + (0x2C))) = animation_table;
    func_80047784(
        map_object,
        *(u8 *)((((gameWork.view.viewAngle + ((S_80170EE4_1 *)actor_data)->unk_2A + 0x100) >> 9) & 7)
                + (u32)animation_table),
        0);
}
