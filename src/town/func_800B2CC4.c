#include "common.h"


extern void townSetItemMenuDataPointer();
extern void townSetItemMenuSecondaryHandler();
extern s32 townInvokeItemMenuOffsetHandler();

/* Dispatch the request's payload according to its result code. */
void townDispatchItemMenuRequestResult(void *request) {
    s32 result_code;

    result_code = townInvokeItemMenuOffsetHandler(((s32 *)request)[1], ((s32 *)request)[3]);
    if (result_code == 1) {
        townSetItemMenuSecondaryHandler(((s32 *)request)[2]);
        return;
    }
    if (result_code == 2) {
        townSetItemMenuDataPointer(((s32 *)request)[2]);
        return;
    }
}
