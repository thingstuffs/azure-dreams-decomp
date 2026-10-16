#include "common.h"
#include "m2c_compat.h"

typedef struct Node8002BB08 Node8002BB08;
Node8002BB08 *initCardBootRequestObject();                /* extern */
void cardBootStopTimerAndInitServer();                            /* extern */
M2C_UNK func_800A68C0();                            /* extern */

/* Run the extra setup callback and dispatch the request in mode 2. */
void mainDispatchRequestModeTwo(s32 request) {
    func_800A68C0();
    cardBootStopTimerAndInitServer();
    initCardBootRequestObject(request, 2);
}
