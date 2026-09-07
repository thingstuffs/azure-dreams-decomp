#include "common.h"
#include "m2c_compat.h"

typedef struct S_800274A8_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_800274A8_0;   /* temp_a1 in func_800274A8 */

typedef struct S_800274A8_1 {
    s32 unk_00;
    u8 pad_04[0x38];
    s32 unk_3C;
} S_800274A8_1;   /* arg0 in func_800274A8; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
void func_800274A8(void *arg0) {
    u16 temp_v1;
    S_800274A8_0 *temp_a1;

    temp_a1 = arg0 - 0x20;
    temp_v1 = temp_a1->unk_1E;
    if (temp_v1 & 0x2000) {
        temp_a1->unk_1E = (u16) (temp_v1 & 0xDFFF);
        ((S_800274A8_1 *)((u8 *)arg0 - 0x10))->unk_00 = (s32) ((S_800274A8_1 *)((u8 *)arg0 - 0x10))->unk_3C;
    }
}
