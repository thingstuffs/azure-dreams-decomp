#include "common.h"

#include "common.h"

extern void func_8003C0C8(void *arg0, void *arg1);
extern u32 D_80083160[];

/* Runs the entry callback, then processes the entry and sets the output field unless flagged to stop. */
void func_8003C3B4(void *entry, void *output, void *context) {
    u8 *runtime_state;
    s32 field_value;
    void (*callback)(void) = *(void (**)(void))entry;

    runtime_state = D_80083160;
    if (callback != 0) {
        callback();
        if ((*(u16 *)((u8 *)entry - 2) & 0x8000) != 0) {
            return;
        }
    }

    func_8003C0C8(entry, context);
    field_value = *(u32 *)(runtime_state + 8) & 0x10;
    if (field_value != 0) {
        field_value = 5;
    } else {
        field_value = 0x10;
    }
    *(u16 *)((u8 *)output + 0xA) = field_value;
}
