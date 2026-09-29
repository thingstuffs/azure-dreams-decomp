#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef void (*Callback)(s32);

typedef struct {
    u8 pad[0x244];
    Callback callback2;
    Callback callback1;
} CallbackTable;

typedef struct {
    s32 state;
    s32 value;
} StateEntry;


/* Invoke both town callbacks and subtract 0x30 from the entry value in state 3. */
s32 func_80017150(void)
{
    ((CallbackTable *)D_80016000->unk_20)->callback1(1);
    ((CallbackTable *)D_80016000->unk_20)->callback2(1);
    if (((StateEntry *)D_80016000->unk_1C)->state == 3) {
        ((StateEntry *)D_80016000->unk_1C)->value -= 0x30;
        return 1;
    }
    return 0;
}
