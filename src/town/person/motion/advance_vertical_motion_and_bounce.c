#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/person/position.h"
#include "town/person/motion.h"
#include "town/player.h"

#include "town/person/object_setup.h"
extern M2C_UNK person_bounce_handler_address;


/* Advance vertical motion, clamp at the landing height, and bounce or finish. */
void advance_vertical_motion_and_bounce(Rec_func_80094268_arg0 *actor, EntityRec *motion, void *context) {
    u16 bounces_left;

    motion->z.v = (s32) (motion->z.v + motion->flags14);
    if (query_lowered_transform_position(motion) < motion->z.w.i) {
        motion->z.w.i = query_lowered_transform_position(motion);
        bounces_left = actor->unk_90.as_u16 - 1;
        actor->unk_90.as_u16 = bounces_left;
        if ((bounces_left << 0x10) <= 0) {
            motion->flags14 = 0;
            apply_object_setup_and_update(actor, motion, context);
            return;
        }
        motion->flags14 = 0xFFF60000;
        actor->unk_54 = &person_bounce_handler_address;
        return;
    }
    add_hex_20000_s_signed_offset_hex_14(motion);
}
