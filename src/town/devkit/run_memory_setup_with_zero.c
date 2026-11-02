#include "common.h"
#include "town/devkit.h"
#include "frontend/card/server_imports.h"

/* Run the setup sequence with a zero argument for func_8007CB08. */
void run_memory_setup_with_zero(void) {
    func_8007CA38();
    StartCARD2_804087A8();
    func_8007CB08(0);
    func_8007CA48();
}
