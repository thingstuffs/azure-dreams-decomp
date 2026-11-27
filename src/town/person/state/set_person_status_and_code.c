#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/person/state.h"

extern void randomize_person_color(TownObjectRecord *object, TownObjectRecord *context, ObjectPosition *position, SpriteFrameState *sprite);

typedef struct S_800AAE00_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_800AAE00_0;   /* arg1 in set_person_status_and_code */


/* Set the status flag and initialize the context's data pointer and code. */
void set_person_status_and_code(TownObjectRecord *context, S_800AAE00_0 *status) {
    status->unk_15 = 1;
    context->state_callback.as_pm = &randomize_person_color;
    context->timer = 0x15;
}
