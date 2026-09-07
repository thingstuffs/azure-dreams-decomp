#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001C8C8_1 {
    u8 pad_00[0x1B8];
    void * unk_1B8;
} S_8001C8C8_1;   /* arg0 in func_8001C8C8 */

typedef struct S_8001C8C8_2 {
    u8 pad_00[0x1C0];
    void * unk_1C0;
    u8 pad_1C4[0xC];
    void * unk_1D0;
    u8 pad_1D4[0xC];
    void * unk_1E0;
    u8 pad_1E4[0xC];
    void * unk_1F0;
} S_8001C8C8_2;   /* var_a0 in func_8001C8C8 */

typedef struct S_8001C8C8_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C8C8_3;   /* ((S_8001C8C8_1 *)arg0)->unk_1B8 in func_8001C8C8 */

typedef struct S_8001C8C8_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C8C8_4;   /* ((S_8001C8C8_2 *)var_a0)->unk_1F0 in func_8001C8C8 */

typedef struct S_8001C8C8_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C8C8_5;   /* ((S_8001C8C8_2 *)var_a0)->unk_1C0 in func_8001C8C8 */

typedef struct S_8001C8C8_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C8C8_6;   /* ((S_8001C8C8_2 *)var_a0)->unk_1D0 in func_8001C8C8 */

typedef struct S_8001C8C8_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C8C8_7;   /* ((S_8001C8C8_2 *)var_a0)->unk_1E0 in func_8001C8C8 */

typedef struct S_8001C8C8_8 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8001C8C8_8;   /* ((S_8001C8C8_3 *)(((S_8001C8C8_1 *)arg0)->unk_1B8))->unk_04 in func_8001C8C8 */

typedef struct S_8001C8C8_9 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_8001C8C8_9;   /* ((S_8001C8C8_4 *)(((S_8001C8C8_2 *)var_a0)->unk_1F0))->unk_04 in func_8001C8C8 */

typedef struct S_8001C8C8_10 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_8001C8C8_10;   /* ((S_8001C8C8_5 *)(((S_8001C8C8_2 *)var_a0)->unk_1C0))->unk_04 in func_8001C8C8 */

typedef struct S_8001C8C8_11 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_8001C8C8_11;   /* ((S_8001C8C8_6 *)(((S_8001C8C8_2 *)var_a0)->unk_1D0))->unk_04 in func_8001C8C8 */

typedef struct S_8001C8C8_12 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_8001C8C8_12;   /* ((S_8001C8C8_7 *)(((S_8001C8C8_2 *)var_a0)->unk_1E0))->unk_04 in func_8001C8C8 */




M2C_UNK func_80403698();                      /* extern */
M2C_UNK func_80403738();       /* extern */
M2C_UNK func_804037F4();                            /* extern */
M2C_UNK func_80403868();    /* extern */

typedef struct S_8001C8C8_0 {
    u8 pad_00[0x80];
    s32 unk_80;
    s32 unk_84;
} S_8001C8C8_0;   /* arg0 in func_8001C8C8 */

void func_8001C8C8(void *arg0) {
    s32 var_t3;
    s32 var_t2;
    s32 var_t1;
    s32 var_t0;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    void *var_a0;

    ((S_8001C8C8_0 *)arg0)->unk_80 = 1;
    ((S_8001C8C8_0 *)arg0)->unk_84 = 1;
    func_804037F4();
    func_80403868(arg0 + 4, 0x36, 0x10);
    func_80403698(arg0);
    var_a3 = 0;
    var_t3 = 0x8E;
    var_t2 = 9;
    var_t1 = 0x42;
    var_t0 = 0x24;
    var_a1 = 0xA;
    var_a2 = 0x82;
    var_a0 = arg0;
    ((S_8001C8C8_8 *)(((S_8001C8C8_3 *)(((S_8001C8C8_1 *)arg0)->unk_1B8))->unk_04))->unk_0A = 0x22;
    do {
        ((S_8001C8C8_9 *)(((S_8001C8C8_4 *)(((S_8001C8C8_2 *)var_a0)->unk_1F0))->unk_04))->unk_08 = var_t3;
        ((S_8001C8C8_9 *)(((S_8001C8C8_4 *)(((S_8001C8C8_2 *)var_a0)->unk_1F0))->unk_04))->unk_0A = var_a2;
        ((S_8001C8C8_10 *)(((S_8001C8C8_5 *)(((S_8001C8C8_2 *)var_a0)->unk_1C0))->unk_04))->unk_08 = var_t2;
        ((S_8001C8C8_10 *)(((S_8001C8C8_5 *)(((S_8001C8C8_2 *)var_a0)->unk_1C0))->unk_04))->unk_0A = var_a1;
        ((S_8001C8C8_11 *)(((S_8001C8C8_6 *)(((S_8001C8C8_2 *)var_a0)->unk_1D0))->unk_04))->unk_08 = var_t1;
        ((S_8001C8C8_11 *)(((S_8001C8C8_6 *)(((S_8001C8C8_2 *)var_a0)->unk_1D0))->unk_04))->unk_0A = var_a1;
        var_a3 += 1;
        ((S_8001C8C8_12 *)(((S_8001C8C8_7 *)(((S_8001C8C8_2 *)var_a0)->unk_1E0))->unk_04))->unk_08 = var_t0;
        var_a2 += 0x10;
        ((S_8001C8C8_12 *)(((S_8001C8C8_7 *)(((S_8001C8C8_2 *)var_a0)->unk_1E0))->unk_04))->unk_0A = var_a1;
        var_a0 += 4;
        var_a1 += 0x10;
    } while (var_a3 < 4);
    func_80403738(arg0, var_a1, var_a2, var_a3);
}
