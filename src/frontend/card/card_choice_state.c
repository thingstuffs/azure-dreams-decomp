#include "frontend/libcard/interfaces.h"
/* Update the paired card choice selection and animation state. */

#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_80026FD4_0 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_80026FD4_0;

/* Stores a value in the object's embedded state and processes that state. */
void card_boot_set_paired_choice_selection(s32 object_addr, s32 value) {
    S_80026FD4_0 *state;

    state = object_addr + 0x20;
    state->unk_24 = value;
    card_boot_refresh_paired_choice_labels((u8 *)state);
}
#include "common.h"
#include "frontend/card.h"

typedef struct Object13B18 Object13B18;

/* Pass the data at offset 0x20 to card_boot_set_paired_choice_animations. */
void card_boot_update_paired_choice_animations(ObjectNodeHeader *base_addr, s32 *enable_flags, s32 *active_flags) {
    card_boot_set_paired_choice_animations((Object13B18 *)(base_addr + 1), enable_flags, active_flags);
}
