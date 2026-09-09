#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"

M2C_UNK func_8008F01C();        /* extern */
M2C_UNK func_8008F104();                         /* extern */
M2C_UNK func_8009B218(); /* extern */
extern M2C_UNK D_800D0690;


typedef struct S_8009C7A8_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8009C7A8_1;   /* arg2 in func_8009C7A8 */

void func_8009C7A8(Rec_D_800CFCB4 *arg0, M2C_UNK arg1, S_8009C7A8_1 *arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg0->unk_94 != 0) {
        arg2->unk_08 = arg4;
        func_8008F104(arg0, arg1, arg5);
        func_8009B218(arg0, arg1, arg2, 0);
        return;
    }
    arg2->unk_08 = arg3;
    func_8008F01C(arg0, arg1, arg5);
    {
        void *call_arg0;
        M2C_UNK call_arg1;
        void *call_arg2;
        M2C_UNK *call_arg3;

        call_arg0 = arg0;
        ASM_KEEP(call_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        call_arg1 = arg1;
        ASM_KEEP(call_arg1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        call_arg2 = arg2;
        ASM_KEEP(call_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        call_arg3 = &D_800D0690;
        ASM_KEEP(call_arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        func_8009B218(call_arg0, call_arg1, call_arg2, call_arg3);
    }
}
