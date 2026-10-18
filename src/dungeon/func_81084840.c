#include "common.h"
#include "m2c_compat.h"

typedef struct S_80172040_0 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
} S_80172040_0;   /* arg0 in initialize_directional_action_state */

/* Initialize the object's two state bytes to 0x10 and zero. */
void initialize_directional_action_state(S_80172040_0 *object) {
    object->unk_9A = 0x10;
    object->unk_9B = 0;
}
