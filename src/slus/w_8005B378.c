#include "common.h"

#include "common.h"

extern s32 func_8005DA88(s32 *arg0);
extern s8 D_8007382B[9];

/* Submit a value and record it when the request succeeds. */
s16 func_8005B378(s16 value)
{
    s32 request[6];

    request[0] = 1;
    request[1] = value;
    if (func_8005DA88(request) != 0) {
        return -1;
    }
    D_8007382B[0] = value;
    return value;
}
