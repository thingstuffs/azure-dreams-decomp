#include "shared/entity.h"
#include "engine/graphics.h"
#include "shared/object_node.h"
#include "shared/position_views.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

typedef struct S_80956E6C_0 {
    u8 pad_00[0x8];
    union { void * p32; s16 s16; } unk_08;   /* accessed as both */
    void * unk_0C;
    void * unk_10;
} S_80956E6C_0;   /* object in create_paletted_position_object */

typedef struct S_80956E6C_4 {
    u8 pad_00[0x48];
    u16 unk_48;
    u16 unk_4A;
} S_80956E6C_4;   /* arg2 in create_paletted_position_object */

typedef struct Palette {
    s32 value[5];
} Palette;

extern void register_node(void *, void *);

extern Palette D_800201B4;
extern u8 D_80023FA8[];

/* Create an object with a signed position, selected palette, and supplied settings. */
void create_paletted_position_object(s32 signed_position, s32 palette_index, S_80956E6C_4 *settings, s32 field_28_value)
{
    Palette palette;
    s32 *palette_entries;
    s32 value;
    s32 negative;
    u32 tint_color;
    s32 palette_value;
    ObjectNodeHeader *object;
    ObjectPosition *position;
    u32 aux_value;
    SpriteFrameState *primitive;

    palette = D_800201B4;
    object = allocate_flagged_object_node(0x15);
    if (object != 0) {
        palette_entries = palette.value;
        object->update_callback = D_80023FA8;
        register_node(object, draw_linked_sprites);

        primitive = object->sprite;
        negative = signed_position < 0;
        value = signed_position;
        position = object->position;
        if (negative) {
            value = -value;
            position->x.w.i = value;
        } else {
            position->x.w.i = value;
        }
        value = 0x80;
        aux_value = (u32)object->position;
        ((SignedPositionView *)aux_value)->y = value;

        aux_value = 0x60;
        primitive->tpage_abr = aux_value;
        primitive->flags |= 0xC;

        value = settings->unk_48;
        object = (u8 *)object + 0x20;
        if (signed_position < 0) {
            value = -value;
        }
        primitive->angle_z = value;
        ((S_80956E6C_0 *)object)->unk_08.s16 = field_28_value;

        palette_value = settings->unk_4A;
        tint_color = 0xC0C0C0;
        primitive->scale_y = palette_value;
        primitive->scale_x = palette_value;
        palette_value = palette_entries[palette_index];
        primitive->unk_04 = 0;
        primitive->frame_ticks = 0;
        primitive->color.word = tint_color;
        primitive->source = palette_value;
    }
}
