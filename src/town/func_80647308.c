#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef s32 M2C_UNK;
typedef struct {
    u8 pad[0x28C];
    M2C_UNK (*func)(M2C_UNK);
} CallTable;

extern M2C_UNK D_80017A34;
extern M2C_UNK *D_80017B3C;

/* Point D_80017B3C at D_80017A34 and invoke the state callback with 2. */
void func_80647308(void) {
    D_80017B3C = &D_80017A34;
    ((CallTable *)D_80016000->unk_20)->func(2);
}
