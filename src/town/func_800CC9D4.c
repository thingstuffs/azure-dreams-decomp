#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800CA75C();                            /* extern */
extern u8 D_80083498[];


typedef struct S_800CA134_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800CA134_0;   /* arg0 in func_800CA134 */

typedef struct S_800CA134_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 n; volatile u16 v; } unk_0A;   /* accessed as both */
} S_800CA134_1;   /* arg1 in func_800CA134 */

typedef struct S_800CA134_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800CA134_2;   /* target in func_800CA134 */

typedef struct S_800CA134_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800CA134_3;   /* (*(void * volatile *)((u8 *)base + (8))) in func_800CA134 */

void func_800CA134(void *arg0, void *arg1) {
    u8 *base;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_v0;

    temp_v0 = ((S_800CA134_0 *)arg0)->unk_6C - 1;
    ((S_800CA134_0 *)arg0)->unk_6C = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800CA75C();
        return;
    }
    base = D_80083498;
    var_v0 = ((S_800CA134_3 *)((*(void * volatile *)((u8 *)base + (8)))))->unk_02 - ((S_800CA134_1 *)arg1)->unk_02;
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    (*(s16 *)((u8 *)arg1 + (2))) = (s16) ((u16) ((S_800CA134_1 *)arg1)->unk_02 + (var_v0 >> 2));
    var_v0_2 = ((S_800CA134_3 *)((*(void * volatile *)((u8 *)base + (8)))))->unk_06 - ((S_800CA134_1 *)arg1)->unk_06;
    if (var_v0_2 < 0) {
        var_v0_2 += 3;
    }
    (*(s16 *)((u8 *)arg1 + (6))) = (s16) ((u16) ((S_800CA134_1 *)arg1)->unk_06 + (var_v0_2 >> 2));
    {
        void *target;
        register s32 current ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 target_value;
        register u32 current_u ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */

        target = (*(void * volatile *)((u8 *)base + (8)));
        current = ((S_800CA134_1 *)arg1)->unk_0A.n;
        target_value = ((S_800CA134_2 *)target)->unk_0A;
        current += 0xD0;
        current = target_value - current;
        ASM_KEEP(current);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        current_u = ((S_800CA134_1 *)arg1)->unk_0A.v;
        if (current < 0) {
            current += 3;
        }
        current = current_u + (current >> 2);
        ((S_800CA134_1 *)arg1)->unk_0A.n = (s16) current;
    }
}

/* MECHANISM: The retail 0x18 frame has only the $ra save; the first two interpolation
   regions fall out naturally from block-local D_80083498 liveness. The third reuses
   $v1 for pointer/target/reread and $v0 for current/difference/final sum; guarded
   pins plus a volatile final u16 reread preserve that exact load-delay schedule. */
