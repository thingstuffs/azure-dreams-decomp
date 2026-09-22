#include "common.h"

extern s32 func_80177C58(void);
extern u32 func_80177CF0(void);

/* Read status bit 24, or refresh and hand back the refresher's status. */
s32 func_8004111C(s32 read_status_bit) {
    if (read_status_bit != 0) {
        return (func_80177CF0() >> 0x18) & 1;
    }
    return func_80177C58();
}
