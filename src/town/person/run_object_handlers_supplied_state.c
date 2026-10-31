#include "common.h"
#include "town/person.h"
#include "town/person/object.h"
#include "town/person/state.h"

typedef struct S_800C88AC_0 {
    u8 pad_00[0x54];
    void (*unk_54)(s32,  s32,  s32);
} S_800C88AC_0;   /* arg0 in func_800C88AC */
/* Call func_800C4804 and set the object pointer to run_object_handlers_supplied_state. */
void initialize_object_with_supplied_state_handlers(S_800C88AC_0 *object, s32 param_1, SpriteFrameState *param_2) {
    func_800C4804(object, param_1, param_2);
    object->unk_54 = &run_object_handlers_supplied_state;
}
