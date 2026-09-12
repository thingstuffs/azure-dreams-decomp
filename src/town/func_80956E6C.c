#include "common.h"

typedef struct S_80956E6C_0 {
    u8 pad_00[0x8];
    union { void * p32; s16 s16; } unk_08;   /* accessed as both */
    void * unk_0C;
    void * unk_10;
} S_80956E6C_0;   /* object in func_80956E6C */

typedef struct S_80956E6C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80956E6C_1;   /* position in func_80956E6C */

typedef struct S_80956E6C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80956E6C_2;   /* position2 in func_80956E6C */

typedef struct S_80956E6C_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_80956E6C_3;   /* primitive in func_80956E6C */

typedef struct S_80956E6C_4 {
    u8 pad_00[0x48];
    u16 unk_48;
    u16 unk_4A;
} S_80956E6C_4;   /* arg2 in func_80956E6C */



typedef struct Palette {
    s32 value[5];
} Palette;

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);

extern Palette D_800201B4;
extern u8 D_80023FA8[];
extern u8 D_80044BB0[];

/* Create an object with a signed position, selected palette, and supplied settings. */
void func_80956E6C(s32 signed_position, s32 palette_index, S_80956E6C_4 *settings, s32 field_28_value)
{
    Palette palette;
    s32 *palette_entries;
    register u16 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u32 tint_color;
    s32 palette_value;
    void *object;
    S_80956E6C_1 *position;
    S_80956E6C_2 *position_aux;
    S_80956E6C_3 *primitive;

    palette = D_800201B4;
    object = func_8003FC64(0x15);
    if (object != 0) {
        palette_entries = palette.value;
        ((S_80956E6C_0 *)object)->unk_10 = D_80023FA8;
        func_8004491C(object, D_80044BB0);

        primitive = ((S_80956E6C_0 *)object)->unk_0C;
        value = signed_position;
        position = ((S_80956E6C_0 *)object)->unk_08.p32;
        if (signed_position < 0) {
            ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            value = -value;
            position->unk_02 = value;
        } else {
            position->unk_02 = value;
        }
        value = 0x80;
        position_aux = ((S_80956E6C_0 *)object)->unk_08.p32;
        position_aux->unk_06 = value;

        primitive->unk_10 = 0x60;
        primitive->unk_14 |= 0xC;

        value = settings->unk_48;
        object = (u8 *)object + 0x20;
        if (signed_position < 0) {
            value = -value;
        }
        primitive->unk_1A = value;
        ((S_80956E6C_0 *)object)->unk_08.s16 = field_28_value;

        value = settings->unk_4A;
        tint_color = 0xC0C0C0;
        primitive->unk_1E = value;
        primitive->unk_1C = value;
        palette_value = palette_entries[palette_index];
        primitive->unk_04 = 0;
        primitive->unk_05 = 0;
        primitive->unk_0C = tint_color;
        primitive->unk_08 = palette_value;
    }
}

/* MECHANISM: A 20-byte Palette local produces the 0x48 frame and five-word stack copy.
   Guarded s1 table-base and v0 value roles reproduce the saved set and temporary coloring.
   Split position, palette-value, and tint_color live ranges place both load-delay fillers exactly. */
