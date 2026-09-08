#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern s32 func_8008CFE8(s32 *, s32, s32);

typedef struct S_8008C570_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8008C570_0;   /* arg0 in func_8008C570 */

typedef struct S_8008C570_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8008C570_1;   /* temp_s0 in func_8008C570 */

/* Evaluates the summed vector and subtracts the entry's integer first component on success. */
s32 func_8008C570(S_8008C570_0 *vector, s32 entry_base, s32 entry_index) {
    s32 summed_vector[5];
    s32 entry_offset;
    s32 result;
    s32 first_fixed;
    s32 first_integer;
    S_8008C570_1 *entry;

    entry_offset = entry_index * 0x10;
    entry = entry_offset + entry_base;
    summed_vector[0] = vector->unk_00 + entry->unk_00;
    summed_vector[1] = vector->unk_04 + entry->unk_04;
    summed_vector[2] = vector->unk_08 + entry->unk_08;
    result = func_8008CFE8(summed_vector, entry_base, entry_offset);
    if ((result << 0x10) == 0) {
        return 0;
    }
    first_fixed = entry->unk_00;
    first_integer = first_fixed >> 0x10;
    if (first_fixed < 0) {
        first_fixed += 0xFFFF;
        first_integer = first_fixed >> 0x10;
    }
    return (s16) (result - first_integer);
}
