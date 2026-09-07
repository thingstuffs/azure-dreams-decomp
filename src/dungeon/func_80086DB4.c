#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80048A44(void *, u8, s32, s32);
extern void func_8008C598() __attribute__((noreturn));
extern void func_800A56E0(u32);
extern s16 D_80083228[];
extern u8 D_800DD030[];


typedef struct S_8008C514_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_8008C514_1;   /* arg3 in func_8008C514 */


void func_8008C514(Rec_func_8008ACDC_arg0 *arg0, s32 arg1, Rec_D_80082E80 *arg2, S_8008C514_1 *arg3) {
    arg0->unk_9A.as_s8 = 0x1A;
    arg0->unk_9B.as_s8 = 0;
    arg0->unk_8C.as_s32 = 0;
    if (arg3->unk_1C & 0x100000) {
        arg2->unk_14.at00_u16.v |= 0x4000;
        func_8008C598(arg2);
    }
    arg2->unk_2C.as_pu8 = D_800DD030;
    func_80048A44(arg2, D_800DD030[((s32)(D_80083228[0] + arg3->unk_2A + 0x100) >> 9) & 7], 0, 1);
    func_800A56E0(0x50A);
    arg0->unk_96.as_s16 = 0;
    arg0->unk_A2 = (u16)(arg0->unk_A2 & 0xFFEF);
}
