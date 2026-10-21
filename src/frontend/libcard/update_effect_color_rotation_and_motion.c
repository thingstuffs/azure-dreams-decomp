#include "common.h"
#include "m2c_compat.h"
#include "engine/texture.h"
#include "frontend/libcard.h"
#include "main/data.h"
typedef struct S_800491F4 S_800491F4;

/* Calls build_reverse_indexed_chain for the target with fixed data and a value of 0x15. */
void update_effect_color_rotation_and_motion(S_800491F4 **target) {
    build_reverse_indexed_chain(target, &D_80027FF8, 0x15);
}
