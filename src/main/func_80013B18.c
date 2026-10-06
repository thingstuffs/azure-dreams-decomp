#include "common.h"

typedef struct Record13B18 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} Record13B18;   /* 12-byte record passed to func_8004CBFC */

typedef struct Object13B18 {
    s32 unk_00;
    Record13B18 records[2];
    u8 pad_1C[0x4C];
    s32 *slots[2];
} Object13B18;   /* object in func_80026B18 */

extern void func_800269B4(u8 *state);
extern void func_8004CBFC(void *, s32, s32 *);
extern u8 D_80027E68[];

/* Updates or clears active records, then refreshes the object if any were active. */
void func_80026B18(Object13B18 *object, s32 *enable_flags, s32 *active_flags)
{
    s32 *slot_value;
    s32 slot_index;
    s32 updated;

    updated = 0;
    for (slot_index = 0; slot_index < 2; slot_index++) {
        if (active_flags[slot_index] != 0) {
            slot_value = object->slots[slot_index];
            updated = 1;
            if (enable_flags[slot_index] != 0) {
                func_8004CBFC(&object->records[slot_index], (s32)D_80027E68, slot_value);
            } else {
                *slot_value = 0;
                object->records[slot_index].unk_04 = 0;
            }
        }
    }
    if (updated != 0) {
        func_800269B4(object);
    }
}
