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


void func_81971398(void *arg0)
{
    void *base;
    s32 i;
    register u8 *p ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *page;
    u16 count;

    base = arg0;
    do { i = 0; } while (0);
    p = base;
#ifdef NON_MATCHING
    page = (u8 *)&D_80025FF4 - 0x5FF4;
#else
    page = (u8 *)0x80020000;
#endif
    ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    count = ((S_81971398_0 *)base)->unk_38.s;
    ((S_81971398_1 *)page)->unk_5FF4 = 1;
    count--;
    ((S_81971398_0 *)base)->unk_38.s = count;
    do {
        ((S_81971398_2 *)p)->unk_0C =
            ((S_81971398_2 *)p)->unk_1C * ((S_81971398_0 *)base)->unk_38.u /
            ((S_81971398_0 *)base)->unk_3A;
        ((S_81971398_2 *)p)->unk_0D =
            ((S_81971398_2 *)p)->unk_1D * ((S_81971398_0 *)base)->unk_38.u /
            ((S_81971398_0 *)base)->unk_3A;
        i++;
        ((S_81971398_2 *)p)->unk_0E =
            ((S_81971398_2 *)p)->unk_1E * ((S_81971398_0 *)base)->unk_38.u /
            ((S_81971398_0 *)base)->unk_3A;
        p += 4;
    } while (i < 4);
    if (((S_81971398_0 *)base)->unk_38.u <= 0) {
        (*(u16 *)((u8 *)base + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
