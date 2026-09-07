#include "common.h"
#include "records/Rec_D_800E3D7C.h"




extern s32 func_80042900(void *, s8);
extern s32 func_80099844(void *, void *);
extern s32 func_800A48F0(void *, s8, s8);
extern u8 D_800E1C25[];

s32 func_800CD994(Rec_D_800E3D7C *arg0, s8 arg1) {
    u8 saved_byte;
    u8 current_byte;
    u8 original_byte;

    original_byte = arg0->unk_10.at03_u8.v;
    if (original_byte != 0x2E) {
        if (((original_byte != 0x1E) || ((arg0->unk_A4.at00_s32.v == 0) && (arg0->unk_AA == 0))) && ((func_80042900(arg0, 0xA) << 0x10) == 0)) {
            current_byte = arg0->unk_10.at03_u8.v;
            if ((s16)func_800A48F0(arg0, 0xA, arg1) >= 0) {
                if (arg0->unk_14.as_s32 & 0x4000) {
                    saved_byte = arg0->unk_10.at03_u8.v;
                    arg0->unk_10.at03_u8.v = current_byte;
                    func_80099844(arg0, D_800E1C25);
                    arg0->unk_10.at03_u8.v = saved_byte;
                }
            }
        }
    }
    return 0;
}
