#include "common.h"

extern s32 get_entity_effect_value(void *entry, s32 effect_id);
extern void clear_slots_of_type(void *entry, s32 effect_id);

/* Checks object code 0x19, exits on failure, and applies it on success. */
s32 consume_object_code_19(void *object) {
    if ((get_entity_effect_value(object, 0x19) << 0x10) != 0) {
        clear_slots_of_type(object, 0x19);
        return 1;
    }
    return 0;
}
