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
    s32 pad;
    s32 x;
    s32 y;
} Position;


/* Invoke both town callbacks with 1 and shift the position by (+32, -16). */
void func_80017270(void)
{
    ((CallbackTable *)D_80016000->unk_20)->callback1(1);
    ((CallbackTable *)D_80016000->unk_20)->callback2(1);
    ((Position *)D_80016000->unk_1C)->x += 0x20;
    ((Position *)D_80016000->unk_1C)->y -= 0x10;
}
