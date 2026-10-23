#include "shared/actor_property_flags.h"
#include "common.h"

#include "common.h"
#include "slus/data.h"
#include "engine/entity.h"

typedef struct {
    u8 pad[0x13];
    u8 id;
    s32 flags;
} Entity;


/* Returns the entity class from shared initial-stat flags or its lowest class flag. */
s32 get_entity_class(Entity *entity)
{
    s32 flags = entity->flags;
    s32 class_id = 0;

    if (flags & ACTOR_CLASS_ENABLED) {
        s32 entity_id = entity->id;
        s32 stats_offset = entity_id << 1;
        s32 shared_flags;
        s32 class_bits;

        stats_offset += entity_id;
        stats_offset <<= 3;
        shared_flags = ((EntityInitialStats *)((u8 *)initialStatsTable + stats_offset))->flags & flags;
        class_bits = shared_flags & ACTOR_ELEMENT_MASK;

        if (class_bits != 0) {
            u8 *class_table = entity_class_lookup;
            class_id = class_table[class_bits];
        } else if (flags & ACTOR_ELEMENT_FIRE) {
            class_id = 1;
        } else if (flags & ACTOR_ELEMENT_WATER) {
            class_id = 2;
        } else if (flags & ACTOR_ELEMENT_WIND) {
            class_id = 3;
        }
    }

    return class_id;
}
