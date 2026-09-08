#include "common.h"

typedef struct S_8196B4A4_0 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    u8 pad_2E[0x5E];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    u8 pad_98[0x8];
    s32 unk_A0;
} S_8196B4A4_0;   /* sub in func_8196B4A4 */

typedef struct S_8196B4A4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8196B4A4_1;   /* node in func_8196B4A4 */

typedef struct S_8196B4A4_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_8196B4A4_2;   /* part in func_8196B4A4 */

typedef struct S_8196B4A4_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8196B4A4_3;   /* coords in func_8196B4A4 */

typedef struct S_8196B4A4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8196B4A4_4;   /* coord_base in func_8196B4A4 */

typedef struct S_8196B4A4_5 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_8196B4A4_5;   /* arg0 in func_8196B4A4 */



typedef struct {
    u8 bytes[0x20];
} LocalPoints;

typedef struct {
    s16 x;
    u16 y;
} LocalPoint;

extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8003DB94();
extern s16 rand();

extern LocalPoints D_80024004;
extern u8 D_80024874[];
extern s32 D_80045340;
extern u8 D_80083780[];
extern u8 D_800DEC70[];

void func_8196B4A4(S_8196B4A4_5 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5)
{
    LocalPoints points;
    void *node;
    S_8196B4A4_0 *sub;
    S_8196B4A4_2 *part;
    S_8196B4A4_3 *coords;
    u8 *coord_base;
    LocalPoint *point_base;
    LocalPoint *point;
    s32 point_index;
    register s32 x_arg3 ASM_REG("$21") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 x_arg4 ASM_REG("$19") = arg4;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 x_arg5 ASM_REG("$20") = arg5;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

    points = D_80024004;
    point_base = (LocalPoint *)&points;
    node = func_8003FC64(0x212);
    if (node != 0) {
        sub = (u8 *)node + 0x20;
        sub->unk_2C = 0xF;
        ((S_8196B4A4_1 *)node)->unk_10 = D_80024874;
        func_8004491C(node, &D_80045340);

        part = ((S_8196B4A4_1 *)node)->unk_0C;
        part->unk_10 = 0x20;
        part->unk_14 |= 0xC;
        part->unk_1A = (rand() & 7) << 9;
        part->unk_06 = 0;

        coords = ((S_8196B4A4_1 *)node)->unk_08;
        coord_base = D_80083780;
        coords->unk_02 = x_arg3;
        coords->unk_06 = x_arg4;
        coords->unk_0A = x_arg5;
        coords->unk_02 += ((S_8196B4A4_4 *)coord_base)->unk_02;
        coords->unk_06 += ((S_8196B4A4_4 *)coord_base)->unk_06;
        coords->unk_0A += ((S_8196B4A4_4 *)coord_base)->unk_0A;

        coords->unk_02 += (rand() & 0x3F) - 0x20;
        coords->unk_06 += (rand() & 0x3F) - 0x20;
        coords->unk_0A += (rand() & 0x3F) - 0x40;

        sub->unk_94 = -0x60000;
        sub->unk_A0 = 0x20000;
        point = point_base;
        point_index = arg0->unk_26;
        point += point_index;
        sub->unk_8C = point->x << 18;
        point = point_base;
        point_index = arg0->unk_26;
        point += point_index;
        sub->unk_90 = point->y << 18;

        sub->unk_8C +=
            -0x80000 + ((rand() & 0x3FFF) << 6);
        sub->unk_90 +=
            -0x80000 + ((rand() & 0x3FFF) << 6);
        sub->unk_94 +=
            -0x80000 + ((rand() & 0x3FFF) << 6);

        part = ((S_8196B4A4_1 *)node)->unk_0C;
        part->unk_1C = part->unk_1E = 0x800;
        part->unk_0C = part->unk_0D =
            part->unk_0E = 0x80;
        part->unk_12 = 0x7DCE;
        part->unk_14 |= 0x100;
        func_8003DB94(part, D_800DEC70, 0);
    }
    ASM_KEEP(x_arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}

/* MECHANISM: The 0x20 byte-aligned copy object preserves the 0x58 frame and lwl/lwr stack copy;
   a held D_80083780 base plus RMW updates restores the load-delay moves and $a0 base.
   Epilogue-held arg pins and split point base/index/add produce the retail saved roles and $s6+$v0 order. */
