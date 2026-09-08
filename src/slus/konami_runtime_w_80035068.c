#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_80034F58_arg0.h"


typedef struct S_80035068_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80035068_3;   /* ((Rec_func_80034F58_arg0 *)arg0)->unk_10 in func_80035068 */


typedef struct S_80035068_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
} S_80035068_0;   /* arg1 in func_80035068 */



void func_80035068(void *arg0, S_80035068_0 *arg1) {
    arg1->unk_04 = (s32) (arg0 + 8);
    arg1->unk_08 = (void *) ((Rec_func_80034F58_arg0 *)arg0)->unk_10;
    ((S_80035068_3 *)(((Rec_func_80034F58_arg0 *)arg0)->unk_10))->unk_04 = arg1;
    ((Rec_func_80034F58_arg0 *)arg0)->unk_10 = arg1;
}
