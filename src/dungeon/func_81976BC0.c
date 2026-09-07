#include "common.h"

typedef struct S_81976BC0_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_81976BC0_0;   /* object in func_81976BC0 */

typedef struct S_81976BC0_1 {
    u8 pad_00[0x4];
    void * unk_04;
    s32 unk_08;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
} S_81976BC0_1;   /* fields in func_81976BC0 */

typedef struct S_81976BC0_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_81976BC0_2;   /* child in func_81976BC0 */



extern void *func_8003FD64(s32, void *);
extern s32 rand(void);
extern u8 D_80024050[];
extern s32 D_800261E4[];
extern u8 D_80083498[];

void func_81976BC0(s32 arg0, s32 arg1)
{
    s32 value;
    S_81976BC0_2 *child;
    void *object;
    S_81976BC0_1 *fields;

    object = func_8003FD64(0x12, D_80083498);
    if (object != 0) {
        ((S_81976BC0_0 *)object)->unk_10 = D_80024050;
        fields = (u8 *)object + 0x20;
        fields->unk_0C = 0;
        fields->unk_0E = 0;
        fields->unk_10 = 0;
        ((S_81976BC0_0 *)object)->unk_20 = arg0;
        fields->unk_04 = D_80083498;
        fields->unk_08 = arg1;
        child = ((S_81976BC0_0 *)object)->unk_0C;
        child->unk_08 = D_800261E4[0];
        child->unk_0E = 0x40;
        child->unk_0D = 0x40;
        child->unk_0C = 0x40;
        child->unk_1E = 0x1800;
        child->unk_1C = 0x1800;
        value = rand();
        child->unk_1A = value % 0x1000;
        child->unk_12 = 0x7DCF;
        child->unk_10 |= 0x20;
        child->unk_14 |= 0x10C;
    }
}
