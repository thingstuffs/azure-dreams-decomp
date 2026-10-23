#include "common.h"

#include "common.h"
#include "engine/object.h"
#include "slus/data.h"

typedef struct {
    u8 pad_00[0x38];
    s32 field_38;
    u8 pad_3C[0xC];
    s32 entries[15];
} State80082A38;

extern State80082A38 runtime_script_state;

extern s32 service_script_controller(void);
extern void call_script(void *reset_value);

/*
 * Enqueues the supplied value, first clearing slots 10 through 14 and starting
 * runtime_pool_service_script when that script is not already active. Returns one.
 */
s32 enqueue_runtime_pool_script(void *input_data) {
    s32 entry_index;

    if (service_script_controller() == 0 || runtime_script_handler_alias[0] != runtime_pool_service_script) {
        for (entry_index = 10; entry_index < 15; entry_index++) {
            runtime_script_state.entries[entry_index] = 0;
        }
        runtime_store_value_in_shifted_slot_pool(input_data);
        call_script(runtime_pool_service_script);
    } else {
        runtime_store_value_in_shifted_slot_pool(input_data);
    }
    return 1;
}
