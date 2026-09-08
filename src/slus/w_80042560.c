#include "common.h"

typedef struct CallbackSlot {
    s8 type;
    s8 value;
} CallbackSlot;

typedef struct CallbackObject {
    u8 pad_00[0x2C];
    CallbackSlot slots[4];
} CallbackObject;

typedef struct CallbackGlobals {
    u16 flags;
    u8 pad_02[8];
} CallbackGlobals;

extern CallbackGlobals D_80013714;
/* Same object, spelled as the bare 2-byte `flags` field: at -G8 gcc treats this
 * declaration as small data and emits the store as a bare assembler macro, which
 * `as` expands through $at (retail's form for this one site).  The 10-byte
 * declaration above stays large, so the read-modify-write at the top keeps its
 * shared %hi base in $3.  Both `.extern` sizes are emitted; `as` honours the last
 * one printed (the 10-byte one), so the macro is NOT $gp-relative. */
extern u16 D_80013714_flags __asm__("D_80013714");

extern s32 func_80042518(CallbackObject *object, s32 type);
extern void func_800A48F0(CallbackObject *object, s32 type, s32 value);

/* Remove type 0x1B and replay the remaining slots with global flag bit 1 set. */
void func_80042560(CallbackObject *object)
{
    CallbackSlot saved_slots[4];
    s32 initial_type = 0x1B;
    s32 slot_index = 0;
    CallbackGlobals *globals = &D_80013714;
    u16 saved_flags;

    ASM_KEEP(initial_type);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    saved_flags = globals->flags;
    globals->flags = saved_flags | 2;
    func_80042518(object, initial_type);

    for (; slot_index < 4; slot_index++) {
        saved_slots[slot_index] = object->slots[slot_index];
        if (saved_slots[slot_index].type != 0) {
            func_80042518(object, saved_slots[slot_index].type);
        }
    }

    for (slot_index = 0; slot_index < 4; slot_index++) {
        if (saved_slots[slot_index].type != 0) {
            func_800A48F0(object, saved_slots[slot_index].type, saved_slots[slot_index].value);
        }
    }

    D_80013714_flags = saved_flags;
}
