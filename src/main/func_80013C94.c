#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026C94_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80026C94_3;   /* temp_a2 in func_80026C94 */

typedef struct S_80026C94_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80026C94_4;   /* temp_a2_2 in func_80026C94 */

typedef struct S_80026C94_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80026C94_5;   /* ((S_80026C94_3 *)temp_a2)->unk_04 in func_80026C94 */

typedef struct S_80026C94_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_80026C94_6;   /* ((S_80026C94_4 *)temp_a2_2)->unk_04 in func_80026C94 */

__asm__(".set D_80028418, 0x80028418");
__asm__(".set D_80028430, 0x80028430");
extern M2C_UNK D_80028418;
extern M2C_UNK D_80028430;

typedef struct S_80026C94_0 {
    u8 pad_00[0x60];
    void * unk_60;
    void * unk_64;
} S_80026C94_0;   /* arg0 in func_80026C94 */

typedef struct S_80026C94_1 {
    M2C_UNK * unk_00;
} S_80026C94_1;   /* temp_a2 in func_80026C94 */

typedef struct S_80026C94_2 {
    M2C_UNK * unk_00;
} S_80026C94_2;   /* temp_a2_2 in func_80026C94 */

void func_80026C94(S_80026C94_0 *arg0) {
    register S_80026C94_1 *temp_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register S_80026C94_2 *temp_a2_2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    temp_a2 = arg0->unk_60;
    ((S_80026C94_5 *)(((S_80026C94_3 *)temp_a2)->unk_04))->unk_08 = 0x40;
    ((S_80026C94_5 *)(((S_80026C94_3 *)temp_a2)->unk_04))->unk_0A = 0x20;
    temp_a2->unk_00 = &D_80028418;
    temp_a2_2 = arg0->unk_64;
    ((S_80026C94_6 *)(((S_80026C94_4 *)temp_a2_2)->unk_04))->unk_08 = 0xC0;
    ((S_80026C94_6 *)(((S_80026C94_4 *)temp_a2_2)->unk_04))->unk_0A = 0x20;
    temp_a2_2->unk_00 = &D_80028430;
}
