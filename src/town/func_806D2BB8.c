/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_806D2BB8_0 {
    s32 unk_00;
    u8 pad_04[0x4];
    union { s32 * s; s32 u; } unk_08;   /* accessed as both */
    s32 unk_0C;
} S_806D2BB8_0;   /* arg1 in func_806D2BB8 */

typedef struct S_806D2BB8_1 {
    s32 unk_00;
    union { s32 * s; s32 u; } unk_04;   /* accessed as both */
    u8 pad_08[0x4];
    s32 unk_0C;
} S_806D2BB8_1;   /* temp_v0 in func_806D2BB8 */


void *func_8001637C();                           /* extern */
extern M2C_UNK D_80017008;

void *func_806D2BB8(void *arg0, S_806D2BB8_0 *arg1) {
    s32 temp_s1;
    s32 temp_v1;
    void *temp_a1;
    S_806D2BB8_1 *temp_v0;

    temp_s1 = arg1->unk_00 & 0x3FFF0000;
    temp_v0 = func_8001637C(arg0, temp_s1);
    temp_a1 = temp_v0;
    if (temp_v0->unk_04.s == NULL) {
        *arg1->unk_08.s = ((s8 *) arg1->unk_0C - (s8 *) &D_80017008) + 4;
        temp_v1 = arg1->unk_08.u;
        temp_v0->unk_00 = temp_s1;
        temp_v0->unk_0C = 0;
        temp_v0->unk_04.u = temp_v1;
    }
    return temp_a1;
}
