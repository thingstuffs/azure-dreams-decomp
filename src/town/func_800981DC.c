#include "common.h"

typedef struct {
    u8 pad0[0x10];
    void *field10;
} FuncArg;

typedef struct {
    u8 pad0[0x14];
    u8 field14;
} FuncData;

s32 func_8009593C(FuncArg *arg0) {
    FuncData *data;

    data = arg0->field10;
    if (data == 0) {
        return 0;
    }
    if ((data->field14 == 1) || (data->field14 == 3)) {
        return 1;
    }
    return 0;
}
