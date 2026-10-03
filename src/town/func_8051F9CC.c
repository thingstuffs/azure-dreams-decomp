#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef void (*Callback)(s32);

typedef struct {
    s32 pad;
    s32 x;
    s32 y;
} Position;


/* Invoke the town callback with 1 and advance both position coordinates by 0x40. */
void func_800171CC(void)
{
    D_80016000->unk_20->callback_248(1);
    ((Position *)D_80016000->unk_1C)->x += 0x40;
    ((Position *)D_80016000->unk_1C)->y += 0x40;
}
