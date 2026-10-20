#include "dungeon/monster/troll/troll_flash_effects.h"

/* Create and position an effect using a linked object or stored tile coordinates. */
void create_actor_action_effect(void *source_object, void *source_pos, void *sprite_template, EntityRec *actor)
{
    void *effect;
    void *effect_state;
    void *effect_data;
    void *template_data;
    void *linked_pos;
    u16 pos_offset[4];

    if (((s32)actor->target) == 0 &&actor->unk_72 >= 0) {
        return;
    }
    effect = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (effect == 0) {
        return;
    }
    effect_state = (u8 *)effect + 0x20;
    ((T_801714FC_S_801714FC_1 *)effect_state)->unk_96 = 0xa;
    ((T_801714FC_S_801714FC_1 *)effect_state)->unk_9E = 0xa;
    ((T_801714FC_S_801714FC_2 *)effect)->unk_10 = (void *)&update_normalized_gray_fade;
    ((T_801714FC_S_801714FC_1 *)effect_state)->unk_94 = ((u16)actor->facing);
    effect_data = ((T_801714FC_S_801714FC_2 *)effect)->unk_0C;
    template_data = sprite_template;
    {
        Blk16 *src_block = (Blk16 *)template_data;
        Blk16 *dst_block = (Blk16 *)effect_data;
        Blk16 *src_end = src_block + 3;
        do {
            *dst_block = *src_block;
            dst_block++;
            src_block++;
        } while (src_block != src_end);
    }
    ((T_801714FC_S_801714FC_3 *)effect_data)->unk_1E = 0x1000;
    ((T_801714FC_S_801714FC_3 *)effect_data)->unk_1C = 0x1000;
    ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0E = 0x80;
    ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0D = 0x80;
    ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0C = 0x80;
    ((T_801714FC_S_801714FC_3 *)effect_data)->unk_14 = ((T_801714FC_S_801714FC_3 *)effect_data)->unk_14 & 0xfff3;
    register_node(effect, project_sprite_chain);
    (*(void * *)((u8 *)effect_data + 0x2c)) = (void *)&D_80175EB4;
    select_sprite_entry(effect_data,
        ((u8 *)&D_80175EB4)[(((s32)g_game_work.view.viewAngle + (s32)actor->facing + 0x100) >> 9) & 7],
        0);
    effect_data = ((T_801714FC_S_801714FC_2 *)effect)->unk_08;
    if (((s32)actor->target) != 0 && (actor->flags14 & 0x04000000) == 0) {
        u8 *direction_offsets = (u8 *)((u8 *)D_80175EBC);
        linked_pos = ((T_801714FC_S_801714FC_8_pre *)(actor->target))[-1].unk_00;
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_02 = ((T_801714FC_S_801714FC_4 *)linked_pos)->unk_02
        - ((*(s16 *)((u8 *)direction_offsets + ((((u16)actor->facing) >> 7) & 0x1c))) * 0x10);
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_06 = ((T_801714FC_S_801714FC_4 *)linked_pos)->unk_06
        - ((*(s16 *)((u8 *)direction_offsets + (((((u16)actor->facing) >> 7) & 0x1c) + 2))) * 0x10);
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0A = ((T_801714FC_S_801714FC_4 *)linked_pos)->unk_0A
        - (D_800DDC40[((T_801714FC_S_801714FC_8 *)(actor->target))->unk_13] >> 1);
        return;
    }
    if (actor->unk_72 < 0) {
        s32 tile_x, tile_y;
        actor->unk_72 = -(u8)((u8)actor->unk_72);
        if (actor->unk_73 < 0) {
            actor->unk_73 = -(u8)((u8)actor->unk_73);
        }
        tile_x = actor->unk_72;
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_02 = (tile_x << 6) + 0x20;
        tile_y = actor->unk_73;
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_06 = (tile_y << 6) + 0x20;
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0A = ((Rec_func_8017121C_arg1 *)source_pos)->unk_0A;
        {
            void *source_data = ((T_801714FC_S_801714FC_6_pre *)source_object)[-1].unk_00;
            if (resolve_record_orientation_or_fallback(((T_801714FC_S_801714FC_7 *)source_data)->unk_08, source_data, pos_offset, 0) != 0) {
                ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0A = ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0A + pos_offset[2];
                return;
            }
        }
        ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0A = ((T_801714FC_S_801714FC_3 *)effect_data)->unk_0A - 0x28;
    }
}
