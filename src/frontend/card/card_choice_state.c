#include "frontend/libcard/paired_choice.h"
#include "frontend/libcard/interfaces.h"
/* Update the paired card choice selection and animation state. */

#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"


/* Stores a value in the object's embedded state and processes that state. */
void card_boot_set_paired_choice_selection(ObjectNodeHeader *object_addr, s32 value) {
    void *body = object_addr + 1;
    CardChoiceOwner *state = body;
    state->selection = value;
    card_boot_refresh_paired_choice_labels(body);
}
#include "frontend/card.h"

typedef struct Object13B18 Object13B18;

/* Pass the data at offset 0x20 to card_boot_set_paired_choice_animations. */
void card_boot_update_paired_choice_animations(ObjectNodeHeader *base_addr, s32 *enable_flags, s32 *active_flags) {
    card_boot_set_paired_choice_animations(NODE_BODY(base_addr), enable_flags, active_flags);
}
