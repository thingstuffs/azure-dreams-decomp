/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad[0x54];
    s32 (*callback)(s32);
} CallbackOwner;

extern u8 D_A0700000[0x1000];
extern CallbackOwner *D_A0700F58[4];

extern s32 func_80700304(void);
extern void func_8070049C(void) __attribute__((noreturn));
extern void func_80700590(s32, u8 *);
extern s32 func_80700DC0(s16);

typedef struct S_808B2B98_0 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_808B2B98_0;   /* temp_v1 in func_808B2B98 */

s32 func_808B2B98(s32 arg0) {
    s32 temp_v0;
    s32 temp_a0;
    s32 var_s0;
    u8 *temp_a1;
    S_808B2B98_0 *temp_v1;
    s32 temp_result;

    var_s0 = arg0;
    if (func_80700304() > 0) {
        temp_v0 = *(s16 *)(D_A0700000 + (var_s0 * 2) + 0xF34);
        temp_a0 = temp_v0;
        if (temp_v0 < 0) {
            temp_a0 = temp_v0 + 0x1F;
        }
        temp_a0 >>= 5;
        temp_a1 = *(u8 **)0xA0700F40 + temp_a0;
        temp_a0 <<= 5;
        temp_a0 = temp_v0 - temp_a0;
        *temp_a1 |= 1 << temp_a0;
        func_80700590(temp_a0, temp_a1);
        func_8070049C();
    }
    D_A0700F58[0]->callback(2);
    temp_v1 = *(void **)0xA0700F40;
    temp_v1->unk_0E = (u8) temp_v1->unk_0E;
    temp_result = func_80700DC0(*(s16 *)0xA0700F2A);
    if (temp_result == 0) {
        if (D_A0700F58[0]->callback(2) != 0) {
            var_s0 += 1;
        }
        *(s32 *)0xA0700F3C = var_s0;
        temp_v0 = var_s0;
        ASM_TAILSLOT_PIN_TIED(temp_v0);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8070049C();
    }
    {
        register s32 final_value ASM_REG("$16");   /* MATCH pin: keeps a constant in a register as retail does */
        final_value = *(s32 *)0xA0700F3C;
        ASM_KEEP(final_value);   /* MATCH pin: keeps a constant in a register as retail does */
        return final_value;
    }
}
