#include "common.h"
#include "m2c_compat.h"

void func_80024354(void) __attribute__((noreturn));
M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_80024224;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE8E8;

typedef struct S_800242A0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
} S_800242A0_0;   /* temp_v0 in func_800242A0 */

typedef struct S_800242A0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_800242A0_1;   /* temp_s0 in func_800242A0 */

typedef struct S_800242A0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800242A0_2;   /* temp_v1 in func_800242A0 */

typedef struct S_800242A0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800242A0_3;   /* arg1 in func_800242A0 */

void *func_800242A0(s32 arg0, S_800242A0_3 *arg1) {
    S_800242A0_1 *temp_s0;
    S_800242A0_0 *temp_v0;
    S_800242A0_2 *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 == NULL) {
        register void *zero ASM_REG("$2") = NULL;   /* MATCH pin: retail delay-slot contents depend on it */

        ASM_TAILSLOT_PIN(zero);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80024354();
    }
    temp_v0->unk_10 = &D_80024224;
    temp_s0 = temp_v0->unk_0C;
    temp_v0->unk_2C = arg0;
    temp_s0->unk_0E = 0x80;
    temp_s0->unk_0D = 0x80;
    temp_s0->unk_0C = 0x80;
    func_8003DB94(temp_s0, &D_800DE8E8, 0);
    temp_s0->unk_1E = 0x1000;
    temp_s0->unk_1C = 0x1000;
    func_8004491C(temp_v0, &D_80045340);
    temp_v1 = temp_v0->unk_08;
    temp_v1->unk_02 = (u16)arg1->unk_02;
    temp_v1->unk_06 = (u16)arg1->unk_06;
    temp_v1->unk_0A = (u16)arg1->unk_0A;
    return temp_v0;
}
