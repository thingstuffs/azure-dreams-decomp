#include "common.h"

typedef struct {
    u8 pad0[4];
    s16 value;
    u8 pad6[6];
} Entry;

extern Entry D_8001791C[8];
extern u8 D_80017BC0[];
extern s32 func_8001E670(s32 value);

/* rowbase owner: func_8001A4F0( */
u8 func_8001A4F0(void) {
    s32 index = 0;

    if (D_80017BC0[index] != 0) {
        Entry *entries = D_8001791C;
        do {
            if (func_8001E670(entries[D_80017BC0[index]].value) != 0) {
                break;
            }
            index++;
        } while (D_80017BC0[index] != 0);
    }
    return D_80017BC0[index];
}
