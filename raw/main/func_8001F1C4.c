#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern s32 func_804022C8(s32 arg0);
extern void func_804033C4(void *arg0);
extern void func_80404688(s32 arg0);
extern void func_80406368(void);
extern void func_80405A64(void);

void func_804061C4(void *arg0)
{
    s32 temp_a0;
    s32 count;

    if (FIELD(arg0, s32 *, 0x38) != 0) {
        FIELD(arg0, void (**)(void), -0x10) = func_80406368;
        goto end;
    }

    if (func_804022C8(FIELD(arg0, s32 *, 0x28)) != 0) {
        count = 0;
        FIELD(arg0, void (**)(void), -0x10) = func_80406368;
        do {
            temp_a0 = FIELD(arg0, s32 *, 4);
            arg0 = (u8 *)arg0 + 4;
            count++;
            func_80404688(temp_a0);
        } while (count < 5);
    } else {
        FIELD(arg0, void (**)(void), 0x34) = func_80406368;
        func_804033C4((u8 *)arg0 - 0x20);
        FIELD(arg0, void (**)(void), -0x10) = func_80405A64;
    }

end:
    return;
}
