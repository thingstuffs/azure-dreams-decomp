#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800233D0_arg0.h"


typedef struct S_80023600_2 {
    u8 pad_00[0x1A8];
    void * unk_1A8;
    u8 pad_1AC[0xC];
    void * unk_1B8;
    u8 pad_1BC[0xC];
    void * unk_1C8;
    u8 pad_1CC[0xC];
    void * unk_1D8;
} S_80023600_2;   /* var_a0 in func_80023600 */

typedef struct S_80023600_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023600_3;   /* ((Rec_func_800233D0_arg0 *)arg0)->unk_1A0 in func_80023600 */

typedef struct S_80023600_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023600_4;   /* ((S_80023600_2 *)var_a0)->unk_1D8 in func_80023600 */

typedef struct S_80023600_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023600_5;   /* ((S_80023600_2 *)var_a0)->unk_1A8 in func_80023600 */

typedef struct S_80023600_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023600_6;   /* ((S_80023600_2 *)var_a0)->unk_1B8 in func_80023600 */

typedef struct S_80023600_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80023600_7;   /* ((S_80023600_2 *)var_a0)->unk_1C8 in func_80023600 */

typedef struct S_80023600_8 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80023600_8;   /* ((S_80023600_3 *)(((Rec_func_800233D0_arg0 *)arg0)->unk_1A0))->unk_04 in func_80023600 */

typedef struct S_80023600_9 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80023600_9;   /* ((S_80023600_4 *)(((S_80023600_2 *)var_a0)->unk_1D8))->unk_04 in func_80023600 */

typedef struct S_80023600_10 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80023600_10;   /* ((S_80023600_5 *)(((S_80023600_2 *)var_a0)->unk_1A8))->unk_04 in func_80023600 */

typedef struct S_80023600_11 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80023600_11;   /* ((S_80023600_6 *)(((S_80023600_2 *)var_a0)->unk_1B8))->unk_04 in func_80023600 */

typedef struct S_80023600_12 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80023600_12;   /* ((S_80023600_7 *)(((S_80023600_2 *)var_a0)->unk_1C8))->unk_04 in func_80023600 */




M2C_UNK func_800233D0();                      /* extern */
M2C_UNK func_80023470();       /* extern */
M2C_UNK func_8002352C(void *);                            /* extern */
M2C_UNK func_800235A0();    /* extern */


void func_80023600(void *arg0) {
    s32 var_t3;
    s32 var_t2;
    s32 var_t1;
    s32 var_t0;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    void *var_a0;

    ((Rec_func_800233D0_arg0 *)arg0)->unk_80 = 1;
    ((Rec_func_800233D0_arg0 *)arg0)->unk_84 = 1;
    func_8002352C(arg0);
    func_800235A0(arg0 + 4, 0x36, 0x10);
    func_800233D0(arg0);
    var_a3 = 0;
    var_t3 = 0x8E;
    var_t2 = 9;
    var_t1 = 0x42;
    var_t0 = 0x24;
    var_a1 = 0xA;
    var_a2 = 0x82;
    var_a0 = arg0;
    ((S_80023600_8 *)(((S_80023600_3 *)(((Rec_func_800233D0_arg0 *)arg0)->unk_1A0))->unk_04))->unk_0A = 0x1A;
    do {
        ((S_80023600_9 *)(((S_80023600_4 *)(((S_80023600_2 *)var_a0)->unk_1D8))->unk_04))->unk_08 = var_t3;
        ((S_80023600_9 *)(((S_80023600_4 *)(((S_80023600_2 *)var_a0)->unk_1D8))->unk_04))->unk_0A = var_a2;
        ((S_80023600_10 *)(((S_80023600_5 *)(((S_80023600_2 *)var_a0)->unk_1A8))->unk_04))->unk_08 = var_t2;
        ((S_80023600_10 *)(((S_80023600_5 *)(((S_80023600_2 *)var_a0)->unk_1A8))->unk_04))->unk_0A = var_a1;
        ((S_80023600_11 *)(((S_80023600_6 *)(((S_80023600_2 *)var_a0)->unk_1B8))->unk_04))->unk_08 = var_t1;
        ((S_80023600_11 *)(((S_80023600_6 *)(((S_80023600_2 *)var_a0)->unk_1B8))->unk_04))->unk_0A = var_a1;
        var_a3 += 1;
        ((S_80023600_12 *)(((S_80023600_7 *)(((S_80023600_2 *)var_a0)->unk_1C8))->unk_04))->unk_08 = var_t0;
        var_a2 += 0x10;
        ((S_80023600_12 *)(((S_80023600_7 *)(((S_80023600_2 *)var_a0)->unk_1C8))->unk_04))->unk_0A = var_a1;
        var_a0 += 4;
        var_a1 += 0x10;
    } while (var_a3 < 3);
    func_80023470(arg0, var_a1, var_a2, var_a3);
}
