#include "common.h"

typedef struct S_80025398_0 {
    union { s16 s; volatile u16 u; u16 p; } unk_00;   /* accessed as both */
    s16 unk_02;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0x4];
    s16 unk_0A;
    u8 pad_0C[0x28];
    void * unk_34;
    u8 pad_38[0x60];
    u16 unk_98;
    volatile s16 unk_9A;
} S_80025398_0;   /* arg0 in func_80025398 */

typedef struct S_80025398_1 {
    u8 pad_00[0xC];
    union { s8 s; volatile s8 u; } unk_0C;   /* accessed as both */
    union { s8 s; volatile s8 u; } unk_0D;   /* accessed as both */
    union { s8 s; volatile s8 u; } unk_0E;   /* accessed as both */
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    union { u16 s; volatile u16 u; } unk_1C;   /* accessed as both */
    union { u16 s; volatile u16 u; } unk_1E;   /* accessed as both */
} S_80025398_1;   /* out in func_80025398 */

typedef struct S_80025398_2 {
    u8 pad_00[0x38];
    s8 unk_38;
} S_80025398_2;   /* cursor in func_80025398 */



typedef struct PackedVector {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} PackedVector __attribute__((packed));

typedef struct Pair16 {
    s16 x;
    s16 y;
} Pair16;

extern PackedVector D_80024004;
extern s16 D_800266BC[5];
extern s32 D_800814A0;

extern void func_80024CD4();

/* Update the effect's fade and rotation, draw it, and flag completion at its final frame. */
void func_80025398(void *effect, void *unused, void *primitive)
{
    PackedVector source;
    register PackedVector *source_ptr ASM_REG("$6");
    PackedVector *render_source;
    Pair16 *derived_ptr;
    u32 source_page;
    register void *output ASM_REG("$7") = primitive;
    Pair16 derived;
    s32 frame;
    s32 peak_frame;
    s32 end_frame;
    s32 state;
    s32 next_state;
    s16 next_frame;
    s32 fade_in;
    s32 fade_out;
    s32 shade_index;
    s32 one;
    u16 angle;
    u16 next_angle;
    s32 vertex_x;
    s32 vertex_y;
    s32 fill_shade;
    void *shade_cursor;

    source_page = 0x80020000;
    ASM_KEEP(source_page);
    source_ptr = (PackedVector *)(source_page + 0x4004);
    ASM_KEEP(source_ptr);
    source = *source_ptr;
    ASM_KEEP(source_page);
    frame = ((S_80025398_0 *)effect)->unk_04.s;
    peak_frame = ((S_80025398_0 *)effect)->unk_0A;
    D_800266BC[0] = 1;

    if (frame < peak_frame) {
        fade_in = (frame << 7) / peak_frame;
        ((S_80025398_1 *)output)->unk_1C.s += 0x50;
        ((S_80025398_1 *)output)->unk_1E.s += 0x50;
        ((S_80025398_1 *)output)->unk_0E.s = fade_in;
        ((S_80025398_1 *)output)->unk_0D.s = fade_in;
        ((S_80025398_1 *)output)->unk_0C.s = fade_in;
    } else {
        end_frame = ((S_80025398_0 *)effect)->unk_02;
        fade_out = ((end_frame - frame) << 7) / (end_frame - peak_frame);
        vertex_x = ((S_80025398_1 *)output)->unk_1C.u;
        vertex_y = ((S_80025398_1 *)output)->unk_1E.u;
        vertex_x += 0x50;
        vertex_y += 0x50;
        ((S_80025398_1 *)output)->unk_1C.s = vertex_x;
        ((S_80025398_1 *)output)->unk_1E.s = vertex_y;
        ASM_KEEP(vertex_x);
        ((S_80025398_1 *)output)->unk_0E.u = fade_out;
        ((S_80025398_1 *)output)->unk_0D.u = fade_out;
        ((S_80025398_1 *)output)->unk_0C.u = fade_out;
    }

    angle = ((S_80025398_0 *)effect)->unk_98;
    next_angle = angle - 0x28;
    ((S_80025398_0 *)effect)->unk_98 = next_angle;
    if ((s16)next_angle < 0) {
        ((S_80025398_0 *)effect)->unk_98 = angle + 0xFD8;
    }

    shade_index = 0x5F;
    if (((S_80025398_0 *)effect)->unk_04.s < 0x32) {
        fill_shade = 0x46;
        shade_cursor = (u8 *)effect + 0x5F;
        do {
            ((S_80025398_2 *)shade_cursor)->unk_38 = fill_shade;
            shade_index--;
            shade_cursor = (u8 *)shade_cursor - 1;
        } while (shade_index >= 0);
    }

    state = ((S_80025398_0 *)effect)->unk_00.s;
    ASM_KEEP(state);
    ((S_80025398_0 *)effect)->unk_9A = 0x64;
    next_state = ((S_80025398_0 *)effect)->unk_00.u + 1;
    if (state != 0) {
        render_source = &source;
        if (state != 1) {
            ASM_SCHED_BARRIER();
            return;
        }
    } else {
        ((S_80025398_0 *)effect)->unk_00.p = next_state;
        ((S_80025398_1 *)output)->unk_14 &= 0xFF7F;
        ASM_SCHED_BARRIER();
        render_source = &source;
    }

    derived_ptr = &derived;
    derived.x = source.x + ((s16)source.z >> 1);
    one = 1;
    derived.y = source.y + 0x3C;
    func_80024CD4(effect, ((S_80025398_0 *)effect)->unk_34, render_source, derived_ptr, one, one);

    next_frame = ((S_80025398_0 *)effect)->unk_04.u + 1;
    ((S_80025398_0 *)effect)->unk_04.u = next_frame;
    if (next_frame == ((S_80025398_0 *)effect)->unk_02) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
