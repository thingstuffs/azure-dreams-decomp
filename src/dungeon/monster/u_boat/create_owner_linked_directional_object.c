#include "dungeon/monster/u_boat/create_owner_linked_directional_object.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/u_boat/create_owner_linked_directional_object.h"
#include "dungeon/monster/u_boat.h"

/* Copies the owner's sprite and position into a tracked directional display with a view-dependent depth
 * offset. */
void create_owner_linked_directional_object(ActorRecord *owner_data, ObjectPosition *source_position, SpriteFrameState *source_sprite) {
    ObjectNodeHeader *object;
    u8 *object_data;
    SpriteFrameState *sprite;
    ObjectPosition *position;
    u8 *direction_table;

    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    object_data = ((u8 *)object) + 0x20;
    if (object != 0) {
        ((S_80D3B0B8_0 *)object_data)->unk_96 = 0x78;
        object->update_callback = D_800D5594;
        ((S_80D3B0B8_0 *)object_data)->unk_AC = (ObjectNodeHeader *)owner_data - 1;
        ((S_80D3B0B8_0 *)object_data)->unk_94 = ((S_80D3B0B8_2 *)owner_data)->unk_2A.s;
        ((S_80D3B0B8_0 *)object_data)->unk_2A = ((S_80D3B0B8_2 *)owner_data)->unk_2A.s;
        sprite = object->sprite;

        *(Copy48 *)sprite = *(Copy48 *)source_sprite;

        register_node(object, project_sprite_chain);
        direction_table = D_800E23F0;
        sprite->frameTable = direction_table;
        select_sprite_entry(sprite,
            direction_table[((g_game_work.view.camera_rotation.parts.viewAngle +
                owner_data->facing + 0x100) >> 9) & 7], 0);

        position = object->position;
        position->x.w.i = ((S_80D3B0B8_6 *)source_position)->unk_02;
        position->y.w.i = ((S_80D3B0B8_6 *)source_position)->unk_06;
        position->z.w.i = ((S_80D3B0B8_6 *)source_position)->unk_0A;
        {
            u16 sprite_field_1c;
            u16 sprite_field_1e;

            sprite_field_1c = source_sprite->scale_x;
            sprite->scale_x = sprite_field_1c;
            sprite_field_1e = source_sprite->scale_y;
            sprite->color.c.b = 0x80;
            sprite->color.c.g = 0x80;
            sprite->color.c.r = 0x80;
            sprite->scale_y = sprite_field_1e;
        }
        sprite->depth_bias =
            view_direction_depth_biases[((g_game_work.view.camera_rotation.parts.viewAngle +
                owner_data->facing + 0x100) >> 9) & 7] * 4;
        owner_data->unk_B0.bytes[0]++;
        create_tracked_effect(object, 0, ((u8 *)sprite) + 0x2C, object_data + 0x2A);
    }
}
