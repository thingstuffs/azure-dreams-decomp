#include "engine/message.h"
#include "engine/message/data.h"

#include "engine/object.h"
#include "slus/data.h"
#include "engine/script.h"

/* Queue a script address in variables 10 through 14, starting the service if needed. */
s32 queue_pool_service_script(void *script) {
    s32 address = (s32)(unsigned long)script;
    s32 entry_index;

    if (service_script_controller() == 0 || runtime_script_state.script_start != runtime_pool_service_script) {
        for (entry_index = 10; entry_index < 15; entry_index++) {
            runtime_script_state.variables[entry_index] = 0;
        }
        push_script_slot_value(address);
        call_script(runtime_pool_service_script);
    } else {
        push_script_slot_value(address);
    }
    return 1;
}
