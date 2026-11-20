#include "common.h"
#include "town/shop/item_lookup.h"
#include "town/scene/collision.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
#include "records/Rec_D_80082D58.h"
#include "shared/object_links.h"
#include "shared/vector.h"
#include "town/scene/paired_value_dispatch_g00647.h"
#include "shared/town_object.h"
#include "engine/node.h"
#include "town.h"
#include "town/player/position.h"
#include "town/scene/object.h"
#include "town/shop.h"
#include "town/scene.h"
#include "town/scene/motion.h"
#include "engine/object.h"
#include "town/shop/target_position_data.h"

typedef struct { s32 words[21]; } TownRecord;


   /* the 0x2 bytes before arg0 in move_item_to_shop_target_and_store, addressed as arg0[-1] */

void itm_mon_koyaw_set(s32 slot, u8 *entry_flags, TownRecord *record, s8 record_byte);

/* Move toward the target and finalize the object when its countdown expires. */
void move_item_to_shop_target_and_store(void *object_arg, struct ColliderView *context, ObjectPosition *motion) {
    Rec_D_80082D58 *object = object_arg;
    s32 *global_flags;
    u16 ticks_or_flags;

    motion->velocity_x = (shop_target_position.x.v - motion->x.v) / 2;
    motion->velocity_y = (shop_target_position.y.v - motion->y.v) / 2;
    motion->velocity_z = (shop_target_position.z.v - motion->z.v) / 2;
    add_motion_deltas_to_position(motion);
    apply_bound_adjustments(context, motion);
    resolve_collider_overlaps(context, motion);
    ticks_or_flags = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = ticks_or_flags;
    if ((ticks_or_flags << 0x10) <= 0) {
        itm_mon_koyaw_set(D_80100B68, object_arg + 0x4C, &town_slot_snapshot, 0);
        unlink_scene_list_node(object_arg);
        unlink_node_if_registered(object);
        ticks_or_flags = ((ObjectRetirementFlags *)object)[-1].flags;
        global_flags = ((s32 *)(&object_flag_block));
        (*(u16 *)((u8 *)object + -2)) = (u16) (ticks_or_flags | 0x8000);
        *global_flags = *global_flags | 0x8000;
        dispatch_paired_table_values();
    }
}
