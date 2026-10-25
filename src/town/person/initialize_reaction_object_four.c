#include "town/person.h"
#include "town/person/mother_event_motion_g00670.h"
extern s32 D_800D5FA0[];
extern void func_800C7A00(void);
extern s32 D_800D64F0[];
extern void func_800C9A98(void);

void initialize_reaction_object_four(PersonSetupState *object, void *unused, void *context) {
    initialize_object_entries(object, context, D_800D64F0);
    object->callback = func_800C9A98;
    object->timer = 4;
}
