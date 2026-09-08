#include "common.h"

extern s32 D_80017D4C;
extern s32 D_80017AAC;
extern void func_8001A1A0(s32 value, s32 *address);

/* Process and return the stored value. */
s32 func_8001A834(void) {
    s32 *stored_value = &D_80017D4C;

    func_8001A1A0(*stored_value, &D_80017AAC);
    return *stored_value;
}
