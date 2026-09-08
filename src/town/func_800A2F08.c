#include "common.h"
#include "records/Rec_func_800A0668_arg0.h"


typedef struct S_800A0668_1 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0668_1;   /* ((Rec_func_800A0668_arg0 *)arg0)->unk_98 in func_800A0668 */



extern s32 func_800A069C();

s32 func_800A0668(void *arg0) {
    if (((S_800A0668_1 *)(((Rec_func_800A0668_arg0 *)arg0)->unk_98))->unk_01 & 8) {
        return ((Rec_func_800A0668_arg0 *)arg0)->unk_95 == 0;
    }
    (void)(*(volatile u8 *)((u8 *)arg0 + 0x95) != 0);
    return func_800A069C() != 0;
}
