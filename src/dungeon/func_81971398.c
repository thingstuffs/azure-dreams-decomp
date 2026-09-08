#include "common.h"

typedef struct S_81971398_0 {
    u8 pad_00[0x38];
    union { u16 s; s16 u; } unk_38;   /* accessed as both */
    s16 unk_3A;
} S_81971398_0;   /* base in func_81971398 */

typedef struct S_81971398_1 {
    u8 pad_00[0x5FF4];
    s16 unk_5FF4;
} S_81971398_1;   /* page in func_81971398 */

typedef struct S_81971398_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
} S_81971398_2;   /* p in func_81971398 */


extern s16 D_80025FF4;
extern s32 D_800814A0;


/* Advance the fade, scale four vertex colors, and flag completion when the timer expires. */
void func_81971398(void *fade_data)
{
    void *fade;
    s32 vertex_index;
    register u8 *vertex ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 *global_page;
    u16 ticks_left;

    fade = fade_data;
    do { vertex_index = 0; } while (0);
    vertex = fade;
#ifdef NON_MATCHING
    global_page = (u8 *)&D_80025FF4 - 0x5FF4;
#else
    global_page = (u8 *)0x80020000;
#endif
    ASM_KEEP(global_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ticks_left = ((S_81971398_0 *)fade)->unk_38.s;
    ((S_81971398_1 *)global_page)->unk_5FF4 = 1;
    ticks_left--;
    ((S_81971398_0 *)fade)->unk_38.s = ticks_left;
    do {
        ((S_81971398_2 *)vertex)->unk_0C =
            ((S_81971398_2 *)vertex)->unk_1C * ((S_81971398_0 *)fade)->unk_38.u /
            ((S_81971398_0 *)fade)->unk_3A;
        ((S_81971398_2 *)vertex)->unk_0D =
            ((S_81971398_2 *)vertex)->unk_1D * ((S_81971398_0 *)fade)->unk_38.u /
            ((S_81971398_0 *)fade)->unk_3A;
        vertex_index++;
        ((S_81971398_2 *)vertex)->unk_0E =
            ((S_81971398_2 *)vertex)->unk_1E * ((S_81971398_0 *)fade)->unk_38.u /
            ((S_81971398_0 *)fade)->unk_3A;
        vertex += 4;
    } while (vertex_index < 4);
    if (((S_81971398_0 *)fade)->unk_38.u <= 0) {
        (*(u16 *)((u8 *)fade + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
