#include "shared/object_node.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/card/load.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_imports.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    ObjectNodeHeader node;
    void *background;
    void *information;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
} StructA_8002001C;


/* Allocates and initializes an object and installs its callback. */
StructA_8002001C *card_dev_create_load_screen(s32 init_value, s32 config_value) {
    StructA_8002001C *object;

    object = allocate_card_object_8003C480(0);
    if (object != NULL) {
        object->unk44 = config_value;
        card_dev_load_forward_object_value( (NODE_BODY(&object->node)), init_value);
        card_dev_run_temp_slot_operation();
        card_dev_cache_slot_summary();
        object->background = init_card_background_object(&object->node, 0);
        object->information = init_card_info_object(&object->node, object->unk4C);
        object->unk28 = init_card_sme_object(&object->node);
        object->unk48 = 0;
        object->node.update_callback = card_dev_build_load_slot_windows;
    }
    return object;
}
