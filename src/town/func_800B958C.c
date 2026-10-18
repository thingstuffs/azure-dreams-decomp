#include "common.h"

extern s32 func_80042900(void *, s8);
extern s32 normalize_monster_status_species_code(s32);
extern s32 func_80049E88(void *);

/* Returns a mapped code for the object, or its fallback value when the code is zero. */
s32 get_mapped_object_code(void *object) {
    s32 code = *((u8 *) object + 0x13);

    if (code != 0) {
        if ((func_80042900(object, 10) << 0x10) != 0) {
            code = 47;
        } else {
            code = normalize_monster_status_species_code(code);
        }
        return code;
    }
    return func_80049E88(object);
}
