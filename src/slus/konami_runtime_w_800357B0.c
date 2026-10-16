#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800357B0_0 {
    u8 pad_00[0x50];
    u16 unk_50;
    u8 pad_52[0x16];
    M2C_UNK * unk_68;
} S_800357B0_0;   /* arg0 in runtimeAssignCode101Callback */


void runtimeAdvanceCounterAndCallback();

/* Assigns runtimeAdvanceCounterAndCallback to objects with code 0x101. */
void runtimeAssignCode101Callback(S_800357B0_0 *object) {
    if (object->unk_50 == 0x101) {
        object->unk_68 = &runtimeAdvanceCounterAndCallback;
    }
}
