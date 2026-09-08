/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

void func_800B3B18(u8 *arg0);                    /* extern */

typedef struct S_800B3C74_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800B3C74_0;   /* var_s0 in func_800B3C74 */

typedef struct S_800B3C74_1 {
    u8 pad_00[0x5C];
    s32 * unk_5C;
} S_800B3C74_1;   /* var_s2 in func_800B3C74 */

typedef struct S_800B3C74_2 {
    u8 pad_00[0x4];
    u8 * unk_04;
} S_800B3C74_2;   /* (s32 *)temp_v0 in func_800B3C74 */

void func_800B3C74(void *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 *table;
    s32 *entry;
    s32 var_s1;
    void *var_s2;
    void *var_s0;

    var_s2 = arg0;
    var_s1 = 2;
    var_s0 = var_s2 + 8;
loop_1:
    temp_v0 = ((S_800B3C74_0 *)var_s0)->unk_0C;
    if (temp_v0 != 0) {
        goto nonzero_count;
    }
    temp_v1 = var_s1 << 2;
    table = ((S_800B3C74_1 *)var_s2)->unk_5C;
    entry = (s32 *)(temp_v1 + (s32)table);
    temp_v0 = *entry;
    ASM_USE(temp_v1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    var_s0 += 4;
    func_800B3B18(((S_800B3C74_2 *)((s32 *)temp_v0))->unk_04);
    ASM_USE(var_s0);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_USE(var_s2);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    var_s1 += 1;
    goto check_done;

nonzero_count:
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    temp_v0--;
    ((S_800B3C74_0 *)var_s0)->unk_0C = temp_v0;
    var_s0 += 4;
    ASM_KEEP(var_s0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    var_s1 += 1;
check_done:
    if (var_s1 >= 5) {
        return;
    }
    goto loop_1;
}
