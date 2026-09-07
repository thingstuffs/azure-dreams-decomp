#include "common.h"

typedef struct S_8002593C_0 {
    u8 pad_00[0x40];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x4];
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
    s16 unk_5C;
    s16 unk_5E;
    s16 unk_60;
} S_8002593C_0;   /* scratch in func_8002593C */

typedef struct S_8002593C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8002593C_1;   /* arg1 in func_8002593C */

typedef struct S_8002593C_2 {
    u8 pad_00[0x16];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_8002593C_2;   /* arg2 in func_8002593C */



typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

extern void func_80064840(void *, void *, void *);
extern void func_80064AE0(void *);
extern void func_80064B90(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_80065AB0(u16, void *);
extern void func_80065C50(u16, void *);
extern void func_80065DF0(u16, void *);

void func_8002593C(void *arg0, S_8002593C_1 *arg1, S_8002593C_2 *arg2)
{
    u8 *scratch = (u8 *)0x1F800000;
    MATRIX matrix;

    ((S_8002593C_0 *)scratch)->unk_40 = arg1->unk_02;
    ((S_8002593C_0 *)scratch)->unk_44 = arg1->unk_06;
    ((S_8002593C_0 *)scratch)->unk_48 = arg1->unk_0A;
    func_80064AE0(&matrix);

    ((S_8002593C_0 *)scratch)->unk_50 = ((S_8002593C_0 *)scratch)->unk_58 =
        ((S_8002593C_0 *)scratch)->unk_60 = 0x1000;
    ((S_8002593C_0 *)scratch)->unk_52 = ((S_8002593C_0 *)scratch)->unk_54 =
        ((S_8002593C_0 *)scratch)->unk_56 = ((S_8002593C_0 *)scratch)->unk_5A =
        ((S_8002593C_0 *)scratch)->unk_5C = ((S_8002593C_0 *)scratch)->unk_5E = 0;

    func_80065AB0(arg2->unk_16, scratch + 0x50);
    func_80065DF0(arg2->unk_1A, scratch + 0x50);
    func_80065C50(arg2->unk_18, scratch + 0x50);
    func_80064B90(scratch + 0x50, scratch + 0x40);
    func_80064840(scratch + 0x50, arg0, scratch + 0xD0);
    func_80064D80(scratch + 0xD0);
    func_80064CF0(scratch + 0xD0);
}
