#include "common.h"

typedef s32 M2C_UNK;
typedef struct {
    u8 pad[0x20];
    void *ptr;
} State;
typedef struct {
    u8 pad[0x28C];
    M2C_UNK (*func)(M2C_UNK);
} CallTable;

extern State *D_80016000;
extern M2C_UNK D_80017A34;
extern M2C_UNK *D_80017B3C;

void func_80647308(void) {
    D_80017B3C = &D_80017A34;
    ((CallTable *)D_80016000->ptr)->func(2);
}
