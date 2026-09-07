#include "common.h"

typedef struct S_800A0668_0 {
    u8 pad_00[0x95];
    u8 unk_95;
    u8 pad_96[0x2];
    void * unk_98;
} S_800A0668_0;   /* arg0 in func_800A0668 */

typedef struct S_800A0668_1 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0668_1;   /* ((S_800A0668_0 *)arg0)->unk_98 in func_800A0668 */



extern s32 func_800A069C();

s32 func_800A0668(void *arg0) {
    if (((S_800A0668_1 *)(((S_800A0668_0 *)arg0)->unk_98))->unk_01 & 8) {
        return ((S_800A0668_0 *)arg0)->unk_95 == 0;
    }
    (void)(*(volatile u8 *)((u8 *)arg0 + 0x95) != 0);
    return func_800A069C() != 0;
}
