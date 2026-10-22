#include "dungeon/monster/u_boat/create_owner_linked_directional_object.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/u_boat/create_owner_linked_directional_object.h"

/* Copies the owner's sprite and position into a tracked directional display with a view-dependent depth
 * offset. */
void create_owner_linked_directional_object(u8 *owner_data, u8 *source_position, u8 *source_sprite) {
    u8 *object;
    u8 *object_data;
    u8 *sprite;
    u8 *position;
    u8 *direction_table;

    object = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    object_data = object + 0x20;
    if (object != 0) {
        ((S_80D3B0B8_0 *)object_data)->unk_96 = 0x78;
        ((S_80D3B0B8_1 *)object)->unk_10 = D_800D5594;
        ((S_80D3B0B8_0 *)object_data)->unk_AC = owner_data - 0x20;
        ((S_80D3B0B8_0 *)object_data)->unk_94 = ((S_80D3B0B8_2 *)owner_data)->unk_2A.s;
        ((S_80D3B0B8_0 *)object_data)->unk_2A = ((S_80D3B0B8_2 *)owner_data)->unk_2A.s;
        sprite = ((S_80D3B0B8_1 *)object)->unk_0C;

        *(Copy48 *)sprite = *(Copy48 *)source_sprite;

        register_node(object, project_sprite_chain);
        direction_table = D_800E23F0;
        ((SpriteFrameState *)sprite)->frameTable = direction_table;
        select_sprite_entry(sprite,
            direction_table[((g_game_work.view.camera_rotation.parts.viewAngle +
                ((S_80D3B0B8_2 *)owner_data)->unk_2A.u + 0x100) >> 9) & 7], 0);

        position = ((S_80D3B0B8_1 *)object)->unk_08;
        ((S_80D3B0B8_5 *)position)->unk_02 = ((S_80D3B0B8_6 *)source_position)->unk_02;
        ((S_80D3B0B8_5 *)position)->unk_06 = ((S_80D3B0B8_6 *)source_position)->unk_06;
        ((S_80D3B0B8_5 *)position)->unk_0A = ((S_80D3B0B8_6 *)source_position)->unk_0A;
        {
            u16 sprite_field_1c;
            u16 sprite_field_1e;

            sprite_field_1c = ((S_80D3B0B8_7 *)source_sprite)->unk_1C;
            ((SpriteFrameState *)sprite)->scale_x = sprite_field_1c;
            sprite_field_1e = ((S_80D3B0B8_7 *)source_sprite)->unk_1E;
            ((SpriteFrameState *)sprite)->color.c.b = 0x80;
            ((SpriteFrameState *)sprite)->color.c.g = 0x80;
            ((SpriteFrameState *)sprite)->color.c.r = 0x80;
            ((SpriteFrameState *)sprite)->scale_y = sprite_field_1e;
        }
        ((SpriteFrameState *)sprite)->unk_06 =
            view_direction_depth_biases[((g_game_work.view.camera_rotation.parts.viewAngle +
                ((S_80D3B0B8_2 *)owner_data)->unk_2A.u + 0x100) >> 9) & 7] * 4;
        ((S_80D3B0B8_2 *)owner_data)->unk_B0++;
        create_tracked_effect(object, 0, sprite + 0x2C, object_data + 0x2A);
    }
}
