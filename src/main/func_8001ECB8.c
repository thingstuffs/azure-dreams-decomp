#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern s32 func_80402154(s32 arg0, s32 arg1);
extern void func_8040325C(void *arg0);
extern void func_80405C44(s32 arg0);
extern void func_80400908(void);
extern void func_80406368(void);
extern void func_80405A3C(void);
extern void func_80405C4C(void);

// Selects the next callback based on the operation result and clears the context's state field.
void func_80405CB8(void *context)
{
    void (*next_callback)(void);
    void *object_base;
    s32 operation_result;

    operation_result = func_80402154(FIELD(context, s32 *, 0x28), 0x80010000);
    object_base = (u8 *)context - 0x20;
    if (operation_result == 0) {
        FIELD(context, void (**)(void), 0x34) = func_80406368;
        func_8040325C(object_base);
        next_callback = func_80405A3C;
    } else {
        func_80405C44(0x80010000);
        next_callback = func_80405C4C;
    }
    FIELD(context, void (**)(void), -0x10) = next_callback;
    func_80400908();
    FIELD(context, s32 *, 0x40) = 0;
}
