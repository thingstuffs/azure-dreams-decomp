#include "modules/main_server_ship.h"
#include "common.h"

extern s32 func_80069C08(s32 card_channel);




/* Processes state 2, returning 5 on reset or advancing to state 3. */
s32 cardBootPollStateTwoTransition(void)
{
    s32 status;

    status = 0;
    if ((*(s32 (*)[])(&D_800287C8))[0] == 2) {
        cardBootDrainSoftwareEvents();
        if (func_80069C08((*(s32 *)(&D_800287CC))) == 0) {
            (*(s32 (*)[])(&D_800287C8))[0] = 0;
            status = 5;
        } else {
            (*(s32 *)(&D_800287E0)) = 0;
            (*(s32 (*)[])(&D_800287C8))[0]++;
        }
    }
    return status;
}
