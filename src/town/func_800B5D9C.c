#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B34FC_1 {
    u8 pad_00[0x9C];
    void * unk_9C;
} S_800B34FC_1;   /* arg0 in func_800B34FC */

typedef struct S_800B34FC_2 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_800B34FC_2;   /* ((S_800B34FC_1 *)arg0)->unk_9C in func_800B34FC */


typedef struct S_800B34FC_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x14];
    s32 unk_18;
} S_800B34FC_0;   /* arg0 in func_800B34FC; pointer addresses record offset 0x10 */


extern M2C_UNK D_800B34A8;

void func_800B34FC(void *arg0) {
    s32 temp_v0;

    ((S_800B34FC_2 *)(((S_800B34FC_1 *)arg0)->unk_9C))->unk_06 = (s16) ((((S_800B34FC_0 *)((u8 *)arg0 - 0x10))->unk_18 << 0xC) / 5);
    temp_v0 = ((S_800B34FC_0 *)((u8 *)arg0 - 0x10))->unk_18 + 1;
    ((S_800B34FC_0 *)((u8 *)arg0 - 0x10))->unk_18 = temp_v0;
    if (temp_v0 >= 6) {
        ((S_800B34FC_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_800B34A8;
    }
}
