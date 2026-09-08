#include "common.h"
#include "m2c_compat.h"

typedef struct S_80020458_2 {
    u8 pad_00[0x60];
    void * unk_60;
} S_80020458_2;   /* arg0 in func_80020458 */

typedef struct S_80020458_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80020458_3;   /* temp_a2 in func_80020458 */

typedef struct S_80020458_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80020458_4;   /* temp_a2_2 in func_80020458 */

typedef struct S_80020458_5 {
    void * unk_00;
    void * unk_04;
} S_80020458_5;   /* ((S_80020458_2 *)arg0)->unk_60 in func_80020458 */

typedef struct S_80020458_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80020458_6;   /* ((S_80020458_3 *)temp_a2)->unk_04 in func_80020458 */

typedef struct S_80020458_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80020458_7;   /* ((S_80020458_4 *)temp_a2_2)->unk_04 in func_80020458 */




/* Callback function addresses outside this overlay's own window (0x8000D000-
   0x80022000); they belong to code loaded elsewhere and are only ever stored
   as raw pointers here, never called, so bind them as absolute symbols
   (established .set idiom) rather than declaring undefined func_ externs. */
__asm__(".set D_80409110, 0x80409110");
__asm__(".set D_80409128, 0x80409128");
extern M2C_UNK D_80409110;
extern M2C_UNK D_80409128;

typedef struct S_80020458_0 {
    M2C_UNK * unk_00;
} S_80020458_0;   /* temp_a2 in func_80020458 */

typedef struct S_80020458_1 {
    M2C_UNK * unk_00;
} S_80020458_1;   /* temp_a2_2 in func_80020458 */

void func_80020458(S_80020458_2 *arg0) {
    register S_80020458_0 *temp_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register S_80020458_1 *temp_a2_2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    temp_a2 = ((S_80020458_5 *)(arg0->unk_60))->unk_00;
    ((S_80020458_6 *)(((S_80020458_3 *)temp_a2)->unk_04))->unk_08 = 0x40;
    ((S_80020458_6 *)(((S_80020458_3 *)temp_a2)->unk_04))->unk_0A = 0x20;
    temp_a2->unk_00 = &D_80409110;
    temp_a2_2 = ((S_80020458_5 *)(arg0->unk_60))->unk_04;
    ((S_80020458_7 *)(((S_80020458_4 *)temp_a2_2)->unk_04))->unk_08 = 0xC0;
    ((S_80020458_7 *)(((S_80020458_4 *)temp_a2_2)->unk_04))->unk_0A = 0x20;
    temp_a2_2->unk_00 = &D_80409128;
}
