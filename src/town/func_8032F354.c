#include "common.h"
#include "records/Rec_func_800165F4_arg0.h"


typedef struct S_80019B54_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80019B54_1;   /* (arg1 * 0x10) + ((Rec_func_800165F4_arg0 *)arg0)->unk_10 in func_80019B54 */



extern s32 func_800199DC(void);
extern s32 func_8001ACE8(s16 value);
extern s32 func_8001AD60(s16 value);

s32 func_80019B54(Rec_func_800165F4_arg0 *arg0, s32 arg1) {
    if (func_800199DC() != 0) {
        func_8001ACE8(((S_80019B54_1 *)((arg1 * 0x10) + arg0->unk_10))->unk_0C);
        func_8001AD60(arg0->unk_18);
        ASM_USE(arg1);   /* MATCH pin: retail register colouring depends on it */
        return 1;
    }
    return 0;
}
