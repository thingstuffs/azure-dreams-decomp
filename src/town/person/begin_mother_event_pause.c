#include "town/person.h"
#include "town/person/mother_event_motion_g00670.h"
extern s32 D_800D5FA0[];
extern s32 D_800D64F0[];
extern void func_800C9A98(void);

void begin_mother_event_pause(PersonSetupState *object, void *unused, void *context) {
    initialize_object_entries(object, context, D_800D5FA0);
    object->callback = func_800C7A00;
    mother_event_ticks.value = 21;
}
