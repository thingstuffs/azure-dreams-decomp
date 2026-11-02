#include "engine/effect.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "engine/node.h"
#include "slus.h"
#include "engine/graphics.h"

/* struct Elem / struct Dst as established in src/code.c for func_8003DB94 */
struct Elem {
    unsigned char b0;
    unsigned char pad1;
    unsigned char pad2;
    unsigned char pad3;
    int f4;
};

struct Dst {
    struct Elem *f0;
    unsigned char f4;
    unsigned char f5;
    unsigned char pad6;
    unsigned char pad7;
    int f8;
    int fc;
    int f10;
    unsigned short f14;
};

struct ObjectPosition;
struct SpriteFrameState;

/* Sized >8B to force %hi/%lo (not $gp) addressing, matching retail's lui/addiu. */
extern struct Elem arc_motion_sprite_source[2];

/* Initializes the object callbacks, sub-object state, linked record, and fixed vector. */
void scene_initialize_arc_motion_sprite(CdCueEffectNode *object, struct Controller *sub_object)
{
    SpriteFrameState *record;
    ObjectPosition *vector;
    char *sub_fields = (char *)&object->body;

    object->header.update_callback = update_staged_motion_effect;
    object->body.owner.controller = sub_object;
    ((short *)sub_fields)[2] = 0;
    ((short *)sub_fields)[3] = 0;

    record = object->header.sprite;
    record->color.word = 0x808080;
    select_record_entry_and_value(record, arc_motion_sprite_source, 0);

    record->scale_y = 0x1000;
    record->scale_x = 0x1000;
    register_node(&object->header, draw_linked_sprites);

    vector = object->header.position;
    vector->x.v = 0x1C00000;
    vector->y.v = 0xC00000;
    vector->z.v = 0x800000;
}
