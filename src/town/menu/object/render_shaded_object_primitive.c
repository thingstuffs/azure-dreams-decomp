#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "town/menu/object.h"
#include "sdk/libgte.h"


   /* the 0x2 bytes before arg0 in render_shaded_object_primitive, addressed as arg0[-1] */

typedef struct S_800A1D1C_0 {
    s32 (*unk_00)(void *, void *, void *);
    u8 pad_04[0xC];
    void * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
    u16 unk_24;
    u8 pad_26[0x2];
    u16 unk_28;
    u8 pad_2A[0x2];
    u16 unk_2C;
    u8 pad_2E[0xE];
    u8 unk_3C;
    u8 unk_3D;
    u8 unk_3E;
} S_800A1D1C_0;   /* arg0 in render_shaded_object_primitive */

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


typedef struct S_800A1D1C_4 {
    u8 pad_00[0x2C];
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
} S_800A1D1C_4;   /* scratch in render_shaded_object_primitive */

   /* arg1 in render_shaded_object_primitive */

/* Update primitive shading and transform object coordinates, or mark it inactive. */
void render_shaded_object_primitive(S_800A1D1C_0 *object, ObjectPosition *coords, SpriteFrameState *primitive) {
    s32 matrix_index;
    s32 red_scaled;
    s32 green_scaled;
    s32 blue_scaled;
    S_800A1D1C_2 *global_page;
    S_800A1D1C_4 *scratch;
    void *position;
    void *matrix;
    S_800A1D1C_1 *render_state;

    render_state = object->unk_10;
    scratch = (S_800A1D1C_4 *)0x1F800000;
    if (render_state->unk_0A != 0) {
        NODE_HEADER(object)->flags = (u16) (NODE_HEADER(object)->flags | 0x8000);
        global_page = (S_800A1D1C_2 *)0x80080000;
        global_page->unk_14A0 |= 0x8000;
        return;
    }
    object->unk_00(object, coords, primitive);
    if (object->unk_3C != 0) {
        primitive->color.c.r = render_state->unk_10.u8;
    } else {
        red_scaled = render_state->unk_10.s16 * 3;
        primitive->color.c.r = (s8) (red_scaled / 4);
    }
    if (object->unk_3D != 0) {
        primitive->color.c.g = render_state->unk_10.u8;
    } else {
        green_scaled = render_state->unk_10.s16 * 3;
        primitive->color.c.g = (s8) (green_scaled / 4);
    }
    if (object->unk_3E != 0) {
        primitive->color.c.b = render_state->unk_10.u8;
    } else {
        blue_scaled = render_state->unk_10.s16 * 3;
        primitive->color.c.b = (s8) (blue_scaled / 4);
    }
    scratch->unk_2C = object->unk_24;
    scratch->unk_2E = object->unk_28;
    scratch->unk_30 = object->unk_2C;
    matrix_index = object->unk_22 != 0;
    PushMatrix();
    matrix = (u8 *)render_state + ((matrix_index << 5) + 0x14);
    SetRotMatrix(matrix);
    SetTransMatrix(matrix);
    position = &scratch->unk_2C;
    RotTransSV(position, position, (void *)((u32)scratch | 0x98));
    PopMatrix();
    coords->x.w.i = scratch->unk_2C;
    coords->y.w.i = scratch->unk_2E;
    coords->z.w.i = scratch->unk_30;
}
