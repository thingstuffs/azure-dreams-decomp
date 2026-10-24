#include "town/person.h"

#include "shared/object_index_slots.h"
extern void func_800C2E84(PersonObject *, s8 *, s32 *);
extern u8 D_800C3B7C[];

/* Select descriptor list +0x0C, clear its slot, and start the timed handler. */
void reset_person_descriptor_entries(PersonObject *object, s32 unused, s8 *output) {
    func_800C2E84(object, output, object->descriptor->entries[3]);
    object_index_slots[object->slot].unk_00 = 0;
    object->handler = D_800C3B7C;
    object->timer = 0x15;
}
