#include "common.h"

/* Canonical status block shared across the D_800847D0 family (see w_8005405C.c etc). */
typedef struct {
    u32 avail;   /* offset 0x0 */
    u32 locked;  /* offset 0x4 */
    u32 pad[1];  /* offset 0x8 - force %hi/%lo addressing (struct > 8 bytes) */
} S_800847D0;

extern S_800847D0 D_800847D0;
extern void *D_80084538[];
extern void *D_800847C0[];
extern void *D_80084758[];

extern s32 func_8005A778(void *a0, s32 a1, void *a2);
extern s32 func_8005AAA8(void *a0, s32 a1);
extern void func_80055C50(s32 a0);
extern void func_8003F52C(s32 a0);
extern void func_8005AC30(s32 a0);

/* Attempts to add an entry (D_80084538[idx]/D_800847C0[idx]) to a subsystem via
   func_8005A778; if that fails, retries via func_8005AAA8 with D_80084758[idx]
   and cancels the pending entry (func_80055C50) on further failure; reports the
   outcome (0x01/0x02 in the high byte of the composed word, idx in bits 8-15)
   to func_8003F52C. On success of the retry path, marks entry idx as available
   in D_800847D0.avail and reactivates the subsystem via func_8005AC30(1). */
void func_80055D84(s16 param_0) {
    register s32 idx ASM_REG("$16") = param_0;
    s32 flag;
    flag = idx;
    if ((s16)func_8005A778(D_80084538[flag], flag, D_800847C0[flag]) == -1) {
        flag = 0x01010000;
        goto tail;
    }
    if ((s16)func_8005AAA8(D_80084758[flag], idx) != -1) {
        goto success;
    }
    func_80055C50(flag);
    flag = 0x01020000;
tail:
    func_8003F52C(((idx << 8) & 0xFF00) | flag);
    return;
success:
    func_8005AC30(1);
    D_800847D0.avail |= (0x10000 << idx);
}
