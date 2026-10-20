#include "common.h"

extern s32 get_entity_effect_value(void *, s8);
extern s32 normalize_monster_status_species_code(s32);
extern s32 select_mapped_object_status_code(void *);

/* Returns a mapped code for the object, or its fallback value when the code is zero. */
s32 get_mapped_object_code(void *object) {
    s32 code = *((u8 *) object + 0x13);

    if (code != 0) {
        if ((get_entity_effect_value(object, 10) << 0x10) != 0) {
            code = 47;
        } else {
            code = normalize_monster_status_species_code(code);
        }
        return code;
    }
    return select_mapped_object_status_code(object);
}
