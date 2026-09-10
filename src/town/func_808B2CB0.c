/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

s32 func_80700304(s32, s32, s32, s32);                                /* extern */
void func_8070055C(void) __attribute__((noreturn)); /* extern */
void func_80700590();                              /* extern */

typedef struct {
    u8 pad[0x54];
    void (*callback)(s32);
} CallbackOwner;

extern s32 D_A0700000[];
__asm__(".set D_A0700000, 0xA0700000");

typedef struct S_808B2CB0_0 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_808B2CB0_0;   /* temp_v1 in func_808B2CB0 */

s32 func_808B2CB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;
    register s32 temp_a0 ASM_REG("$4");
    u8 *temp_a1;
    S_808B2CB0_0 *temp_v1;
    u8 temp_v0_2;

    if (func_80700304(arg0, arg1, arg2, arg3) >= 2) {
        temp_v0 = *(s16 *)((u8 *)D_A0700000 + (arg0 * 2) + 0xF34);
        temp_a0 = temp_v0;
        if (temp_v0 < 0) {
            temp_a0 = temp_v0 + 0x1F;
        }
        temp_a0 >>= 5;
        temp_a1 = *(u8 **)((u8 *)D_A0700000 + 0xF40) + temp_a0;
        temp_a0 = temp_v0 - (temp_a0 << 5);
        *temp_a1 |= 1 << temp_a0;
        func_80700590(temp_a0, temp_a1);
        func_8070055C();
    }

    (*(CallbackOwner **)((u8 *)D_A0700000 + 0xF58))->callback(2);
    temp_v1 = *(void **)((u8 *)D_A0700000 + 0xF40);
    temp_v0_2 = temp_v1->unk_0E;
    temp_v1->unk_0E = temp_v0_2;
    do {
        return arg0;
    } while (0);
}
