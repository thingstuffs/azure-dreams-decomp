#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001C738_0 {
    u8 pad_00[0x1C0];
    void * unk_1C0;
    u8 pad_1C4[0xC];
    void * unk_1D0;
    u8 pad_1D4[0xC];
    void * unk_1E0;
    u8 pad_1E4[0xC];
    void * unk_1F0;
} S_8001C738_0;   /* var_a0 in func_8001C738 */

typedef struct S_8001C738_1 {
    u8 pad_00[0x4];
    s8 * unk_04;
} S_8001C738_1;   /* ((S_8001C738_0 *)var_a0)->unk_1E0 in func_8001C738 */

typedef struct S_8001C738_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C738_2;   /* ((S_8001C738_0 *)var_a0)->unk_1C0 in func_8001C738 */

typedef struct S_8001C738_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C738_3;   /* ((S_8001C738_0 *)var_a0)->unk_1D0 in func_8001C738 */

typedef struct S_8001C738_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C738_4;   /* ((S_8001C738_0 *)var_a0)->unk_1F0 in func_8001C738 */

typedef struct S_8001C738_5 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x5];
    s16 unk_08;
} S_8001C738_5;   /* ((S_8001C738_1 *)(((S_8001C738_0 *)var_a0)->unk_1E0))->unk_04 in func_8001C738 */

typedef struct S_8001C738_6 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_8001C738_6;   /* ((S_8001C738_2 *)(((S_8001C738_0 *)var_a0)->unk_1C0))->unk_04 in func_8001C738 */

typedef struct S_8001C738_7 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_8001C738_7;   /* ((S_8001C738_3 *)(((S_8001C738_0 *)var_a0)->unk_1D0))->unk_04 in func_8001C738 */

typedef struct S_8001C738_8 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_8001C738_8;   /* ((S_8001C738_4 *)(((S_8001C738_0 *)var_a0)->unk_1F0))->unk_04 in func_8001C738 */





void func_8001C738(void *arg0) {
    s32 var_v1;
    void *var_a0;

    var_a0 = arg0;
    var_v1 = 0;
    do {
        ((S_8001C738_5 *)(((S_8001C738_1 *)(((S_8001C738_0 *)var_a0)->unk_1E0))->unk_04))->unk_08 = 0x24;
        *((S_8001C738_1 *)(((S_8001C738_0 *)var_a0)->unk_1E0))->unk_04 = 0x68;
        ((S_8001C738_5 *)(((S_8001C738_1 *)(((S_8001C738_0 *)var_a0)->unk_1E0))->unk_04))->unk_01 = 0x68;
        ((S_8001C738_5 *)(((S_8001C738_1 *)(((S_8001C738_0 *)var_a0)->unk_1E0))->unk_04))->unk_02 = 0x60;
        ((S_8001C738_6 *)(((S_8001C738_2 *)(((S_8001C738_0 *)var_a0)->unk_1C0))->unk_04))->unk_08 = 9;
        ((S_8001C738_7 *)(((S_8001C738_3 *)(((S_8001C738_0 *)var_a0)->unk_1D0))->unk_04))->unk_08 = 0x42;
        var_v1 += 1;
        ((S_8001C738_8 *)(((S_8001C738_4 *)(((S_8001C738_0 *)var_a0)->unk_1F0))->unk_04))->unk_08 = 0x8F;
        var_a0 += 4;
    } while (var_v1 < 4);
}
