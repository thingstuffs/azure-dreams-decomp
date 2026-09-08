#include "common.h"

extern s8 D_8001601C[];
extern u8 D_80017774[];
extern void *D_80018034[];
extern u8 *D_8001E950[];

/* Select fixed data by mode or look up data using the current table index. */
void *func_8001B408(s32 unused_value, s32 unused_option, s32 mode)
{
    if (mode == 4) {
        return D_8001601C;
    } else if (mode == 5) {
        return D_80017774;
    } else {
        return D_80018034[D_8001E950[0][3]];
    }
}
