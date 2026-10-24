#include "town/person.h"

extern void func_800C2E84(PersonObject *, s8 *, s32 *);

/* Select descriptor list +0x24, then forward all three callback inputs. */
void apply_person_descriptor_tail(PersonObject *object, ObjectPosition *position, s8 *output) {
    func_800C2E84(object, output, object->descriptor->entries[9]);
    start_person_target_move(object, position, output);
}
