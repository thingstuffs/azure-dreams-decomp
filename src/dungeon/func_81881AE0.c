#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800252E0_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800252E0_0;   /* global in func_800252E0 */

typedef struct S_800252E0_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x12];
    void * unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
    u8 pad_24[0x9C];
    u32 unk_C0;
} S_800252E0_1;   /* scratch in func_800252E0 */

typedef struct S_800252E0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800252E0_2;   /* input in func_800252E0 */

typedef struct S_800252E0_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800252E0_3;   /* arg2use in func_800252E0 */

typedef struct S_800252E0_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   /* overlapping accesses */
} S_800252E0_4;   /* p in func_800252E0 */

typedef struct S_800252E0_5_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_800252E0_5_pre;   /* the 0x8 bytes before arg0 in func_800252E0, addressed as arg0[-1] */

typedef struct S_800252E0_6 {
    void * unk_00;
} S_800252E0_6;   /* global_slot in func_800252E0 */

typedef struct S_800252E0_7 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800252E0_7;   /* next in func_800252E0 */

typedef struct S_800252E0_8 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800252E0_8;   /* ((S_800252E0_6 *)global_slot)->unk_00 in func_800252E0 */



extern s32 func_80025340();
extern u32 func_80065420();
extern s32 func_80066460();
extern void func_80067F20();
extern u8 D_80080000[];
extern u8 D_80083160[];

s32 func_800252E0(void *arg0, void *arg1, void *arg2) {
    void *input = arg1;
    void *arg2use = arg2;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *global_slot = D_80080000 + 0x3160;
    u32 low_mask = 0x00FFFFFF;
    u32 high_mask = 0xFF000000;
    void *p;
    s32 *tag;

    {
        void *global = (*(void * *)((u8 *)D_80080000 + 0x3160));
        void *cursor = ((S_800252E0_0 *)global)->unk_8D0;
        ((S_800252E0_1 *)scratch)->unk_20 = (u8 *)global + 0xB0;
        ((S_800252E0_1 *)scratch)->unk_18 = cursor;
    }
    for (;;) {
        register u16 first_coord ASM_REG("$2") = ((S_800252E0_2 *)input)->unk_02;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_800252E0_1 *)scratch)->unk_00 = first_coord;
        ((S_800252E0_1 *)scratch)->unk_02 = ((S_800252E0_2 *)input)->unk_06;
        ((S_800252E0_1 *)scratch)->unk_04 = ((S_800252E0_2 *)input)->unk_0A;
        p = ((S_800252E0_1 *)scratch)->unk_18;
        ((S_800252E0_1 *)scratch)->unk_18 = (u8 *)p + 0xC;
        ((S_800252E0_1 *)scratch)->unk_C0 = func_80065420(
            scratch, (u8 *)p + 8, scratch + 0x90, scratch + 0x94);
        if (((S_800252E0_1 *)scratch)->unk_C0 < 0x1E0) {
            s32 value = ((S_800252E0_3 *)arg2use)->unk_0C;
            ((S_800252E0_4 *)p)->unk_00.at03.v = 2;
            ((S_800252E0_4 *)p)->unk_04.at00.v = value;
            ((S_800252E0_4 *)p)->unk_04.at03.v = 0x6A;
            ((S_800252E0_4 *)p)->unk_00.at00.v = (((S_800252E0_4 *)p)->unk_00.at00.v & high_mask) |
                (*(s32 *)((((S_800252E0_1 *)scratch)->unk_C0 << 2) +
                          (u32)((S_800252E0_1 *)scratch)->unk_20) & low_mask);
            {
                u32 tag_offset;
                tag_offset = *(volatile u32 *)(scratch + 0xC0);
                tag = (s32 *)((tag_offset << 2) +
                              (u32)*(void * volatile *)(scratch + 0x20));
            }
            *tag = (*tag & high_mask) | ((u32)p & low_mask);
            p = ((S_800252E0_1 *)scratch)->unk_18;
            ((S_800252E0_1 *)scratch)->unk_18 = (u8 *)p + 0xC;
            func_80067F20(p, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
            ((S_800252E0_4 *)p)->unk_00.at00.v = (((S_800252E0_4 *)p)->unk_00.at00.v & high_mask) |
                (*(s32 *)((((S_800252E0_1 *)scratch)->unk_C0 << 2) +
                          (u32)((S_800252E0_1 *)scratch)->unk_20) & low_mask);
            {
                register u32 tag_addr ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                tag_addr = *(volatile u32 *)(scratch + 0xC0);
                tag_addr = (tag_addr << 2) +
                           (u32)*(void * volatile *)(scratch + 0x20);
                p = (void *)((u32)p & low_mask);
                *(s32 *)tag_addr = (*(s32 *)tag_addr & high_mask) |
                                   (u32)p;
            }
        }
        {
            void *next = ((S_800252E0_5_pre *)arg0)[-1].unk_00;
            if (next == NULL) {
                ((S_800252E0_8 *)(((S_800252E0_6 *)global_slot)->unk_00))->unk_8D0 =
                    ((S_800252E0_1 *)scratch)->unk_18;
                return 0;
            }
            arg0 = (u8 *)next + 0x20;
            input = ((S_800252E0_7 *)next)->unk_08;
            arg2use = ((S_800252E0_7 *)next)->unk_0C;
        }
    }
}
