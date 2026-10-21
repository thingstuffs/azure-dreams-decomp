#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"

typedef s32 M2C_UNK;

typedef struct S_800243E0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800243E0_0;

   /* arg0 in create_type_212_effect_object */

extern M2C_UNK select_record_entry_and_value();
extern s32 register_node();
extern s32 D_80024374;

/* Creates a type 0x212 object, initializes its appearance, and copies the supplied components. */
void *create_type_212_effect_object(MovingPosition *source) {
    SpriteFrameState *appearance;
    S_800243E0_0 *object;
    MovingPosition *components;
    void *result; /* MATCH: Keep the merged return value in v0 for the shared epilogue. */

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        object->unk_10 = &D_80024374;
        appearance = object->unk_0C;
        appearance->color.c.b = 0x80;
        appearance->color.c.g = 0x80;
        appearance->color.c.r = 0x80;
        select_record_entry_and_value(appearance, effect_sprite_sources, 0);
        appearance->scale_y = 0x2000;
        appearance->scale_x = 0x2000;
        register_node(object, project_sprite_chain);
        components = object->unk_08;
        components->unk_02 = source->unk_02;
        components->unk_06 = source->unk_06;
        components->unk_0A = source->unk_0A;
        result = object;
        return result;
    } else {
        result = 0;
        return result;
    }
}
