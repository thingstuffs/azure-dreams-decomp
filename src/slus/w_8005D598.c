#include "common.h"

typedef struct { s32 value; s32 pad[2]; } S_8007997C;
extern S_8007997C D_8007997C;
typedef struct { s32 value; s32 pad[2]; } S_80079980;
extern S_80079980 D_80079980;
typedef struct { s32 value; s32 pad[2]; } S_80079984;
extern S_80079984 D_80079984;
typedef struct { s32 value; s32 pad[2]; } S_80079988;
extern S_80079988 D_80079988;
typedef struct { volatile u16 *ptr; u32 pad2[2]; } S_80079958;
extern S_80079958 D_80079958;

s32 func_8005D598(s32 a0, u32 a1)
{
    s32 a2 = a0;
    u32 val;

    if (D_8007997C.value != 0) {
        s32 divisor = D_80079984.value;
        if (a1 % divisor != 0) {
            a1 = a1 + divisor;
            a1 = a1 & ~D_80079988.value;
        }
    }

    val = a1 >> D_80079980.value;

    if (a2 == -2) {
        goto ret_a1;
    }
    if (a2 != -1) {
        goto do_store;
    }
    return (u16)val;

ret_a1:
    return a1;

do_store:
    D_80079958.ptr[a2] = (u16)val;
    return a1;
}
