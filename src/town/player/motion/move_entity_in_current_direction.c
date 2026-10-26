#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_80097D54_arg0.h"
#include "town/person/position.h"

extern s32 initialize_target_and_handler_table();

/* Move the entity in its current direction until the movement countdown expires. */
void move_entity_in_current_direction(Rec_func_80097D54_arg0 *move_state, EntityRec *entity, s32 finish_arg) {
    s16 direction;
    u16 steps_left;

    entity->z.w.i = query_lowered_transform_position(entity);
    steps_left = move_state->unk_0A - 1;
    move_state->unk_0A = steps_left;
    if ((s16)steps_left < 0) {
        initialize_target_and_handler_table(move_state, entity, finish_arg);
        return;
    }
    direction = move_state->unk_10;
    switch (direction) {
    case 0x400:
        entity->x.v += 0x120000;
        break;
    case 0xC00:
        entity->x.v -= 0x120000;
        break;
    case 0:
        entity->y.v += 0x120000;
        break;
    default:
        entity->y.v -= 0x120000;
        break;
    }
}
