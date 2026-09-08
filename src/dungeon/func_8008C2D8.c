/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() 0

extern void func_80096088(void *, void *);
extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern void func_800BCFBC(s32, s32);
extern u16 D_80083460[8];
extern s32 *D_800DD6B8[];

void func_80091A38(void *arg0, void *arg1, void *arg2, void *arg3) {
    u8 *sp;
    u8 state;
    register s32 **table ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 *row;
    u32 idx1;
    u32 idx0;
    u32 val;
    u32 bank;
    register u32 mask ASM_REG("$5");   /* MATCH pin: retail basic-block layout depends on it */
    s32 (*fn)(s32, void *, s32, s32);

    state = *((u8 *)arg0 + 0x9B);
    if (state == 0 || state == 16) {
        sp = *(u8 **)((u8 *)arg0 + 0x110);
        table = D_800DD6B8;
        mask = 0xFFFFFF;
        idx1 = sp[1] - 1;
        idx0 = sp[0] - 1;
        row = table[idx1];
        val = (u32)row[idx0];
        bank = val >> 0x18;
        fn = (s32 (*)(s32, void *, s32, s32))((val & mask) | 0x80000000);
        if (bank != 0) {
            func_800BCFBC(--bank, mask);
        }
        if (fn((s32)arg3 | 0xA0000000, sp, 0, 0) != 0) {
            *(void **)((u8 *)arg0 + 0x110) = NULL;
            *((u8 *)arg0 + 0x9B) += 1;
            return;
        }
        return;
    }
    if (state == 1) {
        func_80099F70(*(s32 *)((u8 *)arg3 + 0x5C));
        func_80099F04(*(s32 *)((u8 *)arg3 + 0x5C));
        D_80083460[1] |= 0x812;
        func_80096088(arg0, arg3);
    }
}
