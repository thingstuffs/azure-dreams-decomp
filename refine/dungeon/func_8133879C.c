#include "common.h"



typedef s32 M2C_UNK;
extern M2C_UNK D_80083498;
extern u8 D_80083780[12];
extern u8 *D_80175D50[3];
extern s16 func_8016F428(void *arg);

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct S_8016F79C_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_8016F79C_0;   /* s0 in func_8016F79C */

typedef struct S_8016F79C_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_8016F79C_1;   /* s2 in func_8016F79C */

/* Sets the target field from the record or source field and restores two record words. */
void func_8016F79C(void *unused_0, u8 *record, void *unused_2) {
    u8 *source_base = (u8 *)&D_80083498;
    register volatile u8 *source_data = (volatile u8 *)(source_base + 0x20);
    u8 *target_base = D_80175D50[1];
    u8 *target_data = target_base + 0x20;
    s16 raw_value = func_8016F428(record);
    s32 decoded_value = raw_value;

    if (decoded_value == 9) {
        ((S_8016F79C_0 *)target_data)->unk_2A = ((S_8016F79C_1 *)source_data)->unk_2A;
    } else {
        ((S_8016F79C_0 *)target_data)->unk_2A = (u16)(decoded_value << 9);
    }
    {
        register volatile u16 *default_words = (volatile u16 *)D_80083780;
        *(u16 *)(record + 2) = default_words[1];
        *(u16 *)(record + 6) = default_words[3];
    }
}
