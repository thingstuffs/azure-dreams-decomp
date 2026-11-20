#include "engine/message.h"
#include "engine/message/data.h"

#include "engine/object.h"

/* Clears the state field and entries 10 through 14. */
void clear_script_pending_values(void)
{
    s32 entry_index;

    runtime_script_state.script_start = 0;
    for (entry_index = 10; entry_index < 15; entry_index++) {
        runtime_script_state.variables[entry_index] = 0;
    }
}
