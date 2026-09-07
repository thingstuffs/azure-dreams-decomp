/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef void (*Callback3)(M2C_UNK *, M2C_UNK *, M2C_UNK);

typedef struct S_800194E4_0 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800194E4_0;   /* arg0 in func_800194E4 */

typedef struct S_800194E4_1 {
    s16 unk_00;
    u8 pad_02[0x2];
    s32 unk_04;
} S_800194E4_1;   /* (s8 *)arg0 + var_s1 * 8 in func_800194E4 */

typedef struct S_800194E4_2 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800194E4_2;   /* root in func_800194E4 */

typedef struct S_800194E4_3 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800194E4_3;   /* (*(void **)((u8 *)D_80010000 + 0x6000)) in func_800194E4 */

typedef struct S_800194E4_4 {
    u8 pad_00[0x174];
    M2C_UNK (*unk_174)(M2C_UNK);
} S_800194E4_4;   /* ((S_800194E4_3 *)((*(void **)((u8 *)D_80010000 + 0x6000))))->unk_20 in func_800194E4 */


__asm__(".set D_80010000, 0x80010000");
extern s8 D_80010000[];
extern M2C_UNK D_80016064;
extern M2C_UNK D_8001608C;

s32 func_800194E4(void *arg0, s32 arg1) {
    s32 var_s1;
    Callback3 callback;
    void *root;
    void *callbacks;

    var_s1 = 0;
    if (((S_800194E4_0 *)arg0)->unk_04 != 0) {
loop_2:
        if (((S_800194E4_1 *)((s8 *)arg0 + var_s1 * 8))->unk_00 != arg1) {
            var_s1 += 1;
            if (((S_800194E4_1 *)((s8 *)arg0 + var_s1 * 8))->unk_04 != 0) {
                goto loop_2;
            }
        }
        if (((S_800194E4_1 *)((s8 *)arg0 + var_s1 * 8))->unk_04 == 0) {
            goto block_5;
        }
    } else {
block_5:
        do { root = (*(void **)((u8 *)D_80010000 + 0x6000)); } while (0);
        do { callbacks = ((S_800194E4_2 *)root)->unk_20; } while (0);
        callback = (*(Callback3 *)((u8 *)callbacks + 0x168));
        callback(&D_80016064, &D_8001608C, 0x28);
        ((S_800194E4_4 *)(((S_800194E4_3 *)((*(void **)((u8 *)D_80010000 + 0x6000))))->unk_20))->unk_174(1);
    }
    return var_s1;
}
