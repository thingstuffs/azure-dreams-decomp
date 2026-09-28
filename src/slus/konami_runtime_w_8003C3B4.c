#include "common.h"
#include "shared/game_work.h"

#include "common.h"

extern void func_8003C0C8(void *arg0, void *arg1);

/* Runs the entry callback, then processes the entry and sets the output field unless flagged to stop. */
void func_8003C3B4(void *entry, void *output, void *context) {
    GameWork *runtime_state;
    s32 field_value;
    void (*callback)(void) = *(void (**)(void))entry;

    runtime_state = &gameWork;
    if (callback != 0) {
        callback();
        if ((*(u16 *)((u8 *)entry - 2) & 0x8000) != 0) {
            return;
        }
    }

    func_8003C0C8(entry, context);
    field_value = ((u32)runtime_state->unk_008) & 0x10;
    if (field_value != 0) {
        field_value = 5;
    } else {
        field_value = 0x10;
    }
    *(u16 *)((u8 *)output + 0xA) = field_value;
}
