#include "common.h"



typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80016000[];

typedef struct S_80019ADC_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_80019ADC_0;   /* *(void **)D_80016000 in func_80019ADC */

typedef struct S_80019ADC_1 {
    u8 pad_00[0x29C];
    s32 unk_29C;
} S_80019ADC_1;   /* temp_v0 in func_80019ADC */

typedef struct S_80019ADC_2 {
    u8 unk_00;
    u8 unk_01;
} S_80019ADC_2;   /* temp_v1 in func_80019ADC */

/* Return the first entry index matching both bytes, or -1 if none matches. */
s32 func_80019ADC(s32 match_byte_1, s32 match_byte_0) {
    s32 result;
    s32 entry_index;
    void **entry_slot;
    void *list_owner;
    S_80019ADC_2 *entry;

    result = -1;
    do { list_owner = ((S_80019ADC_0 *)(*(void **)D_80016000))->unk_38; } while (0);
    entry_slot = list_owner + 0x29C;
    entry_index = 0;
    if (((S_80019ADC_1 *)list_owner)->unk_29C != 0) {
loop_1:
        do { entry = *entry_slot; } while (0);
        if ((entry->unk_01 == match_byte_1) &&
            (entry->unk_00 == match_byte_0)) {
            result = entry_index;
            goto done;
        }
        entry_slot = (void **)((s8 *)entry_slot + 4);
        entry_index += 1;
        if (*entry_slot == 0) {
            goto done;
        }
        goto loop_1;
    }
done:
    return result;
}
