#include "common.h"
#include "shared/record_ptrs.h"

extern void func_80016CC4(void);
extern s32 func_8001A554(s32 flag_id);
extern s32 func_8001A64C(s32 flag_id);
extern s32 func_8001A8EC(s32 value);

/* Update event flags when prerequisites are met, otherwise invoke the fallback callback. */
s32 func_80017D94(void) {
    func_80016CC4();
    if (func_8001A8EC(6) != 0) {
        func_8001A554(0x93A);
    }
    if (func_8001A8EC(0xB) != 0) {
        func_8001A554(0x93B);
    }
    if (func_8001A64C(0x93A) != 0 && func_8001A64C(0x94A) != 0) {
        func_8001A554(0x93C);
        return 1;
    }
    if (func_8001A64C(0x93B) != 0 && func_8001A64C(0x948) != 0) {
        func_8001A554(0x93C);
        func_8001A554(0x946);
        func_8001A554(0x947);
        return 1;
    }
    {
        s8 *context = *(s8 **)((u8 *)(&D_80016000));
        s8 *callback_table = *(s8 **)(context + 0x20);
        s32 (*fallback_fn)(s32, s32) = *(s32 (**)(s32, s32))(callback_table + 0x2F8);
        fallback_fn(0xF, 0x200);
    }
    return 0;
}
