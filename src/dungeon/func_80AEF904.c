#include "modules/dungeon_resource10_slot0.h"

void update_actor_callbacks_animation_and_ground(u8 *actor, u8 *motion, u8 *object)
{
    u8 *actor_copy;
    R10_80171104_ActorCallback callback;
    s16 old_direction;
    s16 timer;
    u16 flags;
    s16 height_delta;
    s16 floor_height;
    s16 actor_height;
    s16 view_index_copy;
    u8 *animation;
    s32 shifted_direction;

    actor_copy = actor;

    if (g_dungeon_status.flags & 0x2000) {
        R10_80171104_ActorCallback early_callback;
        void *early_actor;

        early_callback = (*(R10_80171104_ActorCallback *)((u8 *)actor + 0x8C));
        if (early_callback == (R10_80171104_ActorCallback)((void *)func_801717F4)) {
            early_actor = actor;
            early_callback(early_actor, motion, object, early_actor);
            return;
        }
        (*(u8 *)((u8 *)actor + 0x71)) &= 0x7F;
        return;
    }


    old_direction = (*(s8 *)((u8 *)actor + 0x6D));
    if (refresh_actor_facing_and_lifecycle(actor, motion, object, actor) != 0) {
        return;
    }

    callback = (*(R10_80171104_ActorCallback *)((u8 *)actor + 0x8C));
    if (callback != 0) {
        callback(actor, motion, object, actor);
    }
    ((R10_80171104_ActorCallback *)D_80175A1C)[(*(u8 *)((u8 *)actor + 0x9A))](actor, motion, object, actor);

    if ((*(u8 *)((u8 *)actor + 0x9A)) != 0xE ||
        (((SpriteAnimationTableView *)object)->unk_14 & 0x40) ||
        ((*(u32 *)((u8 *)actor + 0x1C)) & 0x20)) {
        shifted_direction = (s32)old_direction << 16;
    } else {
        if (((SpriteAnimationTableView *)object)->unk_2C != ((u8 *)D_80175988) &&
            ((SpriteAnimationTableView *)object)->unk_2C != ((u8 *)D_801759A0) &&
            ((SpriteAnimationTableView *)object)->unk_2C != ((u8 *)D_801759B0) &&
            ((SpriteAnimationTableView *)object)->unk_2C != ((u8 *)D_801759B8)) {
            (*(u8 * *)((u8 *)object + 0x2C)) = ((u8 *)D_80175988);
            func_80047784(object,
                ((u8 *)D_80175988)[((g_game_work.view.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7], 0);
            (*(u16 *)((u8 *)actor + 0x9E)) = 0;
            (*(s16 *)((u8 *)actor + 0xA0)) = 10;
        }

        if (((SpriteAnimationTableView *)object)->unk_2C == ((u8 *)D_80175988)) {
            timer = (*(u16 *)((u8 *)actor + 0x9E));
            (*(u16 *)((u8 *)actor + 0x9E)) = timer + 1;
            if (timer >= (*(s16 *)((u8 *)actor + 0xA0))) {
                (*(u8 * *)((u8 *)object + 0x2C)) = ((u8 *)D_801759A0);
                func_80047784(object,
                    ((u8 *)D_801759A0)[((g_game_work.view.viewAngle + ((R10_80171104_S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7], 0);
                func_800478B8(object);
                (*(s16 *)((u8 *)actor + 0xA0)) = 3;
            }
        }

        if (((SpriteAnimationTableView *)object)->unk_2C == ((u8 *)D_801759A0)) {
            timer = (*(u16 *)((u8 *)actor + 0xA0)) - 1;
            (*(s16 *)((u8 *)actor + 0xA0)) = timer;
            if ((timer << 16) <= 0 &&
                (((SpriteAnimationTableView *)object)->unk_14 & 0xE000)) {
                (*(u8 * *)((u8 *)object + 0x2C)) = ((u8 *)D_801759B0);
                func_80047784(object,
                    ((u8 *)D_801759B0)[((g_game_work.view.viewAngle + ((R10_80171104_S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7], 0);
                func_800478B8(object);
                (*(s16 *)((u8 *)actor + 0xA0)) = 6;
                (*(s32 *)((u8 *)actor + 0x90)) += 0xFFE00000;
                ((R10_80171104_S_80171104_2 *)motion)->unk_14 = 0;
                (*(s8 *)((u8 *)actor + 0x9D)) = 0;
            }
        }

        if (((SpriteAnimationTableView *)object)->unk_2C == ((u8 *)D_801759B0)) {
            timer = (*(u16 *)((u8 *)actor + 0xA0)) - 1;
            (*(s16 *)((u8 *)actor + 0xA0)) = timer;
            if ((timer << 16) <= 0 &&
                (((SpriteAnimationTableView *)object)->unk_14 & 0xE000)) {
                (*(u8 * *)((u8 *)object + 0x2C)) = ((u8 *)D_801759B8);
                func_80047784(object,
                    ((u8 *)D_801759B8)[((g_game_work.view.viewAngle + ((R10_80171104_S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7], 0);
                func_800478B8(object);
                (*(s16 *)((u8 *)actor + 0xA0)) = 3;
            }
        }

        if (((SpriteAnimationTableView *)object)->unk_2C != ((u8 *)D_801759B8)) {
            shifted_direction = (s32)old_direction << 16;
        } else {
            timer = (*(u16 *)((u8 *)actor + 0xA0)) - 1;
            (*(s16 *)((u8 *)actor + 0xA0)) = timer;
            if ((timer << 16) > 0) {
                shifted_direction = (s32)old_direction << 16;
            } else {
                if (((SpriteAnimationTableView *)object)->unk_14 & 0xE000) {
                    (*(u8 * *)((u8 *)object + 0x2C)) = ((u8 *)D_80175988);
                    func_80047784(object,
                        ((u8 *)D_80175988)[((g_game_work.view.viewAngle + ((R10_80171104_S_80171104_1 *)actor_copy)->unk_2A + 0x100)
                            >> 9) & 7], 0);
                    (*(u16 *)((u8 *)actor + 0x9E)) = 0;
                    (*(s16 *)((u8 *)actor + 0xA0)) = 20;
                }
                shifted_direction = (s32)old_direction << 16;
            }
        }
    }

    if ((shifted_direction >> 16) != ((R10_80171104_S_80171104_1 *)actor_copy)->unk_6D) {
        try_move_actor_to_valid_position(actor, motion, object, actor_copy);
    }

    flags = ((SpriteAnimationTableView *)object)->unk_14;
    if (!(flags & 0x8000)) {
        s16 view_index;
        s32 old_direction;

        old_direction = ((g_game_work.view.viewAngle + ((R10_80171104_S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7;
        view_index = old_direction;
        view_index_copy = old_direction;
        if ((*(s16 *)((u8 *)actor + 0x94)) != view_index) {
            animation = ((SpriteAnimationTableView *)object)->unk_2C;
            if (animation != 0) {
                select_indirect_table_entry(object, animation[view_index], ((SpriteAnimationTableView *)object)->unk_04);
            }
            (*(s16 *)((u8 *)actor + 0x94)) = old_direction;
        }

        if (dir_sprite_flag[view_index_copy] != 0) {
            ((SpriteAnimationTableView *)object)->unk_14 |= 1;
        } else {
            ((SpriteAnimationTableView *)object)->unk_14 &= 0xFFFE;
        }
        if (!(((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u & 0x20)) {
            if (!(((SpriteAnimationTableView *)object)->unk_14 & 0x40)) {
                func_800478B8(object);
            }
        } else {
            ((SpriteAnimationTableView *)object)->unk_14 |= 0x7000;
        }
        apply_monster_koyaw_data(((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.s, object + 0xC);
    } else if (flags & 0x800) {
        ((SpriteAnimationTableView *)object)->unk_14 = flags & 0x8FFF;
    } else {
        ((SpriteAnimationTableView *)object)->unk_14 = flags | 0x7000;
    }

    ((R10_80171104_S_80171104_2 *)motion)->unk_00.at00.v += ((R10_80171104_S_80171104_2 *)motion)->unk_0C;
    ((R10_80171104_S_80171104_2 *)motion)->unk_04.at00.v += ((R10_80171104_S_80171104_2 *)motion)->unk_10;

    if ((*(u16 *)((u8 *)actor + 0x98)) & 8) {
        (*(s8 *)((u8 *)actor + 0x9D)) = 0;
    } else {
        ((R10_80171104_S_80171104_2 *)motion)->unk_14 += (*(s8 *)((u8 *)actor + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)actor + 0x9D))++;
    }
    (*(s32 *)((u8 *)actor + 0x90)) += ((R10_80171104_S_80171104_2 *)motion)->unk_14;

    if (!((*(u16 *)((u8 *)actor + 0x98)) & 4)) {
        floor_height = ((s16)sample_terrain_surface_height(((R10_80171104_S_80171104_2 *)motion)->unk_00.at02.v, ((R10_80171104_S_80171104_2 *)motion)->unk_04.at02.v,(s16)((s16)(((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.u - 0x20))));
        if (floor_height < 0x200) {
            actor_height = ((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.s;
            if ((*(s16 *)((u8 *)actor + 0x92)) + actor_height < floor_height) {
                ((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    (*(s32 *)((u8 *)actor + 0x90)) = 0;
                } else {
                    height_delta = floor_height - ((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.u;
                    (*(s16 *)((u8 *)actor + 0x92)) = height_delta;
                }
                ((R10_80171104_S_80171104_2 *)motion)->unk_14 = 0;
                ((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u |= 0x08000000;
                (*(s8 *)((u8 *)actor + 0x9D)) = 0;
            }

            if (((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u & 0x40000000) {
                ((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u &= 0xBFFFFFFF;
                floor_height = ((s16)sample_terrain_surface_height((((SpriteAnimationTableView *)object)->unk_24 << 6) | 0x20,
                                       (((SpriteAnimationTableView *)object)->unk_25 << 6) | 0x20,(s16)((s16)(((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.u - 0x20))));
                (*(s16 *)((u8 *)actor + 0x92)) += ((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.u - floor_height;
                ((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.s = floor_height;
            }
        } else {
            ((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u &= 0xF7FFFFFF;
        }
    } else {
        ((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u &= 0xF7FFFFFF;
    }

    ((R10_80171104_S_80171104_2 *)motion)->unk_0A = ((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.u + (*(s16 *)((u8 *)actor + 0x92));
    ((SpriteAnimationTableView *)object)->unk_14 |= 0x40;

    return;
}
