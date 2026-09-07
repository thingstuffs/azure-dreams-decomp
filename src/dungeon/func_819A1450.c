#include "common.h"

typedef struct S_819A1450_0 {
    u8 pad_00[0x3A];
    s16 unk_3A;
    s16 unk_3C;
} S_819A1450_0;   /* setup in func_819A1450 */

typedef struct S_819A1450_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_819A1450_1;   /* node in func_819A1450 */

typedef struct S_819A1450_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_819A1450_2;   /* part in func_819A1450 */

typedef struct S_819A1450_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_819A1450_3;   /* coords in func_819A1450 */

typedef struct S_819A1450_4 {
    u8 pad_00[0x36];
    s16 unk_36;
    u8 pad_38[0x4C];
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
} S_819A1450_4;   /* arg0 in func_819A1450 */



typedef struct {
    s16 first;
    u16 second;
} LocalEntry;

typedef struct {
    LocalEntry entries[8];
} LocalTable;

extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8003DB94();
extern s16 rand();

extern LocalTable D_80024034;
extern u8 D_800246F0[];
extern s32 D_80045340;
extern u8 D_800DEC00[];

void func_819A1450(S_819A1450_4 *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4,
                   s16 arg5)
{
    LocalTable table;
    void *node;
    S_819A1450_2 *part;
    S_819A1450_3 *coords;
    u8 *setup;
    s16 index;

    table = D_80024034;
    node = func_8003FC64(0x212);
    if (node != 0) {
        setup = (u8 *)node + 0x20;
        ((S_819A1450_0 *)setup)->unk_3A = 5;
        ((S_819A1450_0 *)setup)->unk_3C = 5;
        ((S_819A1450_1 *)node)->unk_10 = D_800246F0;
        func_8004491C(node, &D_80045340);

        part = ((S_819A1450_1 *)node)->unk_0C;
        part->unk_10 = 0x20;
        part->unk_14 |= 0xC;
        part->unk_1A = (rand() & 7) << 9;
        part->unk_06 = 0;

        coords = ((S_819A1450_1 *)node)->unk_08;
        coords->unk_02 = arg3;
        coords->unk_06 = arg4;
        coords->unk_0A = arg5;
        coords->unk_02 += arg0->unk_84;
        coords->unk_06 += arg0->unk_86;
        coords->unk_0A += arg0->unk_88;

        index = arg0->unk_36;
        coords->unk_0C =
            (s32)table.entries[index].first << 20;
        index = arg0->unk_36;
        coords->unk_10 =
            (s32)table.entries[index].second << 20;

        part = ((S_819A1450_1 *)node)->unk_0C;
        part->unk_1E = 0x800;
        part->unk_1C = 0x800;
        part->unk_0E = 0x80;
        part->unk_0D = 0x80;
        part->unk_0C = 0x80;
        func_8003DB94(part, D_800DEC00, 0);
    }
}

/* MECHANISM: Preserved the seed's 0x50 frame, eight-register save set, and 32-byte
   stack-local aggregate copy. Typing it as LocalEntry entries[8] made both
   index expressions emit addu $v0,$s6,$v0, closing the two substitutions. */
