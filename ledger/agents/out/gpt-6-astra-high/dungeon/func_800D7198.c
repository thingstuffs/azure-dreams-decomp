#include "common.h"

typedef void (*Func)(void *, s32);
typedef void (*FinalFunc)(void *);

extern Func D_800E2934[];
extern void func_800DC724(void *);

/* Runs callbacks for slots 1 through 7, then processes the object and its final callback. */
void func_800DC8F8(u8 *object) {
    s32 slot;
    Func *callback_table;
    Func *callback_cursor;
    Func callback;
    FinalFunc final_callback;

    slot = 1;
    callback_table = D_800E2934;
    callback_cursor = callback_table + 1;
    do {
        u8 *callback_object = object;

        ASM_KEEP(callback_object);   /* MATCH pin: keeps a statement from moving across a call/branch */
        callback = *callback_cursor++;
        callback(callback_object, *(s32 *)(object + 0x3C) + slot * 0x10);
        slot++;
    } while (slot < 8);
    func_800DC724(object);
    final_callback = *(FinalFunc *)(object + 0x4C);
    if (final_callback != 0) {
        final_callback(object);
    }
}
