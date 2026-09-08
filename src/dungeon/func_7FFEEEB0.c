#include "common.h"
#include "m2c_compat.h"

extern s32 func_8008D01C(s32 *);

typedef struct S_8008C610_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8008C610_0;   /* arg0 in func_8008C610 */

typedef struct S_8008C610_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8008C610_1;   /* temp_s0 in func_8008C610 */

/* Evaluates the summed position and subtracts the offset's integer Y component. */
s16 func_8008C610(S_8008C610_0 *base_pos, s32 offsets_addr, s32 offset_index) {
    s32 position[5];
    s32 sample_result;
    s32 offset_bytes;
    s32 offset_y;
    s32 whole_y;
    S_8008C610_1 *offset;

    offset_bytes = offset_index * 0x10;
    offset = offset_bytes + offsets_addr;
    position[0] = base_pos->unk_00 + offset->unk_00;
    position[1] = base_pos->unk_04 + offset->unk_04;
    position[2] = base_pos->unk_08 + offset->unk_08;
    sample_result = func_8008D01C(position);
    if ((s16) sample_result == 0x7FFF) {
        return 0x7FFF;
    }
    offset_y = offset->unk_04;
    whole_y = offset_y >> 0x10;
    if (offset_y < 0) {
        offset_y += 0xFFFF;
        whole_y = offset_y >> 0x10;
    }
    return sample_result - whole_y;
}
