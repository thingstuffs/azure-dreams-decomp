#include "common.h"

#include "common.h"
s32 test_runtime_handler_or_fallback_status(void *context);                   /* extern */
extern u8 D_80082A38[];

/* Pass the global object D_80082A38 to func_80034FFC. */
void service_script_controller(void) {
    test_runtime_handler_or_fallback_status(&D_80082A38);
}
