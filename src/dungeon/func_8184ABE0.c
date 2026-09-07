#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800243E0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800243E0_0;   /* temp_v0 in func_800243E0 */

typedef struct S_800243E0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_800243E0_1;   /* temp_s0 in func_800243E0 */

typedef struct S_800243E0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800243E0_2;   /* temp_v1 in func_800243E0 */

typedef struct S_800243E0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800243E0_3;   /* arg0 in func_800243E0 */



extern void func_80024488(void) __attribute__((noreturn));
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80024374;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;

void *func_800243E0(S_800243E0_3 *arg0) {
    S_800243E0_1 *temp_s0;
    S_800243E0_0 *temp_v0;
    S_800243E0_2 *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 == 0) {
        register void *zero ASM_REG("$2") = 0;   /* MATCH pin: retail delay-slot contents depend on it */

        ASM_TAILSLOT_PIN(zero);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80024488();
    }
    temp_v0->unk_10 = &D_80024374;
    temp_s0 = temp_v0->unk_0C;
    temp_s0->unk_0E = 0x80;
    temp_s0->unk_0D = 0x80;
    temp_s0->unk_0C = 0x80;
    func_8003DB94(temp_s0, &D_800DE870, 0);
    temp_s0->unk_1E = 0x2000;
    temp_s0->unk_1C = 0x2000;
    func_8004491C(temp_v0, &D_80045340);
    temp_v1 = temp_v0->unk_08;
    temp_v1->unk_02 = arg0->unk_02;
    temp_v1->unk_06 = arg0->unk_06;
    temp_v1->unk_0A = arg0->unk_0A;
    return temp_v0;
}
