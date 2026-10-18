#include "common.h"

#include "common.h"
typedef struct S_8003832C_0 S_8003832C_0;
void func_8003832C(S_8003832C_0 *context);                         /* extern */
s32 func_80053EF0();                         /* extern */

/* Call the handler when check 4 returns zero. */
void func_800382F0(s32 handler_arg) {
    if (func_80053EF0(4) == 0) {
        func_8003832C(handler_arg);
    }
}
