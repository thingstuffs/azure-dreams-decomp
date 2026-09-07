#include "common.h"

/* D_80082E6A: standalone byte global, declared >8B to force %hi/%lo
 * addressing (matches src/w_80047694.c sibling; same symbol, same form). */
struct S_80082E6A {
    u8 field_0;
    u8 pad[11];
};
extern struct S_80082E6A D_80082E6A;

/* D_800D1790: forced >8B so a plain value load also uses %hi/%lo. */
extern volatile s32 D_800D1790[2];

extern s32 func_800A652C(void);

s32 func_800B5D30(void) {
    if (D_80082E6A.field_0 == 1) {
        D_800D1790[0];
        return;
    }
    return func_800A652C();
}
