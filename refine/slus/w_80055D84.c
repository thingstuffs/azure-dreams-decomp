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

/* Initializes an entry, marking it available on success or reporting an error on failure. */
void func_80055D84(s16 entry_id) {
    register s32 entry_index ASM_REG("$16") = entry_id;   /* MATCH pin: slus-diff */
    s32 index_or_error;
    index_or_error = entry_index;
    if ((s16)func_8005A778(D_80084538[index_or_error], index_or_error, D_800847C0[index_or_error]) == -1) {
        index_or_error = 0x01010000;
        goto report_error;
    }
    if ((s16)func_8005AAA8(D_80084758[index_or_error], entry_index) != -1) {
        goto activate_entry;
    }
    func_80055C50(index_or_error);
    index_or_error = 0x01020000;
report_error:
    func_8003F52C(((entry_index << 8) & 0xFF00) | index_or_error);
    return;
activate_entry:
    func_8005AC30(1);
    D_800847D0.avail |= (0x10000 << entry_index);
}
