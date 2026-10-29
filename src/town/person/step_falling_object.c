#include "common.h"
#include "shared/entity.h"
#include "records/Rec_D_80082D58.h"
#include "town/person/position.h"
#include "engine/node.h"
#include "town/player.h"
#include "town/scene.h"

extern void load_indexed_state_value(void *, void *, s32); /* Unprototyped: retail call passes more arguments than the callee reads */
extern s32 D_800D636C[2];


/* Advance motion and handle ground contact or continued movement. */
void step_falling_object(Rec_D_80082D58 *entity, EntityRec *motion, s32 context)
{
    s32 *velocity;
    u16 contacts_left;

    velocity = D_800D636C;
    motion->x.v += velocity[0];
    motion->y.v += velocity[1];
    motion->z.v += motion->flags14;
    if (query_lowered_transform_position(motion) < motion->z.w.i) {
        motion->z.w.i = query_lowered_transform_position(motion);
        contacts_left = entity->unk_90.as_u16 - 1;
        entity->unk_90.as_u16 = contacts_left;
        if ((s16)contacts_left < 0) {
            unlink_node_if_registered(entity);
            func_800C8D34(entity, motion, context);
            return;
        }
        load_indexed_state_value(entity, motion, context);
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(motion);
}
