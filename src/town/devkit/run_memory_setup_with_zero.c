#include "common.h"
void func_8007CA38(void);                            /* extern */
void func_8007CA48(void);                            /* extern */
void func_8007CB08(s32);                     /* extern */
void func_804087A8(void);                            /* extern */

/* Run the setup sequence with a zero argument for func_8007CB08. */
void run_memory_setup_with_zero(void) {
    func_8007CA38();
    func_804087A8();
    func_8007CB08(0);
    func_8007CA48();
}
