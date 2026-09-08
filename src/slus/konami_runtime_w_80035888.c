#include "common.h"

#include "common.h"
#include "records/Rec_func_80034F58_arg0.h"

typedef struct S_80035888_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80035888_0;   /* node in func_80035888 */

typedef struct S_80035888_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    u8 pad_0C[0xC];
    s32 unk_18;
    u8 pad_1C[0x28];
    void * unk_44;
    u8 unk_48;
    u8 pad_49[0x1];
    s16 unk_4A;
    u8 pad_4C[0x28];
    void * unk_74;
    u8 unk_78;
} S_80035888_1;   /* object in func_80035888 */

typedef struct S_80035888_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80035888_2;   /* part8 in func_80035888 */

typedef struct S_80035888_3 {
    s32 unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    s32 unk_0C;
} S_80035888_3;   /* partC in func_80035888 */


typedef struct S_80035888_5 {
    u8 pad_00[0x34];
    s32 unk_34;
} S_80035888_5;   /* ((S_80035888_0 *)node)->unk_20 in func_80035888 */

typedef struct S_80035888_6 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_80035888_6;   /* ((S_80035888_1 *)object)->unk_74 in func_80035888 */



extern void *func_8003FF2C(s32, void *, s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80033C1C(void *, s32);
extern void func_800375C0(void *, void *);
extern void func_800350B0(void *, void *);

extern void func_80033D54(void);
extern void func_800359FC(void);
extern void func_80035AAC(void);
extern void func_80037714(void);

extern u8 D_80082BC0[12];
extern u8 D_8006A9E8[12];
extern s16 D_8006A90C[];
extern u8 D_8007386C[12];
extern s32 D_800809B8;
extern s32 D_800809BC;

void func_80035888(void *arg0, void *arg1, s32 *arg2, s16 arg3, void *arg4)
{
    void *node;
    void *object;
    void *part8;
    void *partC;

    node = func_8003FF2C(0x11, arg0, 0x49, D_80082BC0);
    ((S_80035888_0 *)node)->unk_10 = func_800359FC;
    func_8004491C(node, func_80033D54);

    object = (u8 *)node + 0x20;
    part8 = ((S_80035888_0 *)node)->unk_08;
    partC = ((S_80035888_0 *)node)->unk_0C;
    ((S_80035888_1 *)object)->unk_44 = arg2;
    ((S_80035888_1 *)object)->unk_48 = 1;
    ((S_80035888_1 *)object)->unk_4A = arg3;

    func_80033C1C(arg1, *arg2);

    ((S_80035888_0 *)node)->unk_20 = arg1;
    ((S_80035888_1 *)object)->unk_04 = 0;
    ((S_80035888_1 *)object)->unk_08 = func_80037714;
    func_800375C0(object, D_8006A9E8);
    func_800350B0(arg4, object);

    {
    s32 color;
    s32 first;
    s32 second;

    color = 0x800000;
    first = D_800809B8;
    (*(void * *)((u8 *)object + 0x68)) = func_80035AAC;
    (*(s32 *)((u8 *)object + 0x14)) = first;
    second = D_800809BC;
    color |= second ? 0x8080 : 0x8080;
    ((S_80035888_1 *)object)->unk_18 = second;
    ((S_80035888_2 *)part8)->unk_02 = 0;
    ((S_80035888_3 *)partC)->unk_0C = color;
    ((S_80035888_3 *)partC)->unk_08 = D_8007386C;
    ((S_80035888_3 *)partC)->unk_00 = 0;
    ((S_80035888_3 *)partC)->unk_04 = 0;
    ((S_80035888_3 *)partC)->unk_05 = 0;
    ((S_80035888_1 *)object)->unk_74 = arg4;
    ((S_80035888_1 *)object)->unk_78 = ((Rec_func_80034F58_arg0 *)arg4)->unk_01;
    ((S_80035888_5 *)(((S_80035888_0 *)node)->unk_20))->unk_34 =
        D_8006A90C[((S_80035888_6 *)(((S_80035888_1 *)object)->unk_74))->unk_02];
    }
}
