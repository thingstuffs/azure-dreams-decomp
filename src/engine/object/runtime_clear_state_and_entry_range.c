#include "common.h"

#include "common.h"
#include "engine/object.h"

typedef struct {
    u8 pad_00[0x38];
    s32 field_38;
    u8 pad_3C[0xC];
    s32 entries[15];
} State80082A38;

extern State80082A38 runtime_script_state;

/* Clears the state field and entries 10 through 14. */
void runtime_clear_state_and_entry_range(void)
{
    s32 entry_index;

    runtime_script_state.field_38 = 0;
    for (entry_index = 10; entry_index < 15; entry_index++) {
        runtime_script_state.entries[entry_index] = 0;
    }
}
