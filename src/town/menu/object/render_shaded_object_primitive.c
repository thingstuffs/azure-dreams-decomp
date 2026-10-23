#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
void PushMatrix(void);                            /* extern */
void PopMatrix(void);                            /* extern */
void SetRotMatrix(void *);                      /* extern */
void SetTransMatrix(void *);                      /* extern */
void func_80065320(void *, void *, void *);     /* extern */


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

typedef struct S_800A1D1C_3 {
    u8 pad_00[0xC];
    union { u8 u; s8 s; } unk_0C;   /* accessed as both */
    union { u8 u; s8 s; } unk_0D;   /* accessed as both */
    union { u8 u; s8 s; } unk_0E;   /* accessed as both */
} S_800A1D1C_3;   /* arg2_local in render_shaded_object_primitive */

typedef struct S_800A1D1C_4 {
    u8 pad_00[0x2C];
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
} S_800A1D1C_4;   /* scratch in render_shaded_object_primitive */

   /* arg1 in render_shaded_object_primitive */

/* Update primitive shading and transform object coordinates, or mark it inactive. */
void render_shaded_object_primitive(void *object, MovingPosition *coords, void *primitive) {
    s32 matrix_index;
    s32 red_scaled;
    s32 green_scaled;
    s32 blue_scaled;
    u8 *global_page;
    u8 *scratch;
    void *position;
    void *matrix;
    void *render_state;

    render_state = ((S_800A1D1C_0 *)object)->unk_10;
    scratch = (u8 *)0x1F800000;
    if (((S_800A1D1C_1 *)render_state)->unk_0A != 0) {
        ((ObjectRetirementFlags *)object)[-1].flags = (u16) (((ObjectRetirementFlags *)object)[-1].flags | 0x8000);
        global_page = (u8 *)0x80080000;
        ((S_800A1D1C_2 *)global_page)->unk_14A0 |= 0x8000;
        return;
    }
    ((S_800A1D1C_0 *)object)->unk_00(object, coords, primitive);
    if (((S_800A1D1C_0 *)object)->unk_3C != 0) {
        ((S_800A1D1C_3 *)primitive)->unk_0C.u = ((S_800A1D1C_1 *)render_state)->unk_10.u8;
    } else {
        red_scaled = ((S_800A1D1C_1 *)render_state)->unk_10.s16 * 3;
        ((S_800A1D1C_3 *)primitive)->unk_0C.s = (s8) (red_scaled / 4);
    }
    if (((S_800A1D1C_0 *)object)->unk_3D != 0) {
        ((S_800A1D1C_3 *)primitive)->unk_0D.u = ((S_800A1D1C_1 *)render_state)->unk_10.u8;
    } else {
        green_scaled = ((S_800A1D1C_1 *)render_state)->unk_10.s16 * 3;
        ((S_800A1D1C_3 *)primitive)->unk_0D.s = (s8) (green_scaled / 4);
    }
    if (((S_800A1D1C_0 *)object)->unk_3E != 0) {
        ((S_800A1D1C_3 *)primitive)->unk_0E.u = ((S_800A1D1C_1 *)render_state)->unk_10.u8;
    } else {
        blue_scaled = ((S_800A1D1C_1 *)render_state)->unk_10.s16 * 3;
        ((S_800A1D1C_3 *)primitive)->unk_0E.s = (s8) (blue_scaled / 4);
    }
    ((S_800A1D1C_4 *)scratch)->unk_2C = ((S_800A1D1C_0 *)object)->unk_24;
    ((S_800A1D1C_4 *)scratch)->unk_2E = ((S_800A1D1C_0 *)object)->unk_28;
    ((S_800A1D1C_4 *)scratch)->unk_30 = ((S_800A1D1C_0 *)object)->unk_2C;
    matrix_index = ((S_800A1D1C_0 *)object)->unk_22 != 0;
    PushMatrix();
    matrix = render_state + ((matrix_index << 5) + 0x14);
    SetRotMatrix(matrix);
    SetTransMatrix(matrix);
    position = scratch + 0x2C;
    func_80065320(position, position, (void *)((u32)scratch | 0x98));
    PopMatrix();
    coords->x = ((S_800A1D1C_4 *)scratch)->unk_2C;
    coords->y = ((S_800A1D1C_4 *)scratch)->unk_2E;
    coords->z = ((S_800A1D1C_4 *)scratch)->unk_30;
}
