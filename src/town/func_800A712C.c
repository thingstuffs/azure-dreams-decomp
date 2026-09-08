#include "common.h"

extern s32 D_80100E18[3];

/* p_came_set: Set the first camera position component. */
void func_800A488C(s32 position) {
    *D_80100E18 = position;
}
