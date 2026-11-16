#include "common.h"
#include "shared/object_node.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/card.h"

extern u8 D_8040086C[], D_80400894[];
typedef CardSlotScreenEffect Effect;
extern void release_devkit_node_handles(Effect *);
extern void set_record_values(void *, void *, void *);
extern CardSlotScreenEffect D_8040C5C0;
/* Reuse or allocate a devkit effect, initialize its payload, and attach its callback. */
CardSlotScreenEffect *create_card_dev_slot_screen_effect(void *first, void *second) {
    CardSlotScreenEffect *effect = &D_8040C5C0;
    void *work = NODE_BODY(effect);
    if (func_80047FD8(effect) ||
        ((effect = func_8003C714(0, effect, 0x19)) == 0 &&
         (func_8007C040(D_8040086C, D_80400894, 0x173), func_8007BEF0(1), 1))) {
        release_devkit_node_handles(effect);
        D_8040C5DE &= 0x7FFF;
        func_8007BFE0(work, 0x44);
    }
    set_record_values(work, first, second);
    effect->callback = card_dev_create_slot_screen_objects;
    return effect;
}
