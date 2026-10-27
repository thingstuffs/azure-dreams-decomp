#include "common.h"
#include "shared/actor_status.h"
#include "engine/entity.h"

#include "shared/entity.h"

/* Returns an effect value, 0x100 for a zero-valued match, or a type-specific fallback. */
s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id)
{
    s32 effect_type = effect_id;
    s16 saved_id = effect_id;
    s32 effect_index;

    effect_type = (u32)effect_type << 24;
    effect_type >>= 24;
    if (effect_type != 0) {
        for (effect_index = 3; effect_index >= 0; effect_index--) {
            if (entry->status[effect_index].type == effect_type) {
                s32 effect_value = entry->status[effect_index].value;

                if (effect_value == 0) {
                    return 0x100;
                }
                return effect_value;
            }
        }
    }
    {
        s32 result;
        s32 fallback_type;

        result = (u32)saved_id << 24;
        fallback_type = result >> 24;
        if (fallback_type == 0xE) {
            return entry->hp < 1;
        }
        result = 0xD;
        if (fallback_type != result) {
            result = 0;
        } else {
            result = 0;
            fallback_type = *((volatile s32 *)&entry->flags14);
        }
        return result;
    }
}
