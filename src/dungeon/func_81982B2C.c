#include "modules/dungeon_ovl_19a332c.h"

void initialize_entity_position_and_motion(ovl_19a332c_81982B2C_Entity *entity, ovl_19a332c_81982B2C_Position *position, ovl_19a332c_81982B2C_Motion *motion)
{
    s16 state;
    void *actor;
    u16 *base_coords;

    D_800269F8++;
    state = entity->state;

    if (state == 0) {
        actor = entity->inner->actor;
        if (entity->active == 0) {
            if (resolve_record_orientation_or_fallback(*(s32 *)((u8 *)actor + 8), actor,
                              &entity->x, 0) != 0) {
                entity->active = 1;
            } else if (*(u16 *)((u8 *)actor + 0x14) & 0x8000) {
                entity->active = 1;
                entity->z = -0x40;
            }
            if (entity->active == 0) {
                return;
            }
        }

        base_coords = entity->inner->coords;
        position->x = base_coords[1] + entity->x;
        position->y = base_coords[3] + entity->y;
        position->z = base_coords[5] + entity->z;
        func_8004491C((u8 *)entity - 0x20, func_80045340);
        entity->state++;
        return;
    }

    if (state == 1) {
        if ((u8)motion->value < 0xC0) {
            motion->value += 0x00202020;
            return;
        }
        if (create_nine_linked_effects(position->x, position->y, position->z,
                          *(s16 *)(((u8 **)&D_80027C98)[0] + 0x2A)) != 0) {
            entity->state++;
        }
        return;
    }

    if (state == 2) {
        motion->value += 0xFFFBFBFC;
        if ((u8)motion->value == 0) {
            *(u16 *)((u8 *)entity - 2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}
