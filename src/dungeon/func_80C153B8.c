#include "modules/dungeon_resource17_slot0.h"

void create_anchored_directional_object(void *actor, void *motion, void *object)
{
    u16 initial_flags = g_dungeon_status.flags;
    s32 bob = 0;
    void *actor_state = actor;
    s16 previous_index;
    s16 direction;
    s16 ground;
    s32 ground_offset;
    s32 bob_wave;
    s32 height;
    R17_80170BB8_EntityCallback callback;
    u8 *animation_table;
    u16 status_flags;
    u16 movement_flags;

    if (initial_flags & 0x2000) {
        R17_80170BB8_EntityCallback early_callback = (*(R17_80170BB8_EntityCallback *)((u8 *)actor + (0x8C)));
        if ((void *)early_callback == (void *)((u8 *)update_entity_movement_and_ground_height)) {
            early_callback(actor, motion, object, actor);
            return;
        } else {
            (*(u8 *)((u8 *)actor + (0x71))) &= 0x7F;
            return;
        }
    }


    previous_index = (s8)(*(u8 *)((u8 *)actor + (0x6D)));
    if (refresh_actor_facing_and_lifecycle(actor, motion, object, actor) != 0) {
        return;
    }

    callback = (*(R17_80170BB8_EntityCallback *)((u8 *)actor + (0x8C)));
    if (callback != 0) {
        callback(actor, motion, object, actor);
    }
    ((R17_80170BB8_EntityCallback *)D_80174504)[(*(u8 *)((u8 *)actor + (0x9A)))](actor, motion, object, actor);
    if ((s16)previous_index != (s8)(*(u8 *)((u8 *)actor + (0x6D)))) {
        try_move_actor_to_valid_position(actor, motion, object, actor);
    }

    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at00.v += ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_0C;
    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at00.v += ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_10;

    if (!((*(u32 *)((u8 *)actor + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
        ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_14 += (s8)(*(u8 *)((u8 *)actor + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)actor + (0x9D)))++;
    } else {
        (*(u8 *)((u8 *)actor + (0x9D))) = 0;
    }
    (*(s32 *)((u8 *)actor + (0x90))) += ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_14;
    status_flags = ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14;

    if (!(status_flags & 0x8000)) {
        {
            ground_offset = (g_game_work.view.viewAngle + ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_2A + 0x100) >> 9;
            direction = ground_offset & 7;
        }
        if ((*(s16 *)((u8 *)actor + (0x94))) != direction) {
            select_indirect_table_entry(object, ((R17_80170BB8_S_80170BB8_1 *)object)->unk_2C[direction],
                          ((R17_80170BB8_S_80170BB8_1 *)object)->unk_04);
            (*(s16 *)((u8 *)actor + (0x94))) = direction;
        }
        {
            u32 flip_flags;
            if (dir_sprite_flag[direction] != 0) {
                flip_flags = ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 | 1;
            } else {
                flip_flags = ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 & 0xFFFE;
            }
            ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 = flip_flags;
        }
        if ((*(u8 *)((u8 *)actor + (0x9A))) != 8) {
            apply_monster_koyaw_data(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.s, (u8 *)object + 0xC);
        }

        if (!(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0x20)) {
            if (!(((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 & 0x40)) {
                func_800478B8(object);
            }
        } else {
            ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 |= 0x7000;
            ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u &= 0xFFFBFFFF;
        }

        ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u = ((u32)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0xF7FFFFFF));
        if (((u32)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0xF7FFFFFF)) & 0x40000) {
            if (!(((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 & 0x40)) {
                status_flags = (*(u16 *)((u8 *)actor + (0x98)));
                if (status_flags & 0x8000) {
                    (*(u16 *)((u8 *)actor + (0x98))) = status_flags & 0x7FFF;
                    animation_table = ((R17_80170BB8_S_80170BB8_1 *)object)->unk_2C;
                    if (animation_table == ((u8 *)D_8017449C)) {
                        (*(u8 * *)((u8 *)object + (0x2C))) = ((u8 *)D_80174494);
                        func_80047784(object,
                            ((u8 *)D_80174494)[((g_game_work.view.viewAngle + ((R17_80170BB8_S_if_0 *)actor_state)->unk_2A + 0x100) >> 9) & 7],
                            0);
                    }
                    else if (animation_table == ((u8 *)D_80174494)) {
                        (*(u8 * *)((u8 *)object + (0x2C))) = ((u8 *)D_8017449C);
                        func_80047784(object,
                            ((u8 *)D_8017449C)[((g_game_work.view.viewAngle + ((R17_80170BB8_S_if_0 *)actor_state)->unk_2A + 0x100) >> 9) & 7],
                            0);
                    }
                }
                if (((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 & 0x6000) {
                    (*(u16 *)((u8 *)actor + (0x98))) |= 0x8000;
                    if (((R17_80170BB8_S_80170BB8_1 *)object)->unk_2C == ((u8 *)D_80174494)) {
                        (*(s16 *)((u8 *)actor + (0xA8))) = 0;
                    }
                }
                bob_wave = func_800644B8(((*(s16 *)((u8 *)actor + (0xA8))) << 12) / 21);
                bob = bob_wave >> 8;
                if ((*(u8 *)((u8 *)actor + (0x9A))) == 0x12) {
                    bob = bob_wave >> 10;
                }
                (*(s16 *)((u8 *)actor + (0xA8)))++;
            }

            if (!((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
                ground = (s16)(((s16)sample_terrain_surface_height(((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u - 0x20))) -
                    ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u);
                if ((*(s16 *)((u8 *)actor + (0x92))) > ground - 0x30) {
                    (*(s16 *)((u8 *)actor + (0x92))) = (*(s16 *)((u8 *)actor + (0x92))) - 8;
                } else if (ground - 0x3A > (*(s16 *)((u8 *)actor + (0x92)))) {
                    (*(s16 *)((u8 *)actor + (0x92))) = (*(s16 *)((u8 *)actor + (0x92))) + 8;
                }
            }
        } else {
            movement_flags = (*(u16 *)((u8 *)actor + (0x98)));
            (*(s16 *)((u8 *)actor + (0xA8))) = 0;
            (*(u16 *)((u8 *)actor + (0x98))) = movement_flags & 0x7FFF;
            if (!(movement_flags & 8)) {
                ground_offset = ((s16)sample_terrain_surface_height(((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u - 0x20))) -
                    ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.s;
                if (ground_offset < (*(s16 *)((u8 *)actor + (0x92)))) {
                    (*(s16 *)((u8 *)actor + (0x92))) = ground_offset;
                    (*(u8 *)((u8 *)actor + (0x9D))) = 0;
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_14 = 0;
                    ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u |= 0x08000000;
                }
            }
        }
    } else {
        if (!(status_flags & 0x800)) {
            ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 = status_flags | 0x7000;
        } else {
            ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 = status_flags & 0x8FFF;
        }
        ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u = ((u32)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0xF7FFFFFF));

        if (!(((u32)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0xF7FFFFFF)) & 0x40000)) {
            (*(s16 *)((u8 *)actor + (0xA8))) = 0;
            (*(s16 *)((u8 *)actor + (0x92))) -= bob;
            bob = 0;
            if (!((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
                ground_offset = ((s16)sample_terrain_surface_height(((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u - 0x20))) -
                    ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.s;
                if (ground_offset < (*(s16 *)((u8 *)actor + (0x92)))) {
                    (*(s16 *)((u8 *)actor + (0x92))) = ground_offset;
                    (*(u8 *)((u8 *)actor + (0x9D))) = 0;
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_14 = 0;
                    ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u |= 0x08000000;
                }
            }
        } else {
            if (!(((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 & 0x40)) {
                status_flags = (*(u16 *)((u8 *)actor + (0x98)));
                if (status_flags & 0x8000) {
                    (*(u16 *)((u8 *)actor + (0x98))) = status_flags & 0x7FFF;
                    animation_table = ((R17_80170BB8_S_80170BB8_1 *)object)->unk_2C;
                    if (animation_table == ((u8 *)D_8017449C)) {
                        (*(u8 * *)((u8 *)object + (0x2C))) = ((u8 *)D_80174494);
                        func_80047784(object,
                            ((u8 *)D_80174494)[((g_game_work.view.viewAngle + ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_2A + 0x100)
                                >> 9) & 7],
                            0);
                    } else if (animation_table == ((u8 *)D_80174494)) {
                        (*(u8 * *)((u8 *)object + (0x2C))) = ((u8 *)D_8017449C);
                        func_80047784(object,
                            ((u8 *)D_8017449C)[((g_game_work.view.viewAngle + ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_2A + 0x100)
                                >> 9) & 7],
                            0);
                    }
                }
                if (((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 & 0x6000) {
                    (*(u16 *)((u8 *)actor + (0x98))) |= 0x8000;
                    if (((R17_80170BB8_S_80170BB8_1 *)object)->unk_2C == ((u8 *)D_80174494)) {
                        (*(s16 *)((u8 *)actor + (0xA8))) = 0;
                    }
                }
                bob_wave = func_800644B8(((*(s16 *)((u8 *)actor + (0xA8))) << 12) / 21);
                bob = bob_wave >> 8;
                if ((*(u8 *)((u8 *)actor + (0x9A))) == 0x12) {
                    bob = bob_wave >> 10;
                }
                (*(s16 *)((u8 *)actor + (0xA8)))++;
            }

            if (!((*(u16 *)((u8 *)actor + (0x98))) & 8)) {
                ground = (s16)(((s16)sample_terrain_surface_height(((R17_80170BB8_S_80170BB8_0 *)motion)->unk_00.at02.v,
                    ((R17_80170BB8_S_80170BB8_0 *)motion)->unk_04.at02.v,
                    (s16)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u - 0x20))) -
                    ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u);
                if ((*(s16 *)((u8 *)actor + (0x92))) > ground - 0x30) {
                    (*(s16 *)((u8 *)actor + (0x92))) = (*(s16 *)((u8 *)actor + (0x92))) - 8;
                } else if (ground - 0x3A > (*(s16 *)((u8 *)actor + (0x92)))) {
                    (*(s16 *)((u8 *)actor + (0x92))) = (*(s16 *)((u8 *)actor + (0x92))) + 8;
                }
            }
        }

        (*(s16 *)((u8 *)actor + (0xA8))) = 0;
        (*(u16 *)((u8 *)actor + (0x98))) &= 0x7FFF;
    }

    if (((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0x40000000) {
        ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u = ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_1C.u & 0xBFFFFFFF;
        ground = ((s16)sample_terrain_surface_height((((R17_80170BB8_S_80170BB8_1 *)object)->unk_24 << 6) | 0x20,
            (((R17_80170BB8_S_80170BB8_1 *)object)->unk_25 << 6) | 0x20,
            (s16)(((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u - 0x20)));
        if (ground < 0x200) {
            (*(s16 *)((u8 *)actor + (0x92))) += ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u - ground;
            ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u = ground;
        }
    }
    height = ((R17_80170BB8_S_80170BB8_2 *)actor_state)->unk_88.u +
        (u16)(*(s16 *)((u8 *)actor + (0x92)));
    height += bob;
    *(s16 *)((u8 *)motion + 0xA) = height;
    ((R17_80170BB8_S_80170BB8_1 *)object)->unk_14 |= 0x40;
}
