#include "common.h"

typedef struct S_8016EB14_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8016EB14_0;   /* root in func_8016EB14 */

typedef struct S_8016EB14_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8016EB14_1;   /* object in func_8016EB14 */

typedef struct S_8016EB14_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016EB14_2;   /* part in func_8016EB14 */

typedef struct S_8016EB14_3 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0xA];
    void * unk_24;
    u8 pad_28[0x1C];
    u8 unk_44;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
    s8 unk_48;
    s8 unk_49;
    u8 pad_4A[0x2];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_8016EB14_3;   /* body in func_8016EB14 */

typedef struct S_8016EB14_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8016EB14_4;   /* target in func_8016EB14 */

typedef struct S_8016EB14_5 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8016EB14_5;   /* source in func_8016EB14 */

typedef struct S_8016EB14_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x7E];
    s16 unk_AA;
} S_8016EB14_6;   /* owner in func_8016EB14 */


extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern u8 D_80045340;
extern u8 D_800777B8;
extern u8 D_8016E528;
extern void *D_80174704;
extern s16 D_80174708[16];


void func_8016EB14(void)
{
    s32 x;
    s32 y;
    s32 table_y;
    void *root;
    S_8016EB14_5 *source;
    S_8016EB14_6 *owner;
    register void *body ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *object;
    S_8016EB14_2 *part;
    S_8016EB14_4 *target;
    u8 *table;
    u8 *entry;

    root = D_80174704;
    source = ((S_8016EB14_0 *)root)->unk_08;
    owner = (u8 *)root + 0x20;
    object = func_8003FC64(0x12);
    if (object != 0) {
        ((S_8016EB14_1 *)object)->unk_10 = &D_8016E528;
        func_8004491C(object, &D_80045340);
        part = ((S_8016EB14_1 *)object)->unk_0C;
        part->unk_14 &= 0xFFF3;
        body = (u8 *)object + 0x20;
        ((S_8016EB14_3 *)body)->unk_24 = owner;
        target = ((S_8016EB14_1 *)object)->unk_08;
        target->unk_02 = source->unk_02.s;
        target->unk_06 = source->unk_06.s;
        target->unk_0A = source->unk_0A - 0x20;
#ifdef NON_MATCHING
        table = (u8 *)D_80174708;
#else
        table = (u8 *)0x80170000;
        ASM_KEEP(table);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        table += 0x4708;
#endif
        x = *(s16 *)(u8 *)(((owner->unk_2A >> 7) & 0x1C) +
                           (u32)table);
        ((S_8016EB14_3 *)body)->unk_4C = x << 18;
        table_y = *(s16 *)((u8 *)(((owner->unk_2A >> 7) & 0x1C) +
                                  (u32)table) + 2);
        ((S_8016EB14_3 *)body)->unk_54 = 0xFFF80000;
        ((S_8016EB14_3 *)body)->unk_60 = 0x14900;
        ((S_8016EB14_3 *)body)->unk_50 = table_y << 18;

        ((S_8016EB14_3 *)body)->unk_18 = (owner->unk_2A >> 9) & 7;
        part = ((S_8016EB14_1 *)object)->unk_0C;
        part->unk_1E = 0x1000;
        part->unk_1C = 0x1000;
        entry = (u8 *)(((owner->unk_2A >> 7) & 0x1C) + (u32)table);
        part->unk_06 = *(s16 *)(entry + 2) * 6;
        owner->unk_AA = 0x4D;

        x = source->unk_02.u;
        ((S_8016EB14_3 *)body)->unk_48 = x / 64;
        y = source->unk_06.u;
        ((S_8016EB14_3 *)body)->unk_49 = y / 64;
        part->unk_0E = 0x80;
        part->unk_0D = 0x80;
        part->unk_0C = 0x80;
        part->unk_08 = &D_800777B8;
        ((S_8016EB14_3 *)body)->unk_44 = 0xF;
        ((S_8016EB14_3 *)body)->unk_45 = 1;
        ((S_8016EB14_3 *)body)->unk_46 = 0;
        ((S_8016EB14_3 *)body)->unk_47 = 0;
    }
}
