#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef void (*Callback)(s32);

typedef struct {
    s32 pad;
    s32 x;
    s32 y;
} Position;


/* Invoke both town callbacks with 1 and shift the position by (+32, -16). */
void func_80017270(void)
{
    D_80016000->unk_20->callback_248(1);
    D_80016000->unk_20->callback_244(1);
    ((Position *)D_80016000->unk_1C)->x += 0x20;
    ((Position *)D_80016000->unk_1C)->y -= 0x10;
}
