#include "common.h"

/* manual g1 strike 2: preserve the incoming second argument through the call */
#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_8003F6D4();
extern M2C_UNK D_800814F0;

/* Builds and returns a shared descriptor for the record ID and packed value. */
M2C_UNK *func_80043704(s16 record_id, M2C_UNK packed_value) {
    M2C_UNK count;
    s32 offset;

    if (record_id == 0x38) {
        offset = 0x421F;
        count = 0x4E;
    } else {
        if (record_id >= 0x3A) {
            offset = ((record_id - 0x3A) * 0x2B) + 0x1B8D;
        } else {
            offset = ((record_id - 1) * 0x2B) + 0x56D6;
        }
        count = 0x1A;
    }
    func_8003F6D4(count, packed_value, &D_800814F0, offset);
    return &D_800814F0;
}
