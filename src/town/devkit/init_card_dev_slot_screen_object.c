#include "common.h"
#include "frontend/libcard/card_chooser.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "town/devkit.h"
#include "frontend/card/server_imports.h"


extern CardSlotScreenEffect D_8040C5C0;
extern u16 D_8040C5DE_LOAD[5];
extern u16 D_8040C5DE_STORE[5];
extern u8 D_8040086C[];
extern u8 D_80400894[];

/* Creates or resets the town object, initializes its state, and installs its callback. */
void *init_card_dev_slot_screen_object(ObjectNodeHeader *request, s32 mode) {
    CardSlotScreenEffect *object;
    struct CardChooserBody *state;

    object = &D_8040C5C0;
    state = &object->body;
    if (func_80047FD8(object) != 0 || ((object = func_8003C714(0, &D_8040C5C0, 0x19)) == 0 && (printf_8007C040(D_8040086C, D_80400894, 0x173), exit_8007BEF0(1), 1))) {
        release_devkit_node_handles(&object->node);
        D_8040C5DE_STORE[0] = (u16) (D_8040C5DE_LOAD[0] & 0x7FFF);
        bzero_8007BFE0(state, 0x44);
    }
    set_record_values(state, request, mode);
    object->node.update_callback = card_dev_create_slot_screen_objects;
    return object;
}
