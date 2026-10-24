#include "town/person.h"

#include "shared/object_index_slots.h"
extern void func_800C2E84(PersonObject *, s8 *, s32 *);
extern u8 D_800C3C5C[];

/* Select descriptor list +0x14, clear the slot, and set heading 0xC00. */
void reset_person_heading_c00(PersonObject *object, s32 unused, s8 *output) {
    func_800C2E84(object, output, object->descriptor->entries[5]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = D_800C3C5C;
    object->heading = 0xC00;
}
