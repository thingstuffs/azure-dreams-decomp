#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800B6814_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800B6814_0;   /* node in func_800B6814 */

typedef struct S_800B6814_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800B6814_1;   /* part in func_800B6814 */

typedef struct S_800B6814_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B6814_2;   /* arg0 in func_800B6814 */

typedef struct S_800B6814_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x4];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
} S_800B6814_3;   /* sub in func_800B6814 */

typedef struct S_800B6814_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800B6814_4;   /* image in func_800B6814 */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s16);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand(void);

extern s32 D_80045340;
extern s32 D_800B63A8;
extern s32 D_800DEC00;

void func_800B6814(S_800B6814_2 *arg0)
{
    s32 count;
    s32 step;
    s32 angle;
    s32 i;
    s32 value;
    S_800B6814_1 *part;
    void *node;
    S_800B6814_4 *image;
    S_800B6814_3 *sub;

    count = (rand() & 0xF) | 8;
    step = 0x1000 / count;
    i = 0;
    angle = rand();
    if ((u16)count != 0) {
        do {
            node = func_8003FC64(0x212);
            
            if (node != NULL) {
                part = ((S_800B6814_0 *)node)->unk_08;
                image = ((S_800B6814_0 *)node)->unk_0C;
                ((S_800B6814_0 *)node)->unk_10 = &D_800B63A8;
                func_8004491C(node, &D_80045340);
                part->unk_02 =
                    arg0->unk_02 + (func_80064584(angle) >> 11);
                part->unk_06 =
                    arg0->unk_06 + (func_800644B8(angle) >> 11);
                part->unk_0A = arg0->unk_0A;
                part->unk_0C = func_80064584(angle) << 6;
                part->unk_10 = func_800644B8(angle) << 6;
                part->unk_14 = 0xFFFD0000;
                ((S_800B6814_0 *)node)->unk_20 = -part->unk_0C >> 6;
                value = part->unk_10;
                sub = (u8 *)node + 0x20;
                sub->unk_08 = 0x2000;
                sub->unk_04 = -value >> 6;
                func_8003DB94(image, &D_800DEC00, 0);
                image->unk_0C = 0x808080;
                image->unk_1E = 0x400;
                image->unk_1C = 0x400;
                image->unk_10 = 0x60;
                image->unk_12 = 0x7E80;
                image->unk_14 |= 0x10C;
                sub->unk_0E = (rand() & 3) | 0x10;
                sub->unk_16 = 0x10;
                sub->unk_14 = 0x10;
                sub->unk_18 = 8;
            }
            i++;
            angle += step;
        } while (i < count);
    }
}
