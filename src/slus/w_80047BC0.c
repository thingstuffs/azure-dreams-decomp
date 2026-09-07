#include "common.h"

/* struct element of D_80083D08: only the s16 field at offset 6 is read by this function */
typedef struct {
    u8 unk0[6];
    s16 unk6;
} S_80047BC0;

extern S_80047BC0 D_80083D08[6];

/* Linear search D_80083D08[0..5] for an entry whose unk6 field == arg0; return its index, or -1 if not found */
s32 func_80047BC0(s32 arg0) {
    S_80047BC0 *p;
    s32 result = -1;
    s32 i = 0;
    p = D_80083D08;

    for (; i < 6; i++, p++) {
        if (p->unk6 == arg0) {
            result = i;
            break;
        }
    }
    return result;
}
