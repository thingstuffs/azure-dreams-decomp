#include "common.h"
#include "m2c_compat.h"

typedef struct Node8002BB08 Node8002BB08;
Node8002BB08 *initCardBootRequestObject();                /* extern */
void cardBootStopTimerAndInitServer();                            /* extern */

/* Run setup and dispatch the request in mode 1. */
void cardBootOpenSaveSlotSelection(s32 request) {
    cardBootStopTimerAndInitServer();
    initCardBootRequestObject(request, 1);
}
