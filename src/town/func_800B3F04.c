#include "common.h"
#include "records/Rec_func_800B15B8_arg0.h"

typedef struct S_800B1664_0_pre {
    u16 unk_00;
} S_800B1664_0_pre;   /* the 0x2 bytes before arg0 in func_800B1664, addressed as arg0[-1] */


typedef struct S_800B1664_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800B1664_1;   /* temp_a1 in func_800B1664 */

typedef struct S_800B1664_2 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800B1664_2;   /* temp_v1 in func_800B1664 */


typedef s32 M2C_UNK;


typedef struct S_800B1664_4 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800B1664_4;   /* ((Rec_func_800B15B8_arg0 *)arg0)->unk_C0 in func_800B1664 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    s32 value;
    s32 pad[2];
} GlobalFlags;

M2C_UNK func_8004B248();
M2C_UNK func_800B15B8();
extern GlobalFlags D_800814A0;

void func_800B1664(void *arg0) {
    u16 temp_a0;
    s32 shifted;
    S_800B1664_1 *temp_a1;
    S_800B1664_2 *temp_v1;

    temp_a1 = ((Rec_func_800B15B8_arg0 *)arg0)->unk_C0;
    temp_a0 = temp_a1->unk_06;
    shifted = temp_a0 << 0x10;
    temp_a1->unk_06 = (u16) (temp_a0 - ((s32) ((shifted >> 0x10) + ((u32) shifted >> 0x1F)) >> 1));
    temp_v1 = ((Rec_func_800B15B8_arg0 *)arg0)->unk_C0;
    temp_v1->unk_04 = (u16) (temp_v1->unk_04 - 0x100);
    if ((s16) ((S_800B1664_4 *)(((Rec_func_800B15B8_arg0 *)arg0)->unk_C0))->unk_06 < 0x11) {
        func_8004B248(arg0 + 0xD0, temp_a1);
        func_800B15B8(arg0);
        ((S_800B1664_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800B1664_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0.value |= 0x8000;
    }
}
