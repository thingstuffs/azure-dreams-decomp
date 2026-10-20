#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void func_80035164(void *controller, s32 reset_value, s32 requested_selector);
extern M2C_UNK D_80082A38;

/* Start a script in the global runtime with mode 1. */
void start_script(s32 script_addr) {
    func_80035164(&D_80082A38, script_addr, 1);
}
