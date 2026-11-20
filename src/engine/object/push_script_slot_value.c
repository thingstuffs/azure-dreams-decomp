#include "engine/script.h"
#include "engine/message.h"
#include "engine/message/data.h"

#include "engine/object.h"

/* When all five slots are occupied, keep the current script in slot 10 and replace the oldest pending script. */
void push_script_slot_value(s32 value) {
    s32 slot_index;

    for (slot_index = 10; slot_index < 15; slot_index++) {
        if (runtime_script_state.variables[slot_index] == 0) {
            runtime_script_state.variables[slot_index] = value;
            if (slot_index != 14) {
                runtime_script_state.variables[slot_index + 1] = 0;
            }
            return;
        }
    }

    for (slot_index = 11; slot_index < 14; slot_index++) {
        runtime_script_state.variables[slot_index] = runtime_script_state.variables[slot_index + 1];
    }
    runtime_script_state.variables[14] = value;
}
