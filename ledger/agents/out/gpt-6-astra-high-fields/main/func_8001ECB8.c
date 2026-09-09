#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

typedef struct S_func_80405CB8_0 {
    u8 pad_00[0x10];
    void *unk_10;
    u8 pad_14[0x34];
    s32 unk_48;
    u8 pad_4C[0x8];
    void *unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_func_80405CB8_0;

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
    S_func_80405CB8_0 *object_base;
    s32 operation_result;

    operation_result = func_80402154(((S_func_80405CB8_0 *)((u8 *)context - 0x20))->unk_48, 0x80010000);
    object_base = (S_func_80405CB8_0 *)((u8 *)context - 0x20);
    if (operation_result == 0) {
        ((S_func_80405CB8_0 *)((u8 *)context - 0x20))->unk_54 = func_80406368;
        func_8040325C(object_base);
        next_callback = func_80405A3C;
    } else {
        func_80405C44(0x80010000);
        next_callback = func_80405C4C;
    }
    ((S_func_80405CB8_0 *)((u8 *)context - 0x20))->unk_10 = next_callback;
    func_80400908();
    ((S_func_80405CB8_0 *)((u8 *)context - 0x20))->unk_60 = 0;
}
