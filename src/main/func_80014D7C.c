#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

typedef struct Node8002BB08 Node8002BB08;
Node8002BB08 *initCardBootRequestObject();                /* extern */
void cardBootStopTimerAndInitServer();                            /* extern */
M2C_UNK func_80064F00();            /* extern */
M2C_UNK func_80064F20();                     /* extern */

/* Set up the request with scale 512 and center (160, 120), then dispatch in mode 0. */
void func_80027D7C(s32 request) {
    cardBootStopTimerAndInitServer();
    gameWork.view.unk_088 = 0x200;
    func_80064F20(0x200);
    func_80064F00(0xA0, 0x78);
    initCardBootRequestObject(request, 0);
}
