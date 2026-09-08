#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_8001AEC8_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001AEC8_0;   /* D_80016000[0] in func_8001AEC8 */

typedef struct S_8001AEC8_1 {
    u8 pad_00[0x30C];
    M2C_UNK (*unk_30C)(M2C_UNK);
} S_8001AEC8_1;   /* ((S_8001AEC8_0 *)(D_80016000[0]))->unk_20 in func_8001AEC8 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80016000[];


void func_8001AEC8(void) {
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_8001AEC8_1 *)(((S_8001AEC8_0 *)(D_80016000[0]))->unk_20))->unk_30C(0x9000);
}
