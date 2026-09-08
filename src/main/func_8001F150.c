#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern void func_804032FC(void *arg0);
extern void func_80406368(void);
extern void func_80405A64(void);
extern void func_80405FC4(void);
extern s32 D_8009DDD8[];

/* Selects the object's next callback based on whether its indexed entry is active. */
void func_80406150(void *object_state)
{
    void (*next_callback)(void);
    void *object_base;
    s32 entry_index;
    s32 entry_active;

    entry_index = FIELD(object_state, s32 *, 0x28);
    entry_active = *(s32 *)((u8 *)D_8009DDD8 + entry_index * 0x80);
    object_base = (u8 *)object_state - 0x20;
    if (entry_active != 0) {
        next_callback = func_80405FC4;
        FIELD(object_state, s32 *, 0x2C) = entry_index;
    } else {
        FIELD(object_state, void (**)(void), 0x34) = func_80406368;
        func_804032FC(object_base);
        next_callback = func_80405A64;
    }
    FIELD(object_state, void (**)(void), -0x10) = next_callback;
}
