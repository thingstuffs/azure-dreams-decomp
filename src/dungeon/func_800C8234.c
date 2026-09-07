#include "common.h"

typedef struct S_800CD994_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x8C];
    s32 unk_A4;
    u8 pad_A8[0x2];
    s16 unk_AA;
} S_800CD994_0;   /* arg0 in func_800CD994 */



extern s32 func_80042900(void *, s8);
extern s32 func_80099844(void *, void *);
extern s32 func_800A48F0(void *, s8, s8);
extern u8 D_800E1C25[];

s32 func_800CD994(S_800CD994_0 *arg0, s8 arg1) {
    u8 saved_byte;
    u8 current_byte;
    u8 original_byte;

    original_byte = arg0->unk_13;
    if (original_byte != 0x2E) {
        if (((original_byte != 0x1E) || ((arg0->unk_A4 == 0) && (arg0->unk_AA == 0))) && ((func_80042900(arg0, 0xA) << 0x10) == 0)) {
            current_byte = arg0->unk_13;
            if ((s16)func_800A48F0(arg0, 0xA, arg1) >= 0) {
                if (arg0->unk_14 & 0x4000) {
                    saved_byte = arg0->unk_13;
                    arg0->unk_13 = current_byte;
                    func_80099844(arg0, D_800E1C25);
                    arg0->unk_13 = saved_byte;
                }
            }
        }
    }
    return 0;
}
