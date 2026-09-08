#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8008D050();                      /* extern */

typedef struct S_8008C6B8_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8008C6B8_0;   /* arg0 in func_8008C6B8 */

typedef struct S_8008C6B8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8008C6B8_1;   /* temp_s0 in func_8008C6B8 */

/* Evaluates the summed vector and adjusts nonzero results by the entry's integer second component. */
s16 func_8008C6B8(S_8008C6B8_0 *base_vector, s32 entries_addr, s32 entry_index) {
    s32 combined_vector[5];
    s32 entry_offset;
    s32 query_result;
    s32 second_fixed;
    s32 second_whole;
    s32 component;
    register s32 addend ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_8008C6B8_1 *entry;

    entry_offset = entry_index * 0x10;
    entry = entry_offset + entries_addr;
    component = base_vector->unk_00;
    addend = entry->unk_00;
    component += addend;
    combined_vector[0] = component;
    component = base_vector->unk_04;
    addend = entry->unk_04;
    component += addend;
    combined_vector[1] = component;
    component = base_vector->unk_08;
    addend = entry->unk_08;
    component += addend;
    combined_vector[2] = component;
    query_result = func_8008D050(combined_vector);
    if ((query_result << 0x10) == 0) {
        return 0;
    }
    second_fixed = entry->unk_04;
    second_whole = second_fixed >> 0x10;
    if (second_fixed < 0) {
        second_fixed += 0xFFFF;
        second_whole = second_fixed >> 0x10;
    }
    return query_result - second_whole;
}
