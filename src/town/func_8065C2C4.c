#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct {
    u8 pad[0x3C];
    s32 value;
} Data1C;

typedef void (*Callback)(s32);

typedef struct {
    u8 pad[0x44];
    Callback callback;
} Data20;

extern s32 D_800183C8;

/* Save the state value in D_800183C8 and invoke the state callback with 0. */
void func_8065C2C4(void) {
    D_800183C8 = ((Data1C *)D_80016000->unk_1C)->value;
    ((Data20 *)D_80016000->unk_20)->callback(0);
}
