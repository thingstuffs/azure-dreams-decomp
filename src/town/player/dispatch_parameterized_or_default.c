#include "common.h"
#include "m2c_compat.h"

void initialize_state_from_terminated_entries(s32);                            /* extern */
void initialize_mode_state_tables(void);                            /* extern */
extern s16 D_8006ADD4;

/* Dispatch to the parameterized handler in state 12 or the default handler otherwise. */
void dispatch_parameterized_or_default(s32 handler_param) {
    if (D_8006ADD4 == 0xC) {
        initialize_state_from_terminated_entries(handler_param);
        return;
    }
    initialize_mode_state_tables();
}
