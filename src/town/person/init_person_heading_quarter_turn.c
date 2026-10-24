#include "town/person.h"

extern void func_800C2E84(PersonObject *, s8 *, s32 *);
extern s32 D_800D72AC[];
extern u8 D_800CE4C4[];

/* Select the fixed entry list and install the callback's initial state. */
void init_person_heading_quarter_turn(PersonObject *object, s32 unused, s8 *output) {
    func_800C2E84(object, output, D_800D72AC);
    object->handler = D_800CE4C4;
    object->heading = 0x400;
}
