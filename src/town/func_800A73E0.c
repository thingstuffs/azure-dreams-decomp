#include "common.h"
#include "shared/entity_objects.h"
#include "shared/vector.h"


extern IntVector3 D_80100D98;
extern u8 D_800A4F4C[];
extern void initialize_transition_state(void *);

/* Copy the default state and initialize the supplied control block. */
void initialize_control_block(void *control) {
    IntVector3 *dst = &D_80100D98;
    s32 value;

    D_80100D98.x = D_80083780.x.v;
    value = D_80083780.y.v;
    dst->z = D_80083780.z.v;
    dst->y = value;
    *(void **)((u8 *)control + 0x24) = D_800A4F4C;
    *(s32 *)((u8 *)control + 0x30) = 0;
    initialize_transition_state(control);
}
