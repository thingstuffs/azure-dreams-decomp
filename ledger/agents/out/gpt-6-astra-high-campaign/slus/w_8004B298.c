#include "common.h"

typedef struct S_8004B298_a1 {
    s32 unk00;
    s32 *unk04;
} S_8004B298_a1;

extern int D_800814A0;

/* Set the preceding and global flag bits to 0x8000 when the referenced value is zero. */
void func_8004B298(u16 *record_data, S_8004B298_a1 *value_ref) {
    if (*value_ref->unk04 == 0) {
        record_data[-1] |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
