#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80042900(void *, s8);
extern s32 func_80099844(void *, void *);
extern s32 func_800A48F0(void *, s8, s8);
extern u8 D_800E1C25[];

s32 func_800CD994(void *arg0, s8 arg1) {
    u8 saved_byte;
    u8 current_byte;
    u8 original_byte;

    original_byte = FIELD(arg0, u8, 0x13);
    if (original_byte != 0x2E) {
        if (((original_byte != 0x1E) || ((FIELD(arg0, s32, 0xA4) == 0) && (FIELD(arg0, s16, 0xAA) == 0))) && ((func_80042900(arg0, 0xA) << 0x10) == 0)) {
            current_byte = FIELD(arg0, u8, 0x13);
            if ((s16)func_800A48F0(arg0, 0xA, arg1) >= 0) {
                if (FIELD(arg0, s32, 0x14) & 0x4000) {
                    saved_byte = FIELD(arg0, u8, 0x13);
                    FIELD(arg0, u8, 0x13) = current_byte;
                    func_80099844(arg0, D_800E1C25);
                    FIELD(arg0, u8, 0x13) = saved_byte;
                }
            }
        }
    }
    return 0;
}
