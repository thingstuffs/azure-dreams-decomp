#include "common.h"

typedef struct {
    u8 pad[0x3C];
    s32 value;
} Data1C;

typedef void (*Callback)(s32);

typedef struct {
    u8 pad[0x44];
    Callback callback;
} Data20;

typedef struct {
    u8 pad1C[0x1C];
    Data1C *data1C;
    Data20 *data20;
} State;

extern State *D_80016000;
extern s32 D_800183C8;

/* Save the state value in D_800183C8 and invoke the state callback with 0. */
void func_8065C2C4(void) {
    D_800183C8 = D_80016000->data1C->value;
    D_80016000->data20->callback(0);
}
