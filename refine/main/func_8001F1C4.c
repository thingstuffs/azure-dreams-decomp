#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern s32 func_804022C8(s32 arg0);
extern void func_804033C4(void *arg0);
extern void func_80404688(s32 arg0);
extern void func_80406368(void);
extern void func_80405A64(void);

/* Updates state callbacks and processes five entries if the state check succeeds. */
void func_804061C4(void *state)
{
    s32 entry;
    s32 entry_count;

    if (FIELD(state, s32 *, 0x38) != 0) {
        FIELD(state, void (**)(void), -0x10) = func_80406368;
        goto end;
    }

    if (func_804022C8(FIELD(state, s32 *, 0x28)) != 0) {
        entry_count = 0;
        FIELD(state, void (**)(void), -0x10) = func_80406368;
        do {
            entry = FIELD(state, s32 *, 4);
            state = (u8 *)state + 4;
            entry_count++;
            func_80404688(entry);
        } while (entry_count < 5);
    } else {
        FIELD(state, void (**)(void), 0x34) = func_80406368;
        func_804033C4((u8 *)state - 0x20);
        FIELD(state, void (**)(void), -0x10) = func_80405A64;
    }

end:
    return;
}
