#include "common.h"
#include "town/scene.h"

typedef struct DevSlot {
    s32 flags;
    s32 unk_04;
} DevSlot;

extern DevSlot D_80700734[][2];

extern void func_80700BD8(s32 code);

/* If the slot's ready bit is set, post code 0x107. */
void post_slot_ready_code(s32 group, s32 slot) {
    if (D_80700734[group][slot].flags & 1) {
        func_80700BD8(0x107);
    }
}
