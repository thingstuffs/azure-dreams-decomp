/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AAB20_0_pre {
    u16 unk_00;
} S_800AAB20_0_pre;   /* the 0x2 bytes before arg0 in func_800AAB20, addressed as arg0[-1] */

typedef struct S_800AAB20_0 {
    u8 pad_00[0x50];
    M2C_UNK (*unk_50)(void *, void *, M2C_UNK, void *);
    u8 pad_54[0x10];
    s16 unk_64;
    u8 pad_66[0xC];
    s16 unk_72;
    s16 unk_74;
    u8 pad_76[0x2];
    s32 * unk_78;
    u8 pad_7C[0x1C];
    s8 * unk_98;
} S_800AAB20_0;   /* arg0 in func_800AAB20 */

typedef struct S_800AAB20_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
} S_800AAB20_1;   /* arg2 in func_800AAB20 */


M2C_UNK func_80033D08();
void func_8003DB94();
void func_800478B8();
M2C_UNK func_8008F134();
M2C_UNK func_8009706C();
s32 func_8009CFE0();
M2C_UNK func_800AAC3C();
M2C_UNK func_800AAC48();
s32 func_800C2E1C();
s32 func_800C2F14();
extern s32 D_800814A0[3];

void func_800AAB20(void *arg0, M2C_UNK arg1, S_800AAB20_1 *arg2) {
    s32 temp_v0_2;
    s8 *temp_v0;

    if (func_8009CFE0() != 0) {
        func_8008F134(arg0);
        temp_v0 = ((S_800AAB20_0 *)arg0)->unk_98;
        if (temp_v0 != NULL) {
            *temp_v0 = 0;
        }
        func_80033D08(arg0);
        ((S_800AAB20_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800AAB20_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        return;
    }
    func_8009706C(arg1);
    ((S_800AAB20_0 *)arg0)->unk_50(arg0, arg0, arg1, arg2);
    if (!(((S_800AAB20_0_pre *)arg0)[-1].unk_00 & 0x8000)) {
        temp_v0_2 = func_800C2E1C(((S_800AAB20_0 *)arg0)->unk_72, ((S_800AAB20_0 *)arg0)->unk_64);
        if (((S_800AAB20_0 *)arg0)->unk_74 != temp_v0_2) {
            func_8003DB94(arg2, ((S_800AAB20_0 *)arg0)->unk_78[temp_v0_2], arg2->unk_04);
            ((S_800AAB20_0 *)arg0)->unk_74 = temp_v0_2;
        }
        if ((func_800C2F14(((S_800AAB20_0 *)arg0)->unk_72, ((S_800AAB20_0 *)arg0)->unk_64) << 0x10) != 0) {
            s32 tail_v0;

            tail_v0 = arg2->unk_14 | 1;
            ASM_TAILSLOT_PIN(tail_v0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_800AAC3C();
            return;
        }
        arg2->unk_14 = (u16) (arg2->unk_14 & 0xFFFE);
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_800478B8(arg2);
    }
}
