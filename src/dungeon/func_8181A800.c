#include "common.h"
#include "shared/object_flags.h"

typedef struct S_8181A800_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    s16 unk_04;
} S_8181A800_0;   /* arg0 in func_8002404C; pointer addresses record offset 0x2 */

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800478B8(void *);
extern s16 D_80025914[9];

/* Decrement the record counter, process update data, and flag depletion. */
void func_8002404C(void *record_data, void *unused, void *update_data) {
    s16 remaining;
    s16 *update_flag;

    update_flag = D_80025914;
    remaining = (s16)((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_04 - 1;
    update_flag[0] = 1;
    ((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_04 = remaining;
    func_800478B8(update_data);
    if (((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_04 <= 0) {
        ((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_00 =
            (u16)(((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_00 | 0x8000);
        objectFlagBlock.flags |= 0x8000;
    }
}
