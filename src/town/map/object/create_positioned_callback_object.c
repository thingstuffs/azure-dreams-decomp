#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "engine/graphics.h"
#include "engine/node.h"

typedef struct {
    u16 field_0x00;
    u16 field_0x02;
} Input;

typedef struct {
    u8 pad_0x00[2];
    u16 field_0x02;
    u8 pad_0x04[2];
    u16 field_0x06;
} Vec;

typedef struct {
    u8 pad_0x00[8];
    s32 field_0x08;
    s32 field_0x0C;
    s16 field_0x10;
    u8 pad_0x12[0xA];
    s16 field_0x1C;
    s16 field_0x1E;
} Data;

typedef struct {
    u8 pad_0x00[8];
    Vec *vec;
    Data *data;
    s32 field_0x10;
    u8 pad_0x14[0xE];
    s16 field_0x22;
} Object;

struct ObjectPosition;
struct SpriteFrameState;

/* Create an object at the supplied position and initialize its callback and display data. */
void create_positioned_callback_object(Input *position, s32 object_value, s32 data_value)
{
    ObjectNodeHeader *object;
    SpriteFrameState *field_base;
    u8 *sub;
    s32 neutral_color;

    object = allocate_flagged_object_node(0x136);
    if (object != 0) {
        sub = (u8 *)object + 0x20;
        object->update_callback = object_value;
        (*(Vec * *)&object->position)->field_0x02 = position->field_0x00;
        (*(Vec * *)&object->position)->field_0x06 = position->field_0x02;
        register_node(object, (void *)draw_linked_sprites);
        neutral_color = 0x808080;
        *(s16 *)(sub + 2) = 0x1E;
        field_base = object->sprite;
        field_base->scale_y = 0x1000;
        field_base->scale_x = 0x1000;
        field_base->source = data_value;
        field_base->color.word = neutral_color;
        field_base->tpage_abr = 0x60;
    }
}
