#include "common.h"

typedef struct S_819A1034_0 {
    u8 pad_00[0x3A];
    union { u16 s; s16 u; } unk_3A;   /* accessed as both */
    s16 unk_3C;
} S_819A1034_0;   /* base in func_819A1034 */

typedef struct S_819A1034_1 {
    u8 pad_00[0x61B0];
    s16 unk_61B0;
} S_819A1034_1;   /* page in func_819A1034 */

typedef struct S_819A1034_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
} S_819A1034_2;   /* p in func_819A1034 */


extern s16 D_800261B0;
extern s32 D_800814A0;


/* Decrement the fade timer, scale four colors, and flag completion at zero. */
void func_819A1034(void *fade_data)
{
    void *fade;
    s32 color_index;
    register u8 *color_ptr ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *global_page;
    u16 ticks_left;

    fade = fade_data;
    color_index = 0;
    color_ptr = fade;
#ifdef NON_MATCHING
    global_page = (u8 *)&D_800261B0 - 0x5FF4;
#else
    global_page = (u8 *)0x80020000;
#endif
    ASM_KEEP(global_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ticks_left = ((S_819A1034_0 *)fade)->unk_3A.s;
    ((S_819A1034_1 *)global_page)->unk_61B0 = 1;
    ticks_left--;
    ((S_819A1034_0 *)fade)->unk_3A.s = ticks_left;
    do {
        ((S_819A1034_2 *)color_ptr)->unk_0C =
            ((S_819A1034_2 *)color_ptr)->unk_1C * ((S_819A1034_0 *)fade)->unk_3A.u /
            ((S_819A1034_0 *)fade)->unk_3C;
        ((S_819A1034_2 *)color_ptr)->unk_0D =
            ((S_819A1034_2 *)color_ptr)->unk_1D * ((S_819A1034_0 *)fade)->unk_3A.u /
            ((S_819A1034_0 *)fade)->unk_3C;
        color_index++;
        ((S_819A1034_2 *)color_ptr)->unk_0E =
            ((S_819A1034_2 *)color_ptr)->unk_1E * ((S_819A1034_0 *)fade)->unk_3A.u /
            ((S_819A1034_0 *)fade)->unk_3C;
        color_ptr += 4;
    } while (color_index < 4);
    if (((S_819A1034_0 *)fade)->unk_3A.u <= 0) {
        (*(u16 *)((u8 *)fade + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
