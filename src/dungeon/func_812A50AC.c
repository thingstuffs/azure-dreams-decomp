#include "modules/dungeon_ovl_12c50ac.h"

void *create_and_initializes_entity_center_specified_tile(s16 entity_id, s16 tile_x, u16 tile_y, u16 height) {
    Func812A5000Parent *parent;
    Func812A5000Child *tile_state;
    Func812A5000Child *position;
    Func812A5000Entity *entity;

    entity = NULL;
    parent = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (parent != NULL) {
        if (D_800FBE1C[0] == 0) {
            D_800FBE1C[0] = parent;
        }
        entity = (Func812A5000Entity *)((u8 *)parent + 0x20);
        parent->field10 = func_80170A4C;
        entity->field13 = 0x39;
        func_8004491C(parent, func_80045340);
        tile_state = parent->child0;
        position = parent->child1;
        tile_state->field24 = tile_x;
        tile_state->field25 = tile_y;
        tile_state->field2C = D_80175C30;
        position->field2 = (s16)((tile_state->field24 << 6) + 0x20);
        position->field6 = (s16)((tile_state->field25 << 6) + 0x20);
        position->fieldA = height;
        entity->field2A = (s16)(get_direction_toward_target_position(position) << 9);
        entity->field13 = 2;
        entity->field14 |= 0x6000;
        entity->field1C |= 0x6000;
        initialize_actor_sprite_and_animation(parent, position, tile_state, entity_id);
        entity->field9A = 0xFF;
        entity->field9C = -1;
        entity->field8C = D_80171FA4;
        entity->field92 = -0x20;
        entity->field13 = 0x39;
        entity->field1C |= 0x40000;
        try_move_actor_to_valid_position(entity, position, tile_state, entity);
    }
    return entity;
}
