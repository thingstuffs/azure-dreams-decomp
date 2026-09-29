#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct {
    s32 pad;
    s32 x;
    s32 y;
} Position;

typedef struct {
    u8 pad[0x258];
    void (*cb258)(s32);
} CallbackTable;


/* Calls the state callback with 0xC and checks whether y is between 0x401 and 0x4FF. */
s32 func_8001716C(void) {
    ((CallbackTable *)D_80016000->unk_20)->cb258(0xC);
    return (u32)(((Position *)D_80016000->unk_1C)->y - 0x401) < 0xFFU;
}
