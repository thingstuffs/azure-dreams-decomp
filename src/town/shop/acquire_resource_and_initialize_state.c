#include "common.h"
#include "m2c_compat.h"

s32 create_callback_pair_default();                         /* extern */
void get_zero_based_group_index();                      /* extern */
s32 get_mode_selected_value();                                /* extern */
void collect_enabled_entry_pointers();                    /* extern */
s32 count_nonzero_entries();                             /* extern */

typedef struct S_800B29D0_0 {
    u8 pad_00[0x38];
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
} S_800B29D0_0;   /* arg0 in acquire_resource_and_initialize_state */

/* Acquires a resource and initializes its associated state on success. */
s32 acquire_resource_and_initialize_state(void *state) {
    s32 resourceHandle;
    s32 resourceConfig;

    resourceHandle = create_callback_pair_default(0x100);
    ((S_800B29D0_0 *)state)->unk_40 = resourceHandle;
    if (resourceHandle != 0) {
        resourceConfig = get_mode_selected_value();
        ((S_800B29D0_0 *)state)->unk_44 = resourceConfig;
        collect_enabled_entry_pointers(((S_800B29D0_0 *)state)->unk_40, resourceConfig);
        ((S_800B29D0_0 *)state)->unk_38 = count_nonzero_entries(((S_800B29D0_0 *)state)->unk_40);
        get_zero_based_group_index(state + 0x2C);
    }
    return ((S_800B29D0_0 *)state)->unk_40;
}
