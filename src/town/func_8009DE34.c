#include "common.h"

extern void func_8008F664(void *, void *);
extern void func_8009B2C4(void *, void *, void *, void *);
extern void func_8009BFC0(void *, void *, void *, void *);

extern u8 D_8009B454[];
extern u8 D_8009B594[];
extern u8 D_8009BDC0[];
extern u8 D_800CFCB4[];

/* Runs handlers when any slot flag is set and copies the stored value for eligible states. */
void func_8009B594(void *state_owner, void *update_target, void *update_context, void *output) {
    s32 slot;
    void *current_state;
    s32 *stored_value;

    for (slot = 0; slot < 6; slot++) {
        u8 *slot_flags = D_800CFCB4 + slot;

        if (slot_flags[0x3A] != 0 || slot_flags[0x40] != 0) {
            break;
        }
    }
    if (slot < 6) {
        if (*(u8 *)((u8 *)update_target + 0x3B) == 0) {
            func_8009BFC0(state_owner, update_target, update_context, output);
        }
        func_8008F664(update_target, update_context);
        func_8009B2C4(state_owner, update_target, update_context, output);
    }
    current_state = *(void **)((u8 *)state_owner + 0x50);
    if (current_state != D_8009B454 && current_state != D_8009B594 && current_state != D_8009BDC0) {
        stored_value = *(s32 **)((u8 *)state_owner + 0x7C);
        if (stored_value != 0) {
            *(s32 *)((u8 *)output + 8) = *stored_value;
        }
    }
}
