#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_800C70B8_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C70B8_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in func_800C70B8 */


extern void func_800C2E84();
extern void func_800C4174();
extern u8 D_80082660;


void func_800C70B8(Rec_func_80094268_arg0 *arg0, s32 arg1, s32 arg2) {
    func_800C2E84(arg0, arg2, ((S_800C70B8_1 *)(arg0->unk_80))->unk_04);
    *(&D_80082660 + (arg0->unk_60 * 8)) = 0;
    arg0->unk_72.as_s16 = 0x200;
    func_800C4174(arg0, arg1, arg2);
}

/* MECHANISM: The three incoming values remain live across the first call, forcing
   the 0x20 frame and s0/s2/s1 holds; the first call keeps its real three-argument ABI.
   D_80082660 is byte-wide, so the indexed table clear emits sb rather than sw. */
