#include "common.h"
#include "m2c_compat.h"

extern s32 func_8008CF80(s32 *);

typedef struct S_8008C420_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8008C420_0;   /* arg0 in func_8008C420 */

typedef struct S_8008C420_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8008C420_1;   /* temp_s0 in func_8008C420 */

/* Queries the combined position and subtracts the offset's integer Z component. */
s16 func_8008C420(S_8008C420_0 *origin, s32 offset_table, s32 offset_index) {
    s32 position[5];
    s32 query_result;
    s32 offset_bytes;
    s32 offset_z;
    s32 offset_z_int;
    S_8008C420_1 *offset;

    offset_bytes = offset_index * 0x10;
    offset = offset_bytes + offset_table;
    position[0] = origin->unk_00 + offset->unk_00;
    position[1] = origin->unk_04 + offset->unk_04;
    position[2] = origin->unk_08 + offset->unk_08;
    query_result = func_8008CF80(position);
    if ((s16) query_result == -0x7FFF) {
        return -0x7FFF;
    }
    offset_z = offset->unk_08;
    offset_z_int = offset_z >> 0x10;
    if (offset_z < 0) {
        offset_z += 0xFFFF;
        offset_z_int = offset_z >> 0x10;
    }
    return query_result - offset_z_int;
}
