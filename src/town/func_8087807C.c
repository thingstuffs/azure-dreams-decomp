#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80702670();                         /* extern */
M2C_UNK func_807026C0();                         /* extern */
s32 func_80702714();                             /* extern */
extern u8 D_80700000[];

typedef struct S_8070207C_0 {
    u8 pad_00[0x1DCC];
    u16 unk_1DCC;
    u16 unk_1DCE;
} S_8070207C_0;   /* (D_80700000 + temp_s0) in func_8070207C */

typedef struct S_8070207C_1 {
    u8 pad_00[0x1DCC];
    u16 unk_1DCC;
} S_8070207C_1;   /* (D_80700000 + final_index) in func_8070207C */

/* Dispatches the entry's second value based on its first, then processes the first. */
void func_8070207C(s32 entry_index) {
    s32 entry_offset;
    s32 saved_index;
    s32 final_offset;

    saved_index = entry_index;
    entry_offset = entry_index * 4;
    if (func_80702714(((S_8070207C_0 *)(D_80700000 + entry_offset))->unk_1DCC) != 0) {
        func_80702670(((S_8070207C_0 *)(D_80700000 + entry_offset))->unk_1DCE);
    } else {
        do {
        } while (0);
        func_807026C0(((S_8070207C_0 *)(D_80700000 + entry_offset))->unk_1DCE);
    }
    final_offset = saved_index * 4;
    func_80702670(((S_8070207C_1 *)(D_80700000 + final_offset))->unk_1DCC);
}
