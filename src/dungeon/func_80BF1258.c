/* Relink of matched dungeon/func_80BEB258; every changed retail word is a paired relocation. */
#define update_entity_facing_and_ground func_8016AA58
#define D_8017420C D_8016E20C
#define D_8017426C D_8016E26C
#include "modules/dungeon_resource16_slot0.h"
extern void func_8016B014(void *, void *, void *, void *);
extern s32 func_800644B8(s32);

void func_8016AA58(void *entity, EntityRec *motion, void *sprite)
{
    R16_80170A58_S_80170A58_2 *state = entity;
    s16 previous_state;
    s32 view_dir;
    u8 dir_index;
    s16 height_offset;
    u16 height_bits;
    s32 hover_limit;
    s16 ground_delta;
    s16 ground_height;
    u16 part_flags;
    s32 entity_flags;
    R16_80170A58_Callback gated_callback;
    R16_80170A58_Callback update_callback;

    if (g_dungeon_status.flags & 0x2000) {
        gated_callback = (*(R16_80170A58_Callback *)((u8 *)entity + 0x8C));
        if (gated_callback == (R16_80170A58_Callback)((u8 *)func_8016B014)) {
            gated_callback(entity, motion, sprite, entity);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }

    previous_state = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    if (refresh_actor_facing_and_lifecycle(entity, motion, sprite, entity) != 0) {
        return;
    }

    update_callback = (*(R16_80170A58_Callback *)((u8 *)entity + 0x8C));
    if (update_callback != 0) {
        update_callback(entity, motion, sprite, entity);
    }
    ((R16_80170A58_Callback *)D_8016E26C)[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, sprite, entity);
    if (previous_state != (*(s8 *)((u8 *)entity + 0x6D))) {
        try_move_actor_to_valid_position(entity, motion, sprite, entity);
    }

    motion->x.v += motion->unk_0C;
    motion->y.v += motion->unk_10;

    if (!((*(s32 *)((u8 *)entity + 0x1C)) & 0x40000) && !((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
        motion->flags14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D)) = (*(u8 *)((u8 *)entity + 0x9D)) + 1;
    } else {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += motion->flags14;

    part_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
    if (!(part_flags & 0x8000)) {
        view_dir = ((g_game_work.view.viewAngle + state->unk_2A + 0x100) >> 9) & 7;
        dir_index = view_dir;
        if ((*(s16 *)((u8 *)entity + 0x94)) != dir_index) {
            select_indirect_table_entry(sprite,(u8)(((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8[dir_index]),(s8)(((Rec_D_80082E80 *)sprite)->unk_04.as_s8));
            (*(s16 *)((u8 *)entity + 0x94)) = view_dir;
        }
        if (dir_sprite_flag[dir_index] != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 1;
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xFFFE;
        }
        apply_monster_koyaw_data(state->unk_1C, (u8 *)sprite + 0xC);
        if (!(state->unk_1C & 0x20)) {
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
                func_800478B8(sprite);
            }
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x7000;
            state->unk_1C &= 0xFFFBFFFF;
        }

        entity_flags = state->unk_1C;
        entity_flags &= 0xF7FFFFFF;
        state->unk_1C = entity_flags;
        entity_flags &= 0x40000;
        if (entity_flags != 0) {
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
                if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 == ((u8 *)D_8016E20C)) {
                    u16 bob_tick = (*(u16 *)((u8 *)entity + 0x9E));
                    (*(u16 *)((u8 *)entity + 0x9E)) = bob_tick + 1;
                    (*(s32 *)((u8 *)entity + 0xA0)) += func_800644B8((s16)bob_tick * 0xAA) << 5;
                }
            }
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                sample_terrain_surface_height(((u16)motion->x.w.i), ((u16)motion->y.w.i),(s16)((s16)(state->unk_88 - 0x20)));
                hover_limit = -0x20;
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                height_bits = (*(u16 *)((u8 *)entity + 0x92));
                if (height_offset > hover_limit) {
                    (*(u16 *)((u8 *)entity + 0x92)) = height_bits - 8;
                } else if (height_offset < -0x28) {
                    (*(u16 *)((u8 *)entity + 0x92)) = height_bits + 8;
                }
            }
        } else {
            s32 bob_offset = (*(s32 *)((u8 *)entity + 0xA0));
            (*(u16 *)((u8 *)entity + 0x9E)) = 0;
            (*(s32 *)((u8 *)entity + 0xA0)) = 0;
            (*(s32 *)((u8 *)entity + 0x90)) -= bob_offset;
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                ground_delta = sample_terrain_surface_height(((u16)motion->x.w.i), ((u16)motion->y.w.i),(s16)((s16)(state->unk_88 - 0x20))) -
                        state->unk_88;
                if (ground_delta < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = ground_delta;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->flags14 = 0;
                    state->unk_1C |= 0x8000000;
                }
            }
        }
    } else {
        if (!(part_flags & 0x800)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = part_flags | 0x7000;
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = part_flags & 0x8FFF;
        }

        entity_flags = state->unk_1C;
        entity_flags &= 0xF7FFFFFF;
        state->unk_1C = entity_flags;
        entity_flags &= 0x40000;
        if (entity_flags == 0) {
            s32 bob_offset = (*(s32 *)((u8 *)entity + 0xA0));
            (*(u16 *)((u8 *)entity + 0x9E)) = 0;
            (*(s32 *)((u8 *)entity + 0xA0)) = 0;
            (*(s32 *)((u8 *)entity + 0x90)) -= bob_offset;
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                ground_delta = sample_terrain_surface_height(((u16)motion->x.w.i), ((u16)motion->y.w.i),(s16)((s16)(state->unk_88 - 0x20))) -
                        state->unk_88;
                if (ground_delta < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = ground_delta;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->flags14 = 0;
                    state->unk_1C |= 0x8000000;
                }
            }
        } else {
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
                if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 == ((u8 *)D_8016E20C)) {
                    u16 bob_tick = (*(u16 *)((u8 *)entity + 0x9E));
                    (*(u16 *)((u8 *)entity + 0x9E)) = bob_tick + 1;
                    (*(s32 *)((u8 *)entity + 0xA0)) += func_800644B8((s16)bob_tick * 0xAA) << 5;
                }
            }
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                sample_terrain_surface_height(((u16)motion->x.w.i), ((u16)motion->y.w.i),(s16)((s16)(state->unk_88 - 0x20)));
                hover_limit = -0x20;
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                height_bits = (*(u16 *)((u8 *)entity + 0x92));
                if (height_offset > hover_limit) {
                    (*(u16 *)((u8 *)entity + 0x92)) = height_bits - 8;
                } else if (height_offset < -0x28) {
                    (*(u16 *)((u8 *)entity + 0x92)) = height_bits + 8;
                }
            }
        }
    }

    entity_flags = state->unk_1C;
    if (entity_flags & 0x40000000) {
        state->unk_1C = entity_flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height((((Rec_D_80082E80 *)sprite)->unk_24 << 6) | 0x20,
                               (((Rec_D_80082E80 *)sprite)->unk_25 << 6) | 0x20,(s16)((s16)(state->unk_88 - 0x20)));
        if ((s16)ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + 0x92)) =
                (*(u16 *)((u8 *)entity + 0x92)) + (state->unk_88 - ground_height);
            state->unk_88 = ground_height;
        }
    }

    motion->z.w.i = state->unk_88 + (*(u16 *)((u8 *)entity + 0x92)) -
                            (*(u16 *)((u8 *)entity + 0xA2));
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x40;
}
