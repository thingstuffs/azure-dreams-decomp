#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "records/Rec_func_801736F4_arg0.h"


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, s32);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA79C(void *, s32, void *, void *);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_80173EF4(void *, s32, void *, void *);

extern u8 D_80170E54;
extern u8 D_80174140[];
extern u8 D_80174188[];
extern u8 D_80174190[];

/* Updates actor actions and directional animations through a three-state sequence. */
void func_801736F4(void *controller, s32 actor_index, void *sprite, EntityRec *actor)
{
    DungeonGlobalStatus *dungeon_status;
    s32 actor_flags;
    s32 state;

    state = ((Rec_func_801736F4_arg0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174190;
            func_80047784(
                sprite,
                D_80174190[((gameWork.view.viewAngle
                             + actor->facing + 0x100)
                            >> 9) & 7],
                0);
        }
        {
            DungeonGlobalStatus *dungeon_counters;
            dungeon_counters = &dungeonStatus;
            (*(u16 *)&dungeon_counters->unk_0A)--;
        }
        ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
        return;

    case 1:
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000) {
            void *anim_table;
            anim_table = ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv;
            if (anim_table == D_80174140) {
                ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv = D_80174188;
            } else if (anim_table == D_80174188) {
                ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv = D_80174190;
            }
            func_80047784(
                sprite,
                ((u8 *)((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv)
                    [((gameWork.view.viewAngle
                       + actor->facing + 0x100)
                      >> 9) & 7],
                0);
        }

        if ((func_80042900(actor, 1) << 16) == 0) {
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174188;
            func_80047784(
                sprite,
                D_80174188[((gameWork.view.viewAngle + actor->facing + 0x100)
                            >> 9) & 7],
                0);
            if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0x8000) {
                actor->flags1C &= ~0x200;
                ((Rec_func_801736F4_arg0 *)controller)->unk_8C = &D_80170E54;
                return;
            }
            {
                DungeonGlobalStatus *dungeon_counters = &dungeonStatus;
                (*(u16 *)&dungeon_counters->unk_0A)++;
            }
            ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
            return;
        } else {
            dungeon_status = &dungeonStatus;
            if (!(dungeon_status->flags & 0x1000)
                && ((actor->unk_64 == 0)
                    || (func_800AA6B4(controller, actor_index, sprite, 0) == 0))) {

                if (actor->tileY == 0) {
                    if (dungeon_status->flags & 0x2008) {
                        return;
                    }
                    func_800AA79C(controller, actor_index, sprite, actor);
                    return;
                }

                if ((func_800A2C34(actor) << 16) != 0) {
                    return;
                }
                actor_flags = actor->flags1C;
                if (actor_flags & 0x100) {
                    func_800AA258(controller, actor_index, sprite, actor);
                    return;
                }
                if (actor_flags & 0x80000) {
                    func_800AA888(controller, actor_index, sprite, actor);
                    func_80173EF4(controller, actor_index, sprite, actor);
                    return;
                }
                if (actor->unk_6D == 0) {
                    return;
                }
                if ((func_800A2C34(actor) << 16) != 0) {
                    if ((func_8009A180(
                             actor,
                             ((s32)D_800814A8->unk_58)
                                 + 0x20)
                         << 16)
                        != 0) {
                        return;
                    }
                }

                func_800A9A0C(actor);
                func_800A9A04(actor);
                if ((func_80042900(actor, 1) << 16) != 0) {
                    TileObject *room_base;
                    s32 room_id;
                    room_base = &D_80082E80;
                    room_id = ((Rec_func_800AA258_arg2 *)sprite)->unk_26.as_s8;
                    if (((room_id == room_base->unk_026)
                         && (room_id >= 0))
                        || (func_8009FD40(room_base, sprite) < 2)) {
                        if (!(func_800A6D30() & 7)) {
                            func_80042B68(actor, 1);
                        }
                    }
                }
                if ((func_80042900(actor, 1) << 16) != 0) {
                    return;
                }

                (*(void * *)((u8 *)sprite + 0x2C)) = D_80174188;
                func_80047784(
                    sprite,
                    D_80174188[((gameWork.view.viewAngle + actor->facing + 0x100)
                                >> 9) & 7],
                    0);
                if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0x8000) {
                    actor->flags1C &= ~0x200;
                    ((Rec_func_801736F4_arg0 *)controller)->unk_8C = &D_80170E54;
                    return;
                }
                {
                    DungeonGlobalStatus *dungeon_counters = &dungeonStatus;
                    (*(u16 *)&dungeon_counters->unk_0A)++;
                }
                ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
                return;
            }
        }
        return;

    case 2:
        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *dungeon_counters;
            dungeon_counters = &dungeonStatus;
            (*(u16 *)&dungeon_counters->unk_0A)--;
        }
        actor->flags1C &= ~0x200;
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174188;
        func_80047784(
            sprite,
            D_80174188[((gameWork.view.viewAngle + actor->facing + 0x100)
                        >> 9) & 7],
            0);
        ((Rec_func_801736F4_arg0 *)controller)->unk_8C = &D_80170E54;
        return;

        return;
    }
}
