#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800649A0();                            /* extern */
M2C_UNK func_80064A40();                            /* extern */
M2C_UNK func_80064CF0();                      /* extern */
M2C_UNK func_80064D80();                      /* extern */
M2C_UNK func_80065320();     /* extern */
extern s32 D_800814A0;


typedef struct S_800A1D1C_0_pre {
    u16 unk_00;
} S_800A1D1C_0_pre;   /* the 0x2 bytes before arg0 in func_800A1D1C, addressed as arg0[-1] */

typedef struct S_800A1D1C_0 {
    M2C_UNK (*unk_00)(void *, void *, void *);
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
} S_800A1D1C_0;   /* arg0 in func_800A1D1C */

typedef struct S_800A1D1C_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x4];
    union { u8 u8; s16 s16; } unk_10;   /* accessed as both */
} S_800A1D1C_1;   /* temp_s1 in func_800A1D1C */

typedef struct S_800A1D1C_2 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800A1D1C_2;   /* global_page in func_800A1D1C */

typedef struct S_800A1D1C_3 {
    u8 pad_00[0xC];
    union { u8 u; s8 s; } unk_0C;   /* accessed as both */
    union { u8 u; s8 s; } unk_0D;   /* accessed as both */
    union { u8 u; s8 s; } unk_0E;   /* accessed as both */
} S_800A1D1C_3;   /* arg2_local in func_800A1D1C */

typedef struct S_800A1D1C_4 {
    u8 pad_00[0x2C];
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
} S_800A1D1C_4;   /* scratch in func_800A1D1C */

typedef struct S_800A1D1C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A1D1C_5;   /* arg1 in func_800A1D1C */

/* Update primitive shading and transform object coordinates, or mark it inactive. */
void func_800A1D1C(void *object, S_800A1D1C_5 *coords, void *primitive) {
    s32 matrix_index;
    s32 red_scaled;
    s32 green_scaled;
    s32 blue_scaled;
    u8 *global_page;
    register void *saved_primitive ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *scratch;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *position;
    void *matrix;
    void *render_state;

    render_state = ((S_800A1D1C_0 *)object)->unk_10;
    saved_primitive = primitive;
    scratch = (u8 *)0x1F800000;
    if (((S_800A1D1C_1 *)render_state)->unk_0A != 0) {
        ((S_800A1D1C_0_pre *)object)[-1].unk_00 = (u16) (((S_800A1D1C_0_pre *)object)[-1].unk_00 | 0x8000);
        global_page = (u8 *)0x80080000;
        ASM_KEEP(global_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        ((S_800A1D1C_2 *)global_page)->unk_14A0 |= 0x8000;
        return;
    }
    ASM_KEEP(saved_primitive);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    ((S_800A1D1C_0 *)object)->unk_00(object, coords, saved_primitive);
    if (((S_800A1D1C_0 *)object)->unk_3C != 0) {
        ((S_800A1D1C_3 *)saved_primitive)->unk_0C.u = ((S_800A1D1C_1 *)render_state)->unk_10.u8;
    } else {
        red_scaled = ((S_800A1D1C_1 *)render_state)->unk_10.s16 * 3;
        if (red_scaled < 0) {
            red_scaled += 3;
        }
        ((S_800A1D1C_3 *)saved_primitive)->unk_0C.s = (s8) (red_scaled >> 2);
    }
    if (((S_800A1D1C_0 *)object)->unk_3D != 0) {
        ((S_800A1D1C_3 *)saved_primitive)->unk_0D.u = ((S_800A1D1C_1 *)render_state)->unk_10.u8;
    } else {
        green_scaled = ((S_800A1D1C_1 *)render_state)->unk_10.s16 * 3;
        if (green_scaled < 0) {
            green_scaled += 3;
        }
        ((S_800A1D1C_3 *)saved_primitive)->unk_0D.s = (s8) (green_scaled >> 2);
    }
    if (((S_800A1D1C_0 *)object)->unk_3E != 0) {
        ((S_800A1D1C_3 *)saved_primitive)->unk_0E.u = ((S_800A1D1C_1 *)render_state)->unk_10.u8;
    } else {
        blue_scaled = ((S_800A1D1C_1 *)render_state)->unk_10.s16 * 3;
        if (blue_scaled < 0) {
            blue_scaled += 3;
        }
        ((S_800A1D1C_3 *)saved_primitive)->unk_0E.s = (s8) (blue_scaled >> 2);
    }
    ((S_800A1D1C_4 *)scratch)->unk_2C = ((S_800A1D1C_0 *)object)->unk_24;
    ((S_800A1D1C_4 *)scratch)->unk_2E = ((S_800A1D1C_0 *)object)->unk_28;
    ((S_800A1D1C_4 *)scratch)->unk_30 = ((S_800A1D1C_0 *)object)->unk_2C;
    matrix_index = ((S_800A1D1C_0 *)object)->unk_22 != 0;
    func_800649A0();
    matrix = render_state + ((matrix_index << 5) + 0x14);
    func_80064CF0(matrix);
    func_80064D80(matrix);
    position = scratch + 0x2C;
    func_80065320(position, position, (void *)((u32)scratch | 0x98));
    func_80064A40();
    coords->unk_02 = ((S_800A1D1C_4 *)scratch)->unk_2C;
    coords->unk_06 = ((S_800A1D1C_4 *)scratch)->unk_2E;
    coords->unk_0A = ((S_800A1D1C_4 *)scratch)->unk_30;
}
