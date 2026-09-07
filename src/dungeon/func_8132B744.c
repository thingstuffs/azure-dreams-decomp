#include "common.h"

typedef struct S_80172F44_0 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x40];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_80172F44_0;   /* state in func_80172F44 */

typedef struct S_80172F44_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80172F44_1;   /* object in func_80172F44 */

typedef struct S_80172F44_2 {
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
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80172F44_2;   /* display in func_80172F44 */

typedef struct S_80172F44_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80172F44_3;   /* transform in func_80172F44 */

typedef struct S_80172F44_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80172F44_4;   /* arg0 in func_80172F44 */



extern void *func_8003FC64(s32 arg0);
extern void func_8004491C(void *arg0, void *arg1);
extern s32 rand(void);
extern void func_8003DB94(void *arg0, void *arg1, s32 arg2);
extern void func_80045340(void);
extern void func_80172DFC(void);
extern u8 D_800DE870[];

void func_80172F44(S_80172F44_4 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    void *object;
    S_80172F44_3 *transform;
    S_80172F44_2 *display;
    u8 *state;
    s32 value;
    s32 word8;
    u16 x;

    object = func_8003FC64(0x212);
    if (object != 0) {
        state = (u8 *)object + 0x20;
        ((S_80172F44_0 *)state)->unk_16 = 0x1A;
        ((S_80172F44_1 *)object)->unk_10 = func_80172DFC;
        func_8004491C(object, func_80045340);

        display = ((S_80172F44_1 *)object)->unk_0C;
        display->unk_10 = 0x40;
        display->unk_06 = 6;
        display->unk_14 |= 0xC;

        transform = ((S_80172F44_1 *)object)->unk_08;
        transform->unk_00.at00.v = arg0->unk_00;
        transform->unk_04.at00.v = arg0->unk_04;
        
        x = transform->unk_00.at02.v;
        word8 = arg0->unk_08;
        transform->unk_00.at02.v = x + arg1;
        transform->unk_08.at00.v = word8;
        transform->unk_04.at02.v += arg2;
        transform->unk_08.at02.v += arg3;

        value = rand();
        ((S_80172F44_0 *)state)->unk_58 = value - 0x8000;
        value = rand();
        ((S_80172F44_0 *)state)->unk_5C = value - 0x8000;
        value = rand();
        ((S_80172F44_0 *)state)->unk_60 = value - 0x40000;

        display = ((S_80172F44_1 *)object)->unk_0C;
        display->unk_1E = 0x400;
        display->unk_1C = 0x400;
        display->unk_0E = 0x16;
        display->unk_0D = 0x16;
        display->unk_0C = 0x16;
        display->unk_12 = 0x7DCF;
        display->unk_14 |= 0x100;
        func_8003DB94(display, D_800DE870, 0);
    }
}
