#include "common.h"

typedef struct S_81876014_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x36];
    void * unk_44;
    void * unk_48;
    void * unk_4C;
    u16 unk_50;
    s16 unk_52;
    u16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    s16 unk_64;
    s16 unk_66;
} S_81876014_0;   /* arg0 in func_81876014 */

typedef struct S_81876014_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x90];
    s16 unk_9C;
} S_81876014_1;   /* temp_s3 in func_81876014 */

typedef struct S_81876014_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_81876014_2;   /* arg1 in func_81876014 */

typedef struct S_81876014_3 {
    s32 unk_00;
} S_81876014_3;   /* temp_v1_data in func_81876014 */

typedef struct S_81876014_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_81876014_4;   /* arg2 in func_81876014 */

typedef struct S_81876014_5 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_81876014_5;   /* ((S_81876014_0 *)arg0)->unk_44 in func_81876014 */

typedef struct S_81876014_6 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_81876014_6;   /* ((S_81876014_0 *)arg0)->unk_48 in func_81876014 */



extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s16 D_80026664;
extern s32 D_800814A0;

/* Update the effect quad, copy its position and color, and flag completion based on owner state. */
void func_81876014(void *effect, void *position_out, void *color_out) {
    s16 vertex_coord;
    register s16 y_third ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 y_fourth ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u16 x_edge;
    register u16 x_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s16 z_third ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *position;
    register s32 y_offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u16 z_fourth;
    s16 next_angle;
    s32 y_factor;
    s32 y_product;
    u16 angle;
    void *owner;

    owner = ((S_81876014_0 *)effect)->unk_4C;
    D_80026664 = 1;
    if (((S_81876014_1 *)owner)->unk_9C == 0x37) {
        ((S_81876014_0 *)effect)->unk_50 =
            (u16)((((S_81876014_0 *)effect)->unk_0A *
                   func_80064584(((S_81876014_0 *)effect)->unk_0C)) >> 12);
        y_factor = func_800644B8(((S_81876014_0 *)effect)->unk_0C);
        y_product = ((S_81876014_0 *)effect)->unk_0A * y_factor;
        ((S_81876014_0 *)effect)->unk_60 = 0;
        vertex_coord = (*(volatile u16 *)((u8 *)effect + 0x60));
        x_edge = ((S_81876014_0 *)effect)->unk_50;
        ASM_KEEP(x_edge);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((S_81876014_0 *)effect)->unk_62 = vertex_coord;
        ASM_KEEP(x_edge);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        x_base = x_edge;
        x_edge += 0x10;
        ASM_KEEP(x_edge);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((S_81876014_0 *)effect)->unk_52 = x_edge;
        x_edge = x_base;
        ((S_81876014_0 *)effect)->unk_54 = x_base;
        ASM_KEEP(x_base);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        z_third = vertex_coord;
        ASM_KEEP(z_third);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        z_third += 0x10;
        ((S_81876014_0 *)effect)->unk_64 = z_third;
        x_edge += 0x10;
        ((S_81876014_0 *)effect)->unk_56 = x_edge;
        position = ((S_81876014_0 *)effect)->unk_44;
        ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        y_offset = y_product >> 12;
        ((S_81876014_0 *)effect)->unk_58 = y_offset;
        ASM_KEEP(y_offset);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        vertex_coord = y_offset;
        ASM_KEEP(vertex_coord);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        y_third = y_offset;
        ASM_KEEP(y_third);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        y_fourth = y_offset;
        ASM_KEEP(y_fourth);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        z_fourth = ((S_81876014_0 *)effect)->unk_60;
        ((S_81876014_0 *)effect)->unk_5A = vertex_coord;
        ((S_81876014_0 *)effect)->unk_5C = y_third;
        ((S_81876014_0 *)effect)->unk_5E = y_fourth;
        z_fourth += 0x10;
        ((S_81876014_0 *)effect)->unk_66 = z_fourth;
        ((S_81876014_2 *)position_out)->unk_00 = ((S_81876014_3 *)position)->unk_00;
        ((S_81876014_2 *)position_out)->unk_04 = ((S_81876014_5 *)(((S_81876014_0 *)effect)->unk_44))->unk_04;
        ((S_81876014_2 *)position_out)->unk_08 = ((S_81876014_5 *)(((S_81876014_0 *)effect)->unk_44))->unk_08;
        ((S_81876014_4 *)color_out)->unk_0C = ((S_81876014_6 *)(((S_81876014_0 *)effect)->unk_48))->unk_0C;
        ((S_81876014_4 *)color_out)->unk_0D = ((S_81876014_6 *)(((S_81876014_0 *)effect)->unk_48))->unk_0D;
        ((S_81876014_4 *)color_out)->unk_0E = ((S_81876014_6 *)(((S_81876014_0 *)effect)->unk_48))->unk_0E;
        angle = ((S_81876014_0 *)effect)->unk_0C;
        next_angle = angle - 0x64;
        ((S_81876014_0 *)effect)->unk_0C = next_angle;
        if (next_angle < 0) {
            ((S_81876014_0 *)effect)->unk_0C = angle + 0xF9C;
        }
        if (((S_81876014_1 *)owner)->unk_0A >= 5) {
            goto mark_finished;
        }
    } else {
mark_finished:
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
