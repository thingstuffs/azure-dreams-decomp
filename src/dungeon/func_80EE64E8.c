#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80171E20_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80171E20_0;   /* arg0 in func_8016BCE8 */

typedef struct S_80171E20_1 {
    u8 pad_00[0x1C];
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
} S_80171E20_1;   /* arg3 in func_8016BCE8 */

typedef struct S_80171E20_2 {
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
} S_80171E20_2;   /* arg2 in func_8016BCE8 */


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
extern s32 func_800AA924(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);

extern void func_8016C24C(void *, void *, void *, void *);
extern void func_8016C490(void *, void *, void *, void *);
extern s32 func_8016CC44(void *, void *, void *, void *);
extern void func_8016CE08(void *, void *, void *, void *);
extern s32 func_8016CF20(void *, void *, void *, s32);
extern void func_8016E650(void *, void *, void *, void *);
extern void func_8016E824(void *, void *, void *, void *);

extern u8 D_8016EEB8[];
extern u8 D_8016EEC0[];
extern u8 D_8016EEF0[];
extern u8 D_8016EEF8[];
extern u8 D_8016EF00[];

/* Updates an actor's dungeon behavior, facing, and animation. */
void func_8016BCE8(void *actor_in, void *actor_data_in, void *sprite_in, void *status_in)
{
    u32 initial_flags = dungeonStatus.flags;
    s16 distance;
    s32 status_flags;
    s8 tile_id;
    s16 facing;
    u16 action_flags;
    u8 *anim_table;
    EntityRec *player;

    if (initial_flags & 0x1000) {
        ((S_80171E20_0 *)actor_in)->unk_9A = 14;
        func_8016C24C(actor_in, actor_data_in, sprite_in, status_in);
        return;
    }


    if (((S_80171E20_1 *)status_in)->unk_25 == 0) {
        func_800AA79C(actor_in, actor_data_in, sprite_in, status_in);
        if (((S_80171E20_2 *)sprite_in)->unk_2C == D_8016EF00) {
            return;
        }
        {
            u8 *early_anim_table = D_8016EEF8;
            (*(u8 * *)((u8 *)sprite_in + 0x2C)) = early_anim_table;
            func_80047784(
                sprite_in,
                early_anim_table[((gameWork.view.viewAngle + ((S_80171E20_1 *)status_in)->unk_2A + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (((S_80171E20_1 *)status_in)->unk_1C & 0x200) {
        if (((S_80171E20_2 *)sprite_in)->unk_2C == D_8016EF00) {
            ((S_80171E20_0 *)actor_in)->unk_9A = 13;
            ((S_80171E20_0 *)actor_in)->unk_9B = 1;
            ((S_80171E20_0 *)actor_in)->unk_8C = 0;
            ((S_80171E20_1 *)status_in)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor_in, actor_data_in, sprite_in, D_8016EEF8) != 0) {
            return;
        }
    }

    if ((dungeonStatus.flags & 0x2000) == 0) {
        if (((S_80171E20_1 *)status_in)->unk_1C & 0x100) {
            func_800AA258(actor_in, actor_data_in, sprite_in, status_in);
            return;
        }

        {
            u8 current_state = ((S_80171E20_0 *)actor_in)->unk_9A;
            u32 next_state = 14;

            if (current_state != next_state) {
                anim_table = D_8016EEB8;
                if (((S_80171E20_2 *)sprite_in)->unk_2C != anim_table) {
                    (*(u8 * *)((u8 *)sprite_in + 0x2C)) = anim_table;
                    func_80047784(
                        sprite_in,
                        anim_table[((gameWork.view.viewAngle + ((S_80171E20_1 *)status_in)->unk_2A + 0x100) >> 9) & 7],
                        0);
                }
                ((S_80171E20_0 *)actor_in)->unk_9A = next_state;
            }
        }

        ((S_80171E20_0 *)actor_in)->unk_98 &= 0xFFF3;

        if (((S_80171E20_1 *)status_in)->unk_64 != 0) {
            if (func_800AA6B4(actor_in, actor_data_in, sprite_in, D_8016EEC0) != 0) {
                return;
            }
        }

        if (((S_80171E20_1 *)status_in)->unk_1C & 0x80000) {
            func_800AA888(actor_in, actor_data_in, sprite_in, status_in);
            func_8016E650(actor_in, actor_data_in, sprite_in, status_in);
            return;
        }

        if ((s16)func_800A1C58(status_in) != 0) {
            func_800AAB10(actor_in, actor_data_in, sprite_in, status_in);
        }
    }

    tile_id = func_8009FB34(((S_80171E20_2 *)sprite_in)->unk_24.at00.v, ((S_80171E20_2 *)sprite_in)->unk_24.at01.v);
    ((S_80171E20_2 *)sprite_in)->unk_26 = tile_id;

    if (((S_80171E20_1 *)status_in)->unk_6D > 0) {
        if (((S_80171E20_1 *)status_in)->unk_1C & 0x20) {
            func_800A9A0C(status_in);
            return;
        }
        if (((S_80171E20_2 *)sprite_in)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_8016C490(actor_in, actor_data_in, sprite_in, status_in);
            return;
        }
        action_flags = ((S_80171E20_1 *)status_in)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(
                        status_in, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8016CF20(actor_in, actor_data_in, sprite_in, 0) == 0) {
                return;
            }
            action_flags = ((S_80171E20_1 *)status_in)->unk_46 | 0x4000;
            ((S_80171E20_1 *)status_in)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_8016C490(actor_in, actor_data_in, sprite_in, status_in);
            return;
            }
        }

        switch (((S_80171E20_1 *)status_in)->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)func_8016CC44(actor_in, actor_data_in, sprite_in, status_in) != 0) {
                return;
            }
            func_8016CE08(actor_in, actor_data_in, sprite_in, status_in);
            return;
        case 9:
            func_8016E824(actor_in, actor_data_in, sprite_in, status_in);
            return;
        case 5:
        case 6:
        case 7:
            facing = func_800A0818(
                ((S_80171E20_2 *)sprite_in)->unk_24.at00.v, ((S_80171E20_2 *)sprite_in)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY, &distance);
            player = D_800814A8;
            ((S_80171E20_1 *)status_in)->unk_2A = facing;
            if (player->unk_9A == 0x11) {
                func_800AAF00(actor_in, actor_data_in, sprite_in, D_8016EEF0, func_8016BCE8);
                return;
            }
            /* fallthrough */
        case 12:
            func_800A9A0C(status_in);
            return;
        case 1:
        case 2:
        case 3:
            func_800AAF00(actor_in, actor_data_in, sprite_in, D_8016EEF0, func_8016BCE8);
            return;
        default:
            func_8016C490(actor_in, actor_data_in, sprite_in, status_in);
            return;
        }
    }

    status_flags = ((S_80171E20_1 *)status_in)->unk_1C;
    if (!(status_flags & 0x2000)) {
        if ((tile_id < 0) ||
            !(D_800E2970[tile_id].flags & 2)) {
            if (!(status_flags & 0x430)) {
                if ((s16)func_8009FD7C(
                        ((S_80171E20_2 *)sprite_in)->unk_24.at00.v, ((S_80171E20_2 *)sprite_in)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) != 0) {
                    ((S_80171E20_1 *)status_in)->unk_2A = func_800A0818(
                        ((S_80171E20_2 *)sprite_in)->unk_24.at00.v, ((S_80171E20_2 *)sprite_in)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY, &distance);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_80171E20_2 *)sprite_in)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_8016EEB8;
    if (((S_80171E20_2 *)sprite_in)->unk_2C == anim_table) {
        return;
    }

    (*(u8 * *)((u8 *)sprite_in + 0x2C)) = anim_table;
    func_80047784(
        sprite_in,
        anim_table[((gameWork.view.viewAngle + ((S_80171E20_1 *)status_in)->unk_2A + 0x100) >> 9) & 7],
        0);
}
