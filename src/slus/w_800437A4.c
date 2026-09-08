#include "common.h"

/* manual g1 strike 2: preserve the incoming second argument through the call */
#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_8003F6D4();
extern M2C_UNK D_800814F8;

/* Selects an entry offset and requests data in the shared buffer. */
M2C_UNK *func_800437A4(s16 entry_id, M2C_UNK request_arg) {
    s32 entry_offset;

    if (entry_id == 0x38) {
        entry_offset = 0x426D;
    } else if (entry_id >= 0x3A) {
        entry_offset = ((entry_id - 0x3A) * 0x2B) + 0x1BA7;
    } else {
        entry_offset = ((entry_id - 1) * 0x2B) + 0x56F0;
    }
    func_8003F6D4(0x11, request_arg, &D_800814F8, entry_offset);
    return &D_800814F8;
}
