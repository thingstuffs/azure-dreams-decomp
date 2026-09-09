#include "common.h"

typedef struct S_80026C20_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    void * unk_14;
} S_80026C20_0;   /* temp_a0 in func_80026C20 */

typedef struct S_80026C20_1 {
    u8 unk_00;
    union { u8 s; volatile u8 u; } unk_01;   /* accessed as both */
} S_80026C20_1;   /* var_a2 in func_80026C20 */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80029510[12];

/* Returns whether the object's byte pairs contain a nondefault, nonspace pair. */
s32 func_80026C20(s32 object_addr) {
    s32 byte_count;
    s32 loop_bound;
    u8 compare_space;
    s32 pair_count;
    s32 byte_offset;
    s32 has_content;
    u8 first_byte;
    u8 default_first;
    S_80026C20_0 *pair_info;
    void *pair_data;
    S_80026C20_1 *pair;
    u8 *default_pair;

    has_content = 0;
    if (object_addr != 0) {
        pair_info = object_addr + 0x20;
        pair_count = 9;
        if (pair_info->unk_0C == 0x13) {
            pair_count = 6;
        }
        byte_count = pair_count * 2;
        byte_offset = 0;
        if (has_content < byte_count) {
            default_pair = D_80029510;
            compare_space = 0x20;
            loop_bound = byte_count;
            pair_data = pair_info->unk_14;
            default_first = D_80029510[0];
next_pair:
            pair = pair_data + byte_offset;
            first_byte = pair->unk_00;
            if (first_byte != 0) {
                if (((first_byte != default_first) ||
                     (pair->unk_01.s !=
                      default_pair[1])) &&
                    ((first_byte != compare_space) ||
                     (pair->unk_01.u != first_byte))) {
                    has_content = 1;
                }
                byte_offset += 2;
                if (byte_offset < loop_bound) {
                    goto next_pair;
                }
            }
        }
    }
    return has_content;
}

/* MECHANISM: Frameless leaf with held t0/t1/t2/t3/t4 roles and a volatile second byte read.
   Distinct a1 -> v1 -> t2 bound lifetimes plus the t0-relative test force retail's slt/beqz
   and move handoff, restoring the two missing words and every cascaded branch displacement. */
