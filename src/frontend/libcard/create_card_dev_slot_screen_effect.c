#include "common.h"
#include "shared/object_node.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/card.h"
#include "frontend/libcard/card_chooser.h"

extern const char D_8040086C[];
extern const char D_80400894[];
extern CardSlotScreenEffect D_8040C5C0;
/* Reuse or allocate a devkit effect, initialize its payload, and attach its callback. */
CardSlotScreenEffect *create_card_dev_slot_screen_effect(ObjectNodeHeader *request, s32 mode) {
    CardSlotScreenEffect *effect = &D_8040C5C0;
    CardChooserBody *work = &effect->body;
    if (func_80047FD8(effect) ||
        ((effect = func_8003C714(0, effect, 0x19)) == 0 &&
         (printf_8007C040(D_8040086C, D_80400894, 0x173), exit_8007BEF0(1), 1))) {
        release_devkit_node_handles(&effect->node);
        D_8040C5DE &= 0x7FFF;
        bzero_8007BFE0(work, 0x44);
    }
    set_record_values(work, request, mode);
    effect->node.update_callback = card_dev_create_slot_screen_objects;
    return effect;
}
