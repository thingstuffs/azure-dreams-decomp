#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef void (*Callback)(s32);

typedef struct {
    s32 state;
    s32 value;
} StateEntry;


/* Invoke both town callbacks and subtract 0x30 from the entry value in state 3. */
s32 func_80017150(void)
{
    D_80016000->unk_20->callback_248(1);
    D_80016000->unk_20->callback_244(1);
    if (((StateEntry *)D_80016000->unk_1C)->state == 3) {
        ((StateEntry *)D_80016000->unk_1C)->value -= 0x30;
        return 1;
    }
    return 0;
}
