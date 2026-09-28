#include "common.h"
#include "shared/record_ptrs.h"

typedef struct {
    s32 pad;
    s32 x;
    s32 y;
} Position;

typedef struct {
    u8 pad[0x258];
    void (*cb258)(s32);
} CallbackTable;

typedef struct {
    u8 pad[0x1C];
    Position *position;
    CallbackTable *callbacks;
} TownState;


/* Calls the state callback with 0xC and checks whether y is between 0x401 and 0x4FF. */
s32 func_8001716C(void) {
    ((TownState *)D_80016000)->callbacks->cb258(0xC);
    return (u32)(((TownState *)D_80016000)->position->y - 0x401) < 0xFFU;
}
