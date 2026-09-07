#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800B22F0_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800B22F0_0;   /* arg2 in func_800B22F0 */

typedef struct S_800B22F0_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x51];
    u8 unk_71;
    u8 pad_72[0x16];
    s16 unk_88;
    u8 pad_8A[0x23];
    u8 unk_AD;
} S_800B22F0_1;   /* state in func_800B22F0 */




extern s8 func_8009FB34(u8, u8);
extern void func_800A2B04(void *, u8, u8);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_80099FDC(void *);
extern void func_8009A21C(u8, u8, s32);
extern void func_800BC26C(void *, s32, void *, void *);

void func_800B22F0(void *arg0, Rec_D_800E3D7C *arg1, void *arg2)
{
    u8 *state = (u8 *)arg0 + 0x20;

    ((S_800B22F0_0 *)arg2)->unk_26 =
        func_8009FB34(((S_800B22F0_0 *)arg2)->unk_24, ((S_800B22F0_0 *)arg2)->unk_25);
    func_800A2B04(arg1, ((S_800B22F0_0 *)arg2)->unk_24, ((S_800B22F0_0 *)arg2)->unk_25);

    ((S_800B22F0_1 *)state)->unk_88 =
        func_800BCB04(arg1->unk_00.at02_u16.v, arg1->unk_04.at02_u16.v,
                      (s16)(arg1->unk_08.at02_u16.v - 0x20));

    ((S_800B22F0_0 *)arg2)->unk_1E = 0x1000;
    ((S_800B22F0_0 *)arg2)->unk_1C = 0x1000;
    ((S_800B22F0_0 *)arg2)->unk_0C = 0x2C808080;
    ((S_800B22F0_0 *)arg2)->unk_14 |= 0x8000;
    func_80099FDC(arg0);

    func_8009A21C(((S_800B22F0_0 *)arg2)->unk_24, ((S_800B22F0_0 *)arg2)->unk_25,
                  (((S_800B22F0_1 *)state)->unk_1C & 0x2000) ? 0x300 : 0x3000);

    ((S_800B22F0_1 *)state)->unk_AD = 1;
    ((S_800B22F0_1 *)state)->unk_71 = 0;
    ((S_800B22F0_1 *)state)->unk_1C |= 0x40000000;
    func_800BC26C(arg0, 0, (u8 *)arg2 + 0x2C, (u8 *)arg0 + 0x4A);
}
