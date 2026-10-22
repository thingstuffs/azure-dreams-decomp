#include "common.h"
#include "shared/object_node.h"
#ifndef NULL
#define NULL 0
#endif
extern void *create_item_menu_child_object(s32);
extern s32 D_800AFD00[4];

/* Create an object and initialize its handler table and state value. */
void *create_item_menu_handler_object(s32 object_id) {
    ObjectNodeHeader *object = create_item_menu_child_object(object_id);
    if (object != NULL) {
        void *state = *(void **)((u8 *)object + 0xBC);
        object->unk_10 = D_800AFD00;
        *(s16 *)((u8 *)state + 6) = 0x1000;
    }
    return object;
}
