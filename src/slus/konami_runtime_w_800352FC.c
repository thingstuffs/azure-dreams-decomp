#include "common.h"

#include "common.h"
s32 func_80034FFC(void *context);                   /* extern */
extern u8 D_80082A38[];

/* Pass the global object D_80082A38 to func_80034FFC. */
void func_800352FC(void) {
    func_80034FFC(&D_80082A38);
}
