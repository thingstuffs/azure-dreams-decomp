#include "common.h"
#include "m2c_compat.h"

typedef struct S_800249B4_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800249B4_3;   /* temp_v0 in func_800249B4 */

typedef struct S_800249B4_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800249B4_4;   /* ((S_800249B4_3 *)temp_v0)->unk_04 in func_800249B4 */




extern void *func_8004DA74(void *a0, u8 *a1, s32 a2);
extern u8 *D_800283EC[];

typedef struct S_800249B4_0 {
    u8 pad_00[0xB4C];
    void * unk_B4C;
} S_800249B4_0;   /* var_a1 in func_800249B4 */

typedef struct S_800249B4_1 {
    s32 unk_00;
    void * unk_04;
} S_800249B4_1;   /* temp_v0 in func_800249B4 */

typedef struct S_800249B4_2 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800249B4_2;   /* temp_v1 in func_800249B4 */

void func_800249B4(void *arg0) {
    s32 var_t0;
    s16 var_t1;
    s16 var_a3;
    s32 var_a2;
    void *temp_a0;
    S_800249B4_1 *temp_v0;
    S_800249B4_2 *temp_v1;
    void *var_a1;

    func_8004DA74((u8 *)arg0 + 0x84, D_800283EC[0], 1);
    func_8004DA74((u8 *)arg0 + 0x204, D_800283EC[1], 1);
    var_t0 = 0;
    var_t1 = 0xA9;
    var_a3 = 0x110;
    var_a2 = 0x84;
    var_a1 = arg0;
    do {
        temp_a0 = (u8 *)arg0 + var_a2;
        temp_v0 = ((S_800249B4_0 *)var_a1)->unk_B4C;
        var_a2 += 0x180;
        temp_v1 = temp_v0->unk_04;
        var_a1 = (u8 *)var_a1 + 4;
        temp_v0->unk_00 = temp_a0;
        temp_v1->unk_08 = var_t1;
        var_t0 += 1;
        ((S_800249B4_4 *)(((S_800249B4_3 *)temp_v0)->unk_04))->unk_0A = var_a3;
        var_a3 += 0x10;
    } while (var_t0 < 2);
}
