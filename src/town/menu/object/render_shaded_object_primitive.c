#include "common.h"
#include "shared/object_flags.h"
#include "town/menu/object.h"
#include "town/menu/motion.h"
#include "town/menu/state.h"
#include "sdk/libgte.h"

typedef struct S_800A1D1C_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x4];
    union { u8 u8; s16 s16; } unk_10;   /* accessed as both */
} S_800A1D1C_1;

typedef struct S_800A1D1C_2 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800A1D1C_2;   /* global_page in render_shaded_object_primitive */

typedef struct DoorProjectionScratch {
    u8 pad_00[0x2C];
    SVECTOR position;
    u8 pad_34[0x64];
    s32 transform_flags;
} DoorProjectionScratch;

/* Update primitive shading and transform object coordinates, or mark it inactive. */
void render_shaded_object_primitive(DoorProjectionChild *object, ObjectPosition *coords, SpriteFrameState *primitive) {
    s32 matrix_index;
    s32 red_scaled;
    s32 green_scaled;
    s32 blue_scaled;
    S_800A1D1C_2 *global_page;
    DoorProjectionScratch *scratch;
    SVECTOR *position;
    MATRIX *matrix;
    DoorTransitionEffect *render_state;

    render_state = object->parent;
    scratch = (DoorProjectionScratch *)0x1F800000;
    if (render_state->finished != 0) {
        NODE_HEADER(object)->flags |= 0x8000;
        global_page = (S_800A1D1C_2 *)0x80080000;
        global_page->unk_14A0 |= 0x8000;
        return;
    }
    object->update(object, coords, primitive);
    if ((object->color_flags & 0xFF) != 0) {
        primitive->color.c.r = render_state->intensity;
    } else {
        red_scaled = render_state->intensity * 3;
        primitive->color.c.r = red_scaled / 4;
    }
    if (((object->color_flags >> 8) & 0xFF) != 0) {
        primitive->color.c.g = render_state->intensity;
    } else {
        green_scaled = render_state->intensity * 3;
        primitive->color.c.g = green_scaled / 4;
    }
    if (((object->color_flags >> 16) & 0xFF) != 0) {
        primitive->color.c.b = render_state->intensity;
    } else {
        blue_scaled = render_state->intensity * 3;
        primitive->color.c.b = blue_scaled / 4;
    }
    scratch->position.vx = object->x;
    scratch->position.vy = object->y;
    scratch->position.vz = object->z;
    matrix_index = object->matrix_index != 0;
    PushMatrix();
    matrix = &render_state->matrices[matrix_index];
    SetRotMatrix(matrix);
    SetTransMatrix(matrix);
    position = &scratch->position;
    RotTransSV(position, position, &scratch->transform_flags);
    PopMatrix();
    coords->x.w.i = scratch->position.vx;
    coords->y.w.i = scratch->position.vy;
    coords->z.w.i = scratch->position.vz;
}
