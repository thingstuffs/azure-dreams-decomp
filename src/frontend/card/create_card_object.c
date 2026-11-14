#include "common.h"
#include "frontend/card/server_imports.h"
#include "frontend/card.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    void (*unk10)(void *object_data, s32 first_value, s32 second_value); /* update callback slot: create_card_object installs update_card_object_and_linked_value */
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
} StructA_8001B428;

extern void (*card_object_callbacks[1])(StructA_8001B428 *object);

/* Creates an object with initialization data, runs its selected initializer, and sets its callback. */
StructA_8001B428 *create_card_object(s32 unused, s32 init_data, s32 init_index) {
    StructA_8001B428 *object;

    object = func_8003C480(0);
    if (object != NULL) {
        object->unk20 = init_data;
        object->unk24 = init_index;
        card_object_callbacks[init_index](object);
        object->unk10 = update_card_object_and_linked_value;
    }
    return object;
}
