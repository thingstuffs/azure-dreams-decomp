#include "common.h"
#include "m2c_compat.h"

extern u8 D_80178240;
extern s32 D_80178280;
extern s32 D_801782C4;

typedef struct S_80040F10_0 {
    s32 unk_00;
} S_80040F10_0;   /* var_a1 in func_80040F10 */

typedef struct S_80040F10_1 {
    s32 unk_00;
} S_80040F10_1;   /* var_a2 in func_80040F10 */

typedef struct S_80040F10_2 {
    s32 unk_00;
} S_80040F10_2;   /* var_a1_2 in func_80040F10 */

typedef struct S_80040F10_3 {
    s32 unk_00;
} S_80040F10_3;   /* var_a2_2 in func_80040F10 */

typedef struct S_80040F10_4 {
    s32 unk_00;
} S_80040F10_4;   /* var_a1_3 in func_80040F10 */

typedef struct S_80040F10_5 {
    s32 unk_00;
} S_80040F10_5;   /* var_a2_3 in func_80040F10 */

/* Copy three global data blocks into a contiguous 256-byte buffer. */
s32 *func_80040F10(s8 *buffer) {
    s8 *first_src;
    s8 *second_src;
    s8 *third_src;
    s8 *first_dst;
    s8 *second_dst;
    s8 *third_dst;
    s32 first_word;
    s32 second_word;
    s32 third_word;
    s32 first_countdown;
    s32 second_countdown;
    s32 third_countdown;

    first_dst = buffer;
    first_src = &D_80178240;
    first_countdown = 0xF;
    do {
        first_word = ((S_80040F10_0 *)first_src)->unk_00;
        first_src += 4;
        first_countdown -= 1;
        ((S_80040F10_1 *)first_dst)->unk_00 = first_word;
        first_dst += 4;
    } while (first_countdown != -1);
    second_dst = buffer + 0x40;
    second_src = &D_80178280;
    second_countdown = 0xF;
    do {
        second_word = ((S_80040F10_2 *)second_src)->unk_00;
        second_src += 4;
        second_countdown -= 1;
        ((S_80040F10_3 *)second_dst)->unk_00 = second_word;
        second_dst += 4;
    } while (second_countdown != -1);
    third_dst = buffer + 0x80;
    third_src = &D_801782C4;
    third_countdown = 0x1F;
    do {
        third_word = ((S_80040F10_4 *)third_src)->unk_00;
        third_src += 4;
        third_countdown -= 1;
        ((S_80040F10_5 *)third_dst)->unk_00 = third_word;
        third_dst += 4;
    } while (third_countdown != -1);
    return buffer;
}
