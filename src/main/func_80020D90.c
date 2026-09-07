#include "common.h"
#include "m2c_compat.h"

typedef struct S_80020D90_0 {
    s32 unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
    u8 pad_10[0x2C];
    s32 unk_3C;
} S_80020D90_0;   /* arg0 in func_80020D90; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
void func_80020D90(void *arg0) {
    u16 temp_a1;

    temp_a1 = ((S_80020D90_0 *)((u8 *)arg0 - 0x10))->unk_0E;
    if (temp_a1 & 0x2000) {
        ((S_80020D90_0 *)((u8 *)arg0 - 0x10))->unk_0E = (u16) (temp_a1 & 0xDFFF);
        ((S_80020D90_0 *)((u8 *)arg0 - 0x10))->unk_00 = (s32) ((S_80020D90_0 *)((u8 *)arg0 - 0x10))->unk_3C;
    }
}
