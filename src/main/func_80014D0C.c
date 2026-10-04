#include "common.h"
#include "m2c_compat.h"

typedef struct Node8002BB08 Node8002BB08;
Node8002BB08 *func_80027AFC();                /* extern */
void func_80027C60();                            /* extern */

/* Run setup and dispatch the request in mode 1. */
void func_80027D0C(s32 request) {
    func_80027C60();
    func_80027AFC(request, 1);
}
