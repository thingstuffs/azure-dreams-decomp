#include "common.h"
#include "shared/object_node.h"
#include "shared/dungeon_effect_views.h"

typedef struct {
    u8 pad_0[8];
    EffectInitialState *data;
    u8 pad_C[4];
    void (*callback_10)(void);
    u8 pad_14[12];
    void (*callback_20)(void);
} AllocatedObject;

extern void *allocate_list_node(s32 kind, void *owner);
extern void invoke_menu_motion_handler(void);
extern void initialize_animated_menu_ring(void);

/* Allocate an object, copy its initial data, and set its callbacks. */
AllocatedObject *allocate_object_with_callbacks(EffectInitialState *source)
{
    AllocatedObject *obj;
    EffectInitialState *data;

    obj = allocate_list_node(0x10, ((u8 *)(&scene_object_list_anchor)));
    if (obj == 0) {
        return 0;
    }

    data = obj->data;
    data->unk_00 = source->unk_00;
    data->unk_04 = source->unk_04;
    data->unk_08 = source->unk_08;
    obj->callback_10 = invoke_menu_motion_handler;
    obj->callback_20 = initialize_animated_menu_ring;
    return obj;
}
