#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"


extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_801724B0(void *, s32, void *, void *);
extern void func_801726EC(void *, void *, void *, void *);
extern s32 func_80172E80(void *, void *, void *, void *);
extern void func_801730A4(void *, void *, void *, void *);
extern s32 func_801731DC(void *, void *, void *, s32);
extern void func_8017531C(void *, void *, void *, void *);
extern void func_801754F0(void *, void *, void *, void *);
extern void func_80175BE0(void *, void *, void *, void *);

extern u8 D_800DCF5B;
extern u8 D_800E2348[];
extern u8 D_800E2358[];
extern u8 D_800E2378;
extern u8 D_800E23A0[];
extern u8 D_800E23A8[];
extern s32 D_80171F1C;


typedef struct S_80171F1C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
} S_80171F1C_0;   /* arg0 in func_80171F1C */


typedef struct S_80171F1C_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171F1C_2;   /* arg2 in func_80171F1C */


/* Update actor movement, animation, and action handling for the dungeon turn. */
void func_80171F1C(void *motion_arg, void *actor_index_arg, void *actor_arg, void *move_data_arg)
{
    EntityRec *move_data;
    s32 direction_flags;
    s8 room_id;
    u16 action_state;
    u32 initial_flags = dungeonStatus.flags;

    move_data = move_data_arg;

    if (initial_flags & 0x1000) {
        ((S_80171F1C_0 *)motion_arg)->unk_9A = 0xE;
        func_801724B0(motion_arg, (s32)actor_index_arg, actor_arg, move_data);
        return;
    }


    if (move_data->tileY == 0) {
        void *anim_table;

        func_800AA79C(motion_arg, actor_index_arg, actor_arg, move_data);
        if (((S_80171F1C_2 *)actor_arg)->unk_2C == D_800E23A8) {
            return;
        }
        anim_table = D_800E23A0;
        (*(void * *)((u8 *)actor_arg + (0x2C))) = anim_table;
        func_80047784(actor_arg,
            ((u8 *)anim_table)[((gameWork.view.viewAngle + move_data->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)move_data->flags1C) & 0x200) {
        if (((S_80171F1C_2 *)actor_arg)->unk_2C == D_800E23A8) {
            ((S_80171F1C_0 *)motion_arg)->unk_9A = 0xD;
            ((S_80171F1C_0 *)motion_arg)->unk_9B = 1;
            ((S_80171F1C_0 *)motion_arg)->unk_8C = 0;
            move_data->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(motion_arg, actor_index_arg, actor_arg, D_800E23A0) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)move_data->flags1C) & 0x100) {
            func_800AA258(motion_arg, actor_index_arg, actor_arg, move_data);
            return;
        }

        {
            u8 current_state = ((S_80171F1C_0 *)motion_arg)->unk_9A;
            u32 idle_state = 0xE;
            void *current_anim;
            void *anim_table;

            if (current_state != idle_state) {
                ((S_80171F1C_0 *)motion_arg)->unk_9A = idle_state;
            }
            current_anim = ((S_80171F1C_2 *)actor_arg)->unk_2C;
            anim_table = D_800E2348;
            if (current_anim != anim_table) {
                (*(void * *)((u8 *)actor_arg + (0x2C))) = anim_table;
                func_80047784(actor_arg,
                    ((u8 *)anim_table)[((gameWork.view.viewAngle + move_data->facing + 0x100) >> 9) & 7],
                    0);
                ((S_80171F1C_2 *)actor_arg)->unk_05 = 1;
                ((S_80171F1C_0 *)motion_arg)->unk_A2.s = 0;
                ((S_80171F1C_0 *)motion_arg)->unk_9E = 0;
            }
        }

        move_data->flags1C |= 0x40000;
        ((S_80171F1C_0 *)motion_arg)->unk_98 &= 0xFFF7;

        if (move_data->unk_64 != 0) {
            if (func_800AA6B4(motion_arg, actor_index_arg, actor_arg, D_800E2358) != 0) {
                return;
            }
        }

        if (((u32)move_data->flags1C) & 0x80000) {
            s16 base_height;

            func_800AA888(motion_arg, actor_index_arg, actor_arg, move_data);
            base_height = ((S_80171F1C_0 *)motion_arg)->unk_92.u - ((S_80171F1C_0 *)motion_arg)->unk_A2.u;
            ((S_80171F1C_0 *)motion_arg)->unk_A2.s = 0;
            ((S_80171F1C_0 *)motion_arg)->unk_9E = 0;
            ((S_80171F1C_0 *)motion_arg)->unk_92.s = base_height;
            func_8017531C(motion_arg, actor_index_arg, actor_arg, move_data);
            return;
        }

        if ((func_800A1C58(move_data) << 16) != 0) {
            func_800AAB10(motion_arg, actor_index_arg, actor_arg, move_data);
        }
    }

    room_id = func_8009FB34(((S_80171F1C_2 *)actor_arg)->unk_24.at00.v, ((S_80171F1C_2 *)actor_arg)->unk_24.at01.v);
    ((S_80171F1C_2 *)actor_arg)->unk_26 = room_id;

    if (move_data->unk_6D > 0) {
        if (((u32)move_data->flags1C) & 0x20) {
            func_800A9A0C(move_data);
            return;
        }
        if (((S_80171F1C_2 *)actor_arg)->unk_24.at00u.v != *(u16 *)(&D_80082E80.tileX)) {
            if (!(move_data->unk_46 & 0x8000)) {
                if (dungeonStatus.flags & 0x2000) {
                    if ((func_8009A180(move_data,
                            (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_801731DC(motion_arg, actor_index_arg, actor_arg, 0) << 16) == 0) {
                    return;
                }
                action_state = move_data->unk_46 | 0x4000;
                move_data->unk_46 = action_state;
                if (!(action_state & 0x8000)) {
                    func_801726EC(motion_arg, actor_index_arg, actor_arg, move_data);
                    return;
                }
            }

            action_state = move_data->unk_46 & 0x3FFF;
            switch (action_state) {
            case 8:
                if ((func_80172E80(motion_arg, actor_index_arg, actor_arg, move_data) << 16) != 0) {
                    return;
                }
                func_801730A4(motion_arg, actor_index_arg, actor_arg, move_data);
                return;

            case 10:
                if (D_800DCF5B != 0) {
                    func_800A9A0C(move_data);
                    return;
                }
                func_801754F0(motion_arg, actor_index_arg, actor_arg, move_data);
                return;

            case 9:
                if (!(((u32)move_data->flags1C) & 0x20000)) {
                    func_800A9A0C(move_data);
                    return;
                }
                func_80175BE0(motion_arg, actor_index_arg, actor_arg, move_data);
                return;

            case 5:
            case 6:
            case 7:
            {
                EntityRec *player;
                s16 heading;

                heading = func_800A0818(
                    ((S_80171F1C_2 *)actor_arg)->unk_24.at00.v, ((S_80171F1C_2 *)actor_arg)->unk_24.at01.v,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &direction_flags);
                player = D_800814A8;
                move_data->facing = heading;
                if (player->unk_9A == 0x11) {
                    func_800AAF00(motion_arg, actor_index_arg, actor_arg, &D_800E2378, &D_80171F1C);
                    return;
                }
            }
                                        /* fallthrough */
            case 12:
                func_800A9A0C(move_data);
                return;

            case 1:
            case 2:
            case 3:
                func_800AAF00(motion_arg, actor_index_arg, actor_arg, &D_800E2378, &D_80171F1C);
                return;

            case 4:
            case 11:
            default:
                break;
            }
        }
        func_801726EC(motion_arg, actor_index_arg, actor_arg, move_data);
        return;
    }

    if (!(((u32)move_data->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) || !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)move_data->flags1C) & 0x430)) {

                if ((func_8009FD7C(
                        ((S_80171F1C_2 *)actor_arg)->unk_24.at00.v, ((S_80171F1C_2 *)actor_arg)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    move_data->facing = func_800A0818(
                        ((S_80171F1C_2 *)actor_arg)->unk_24.at00.v, ((S_80171F1C_2 *)actor_arg)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_flags);
                }
            }
        }
    }
}
