#include "common.h"

typedef struct Struct_804B87DC_Inner {
    s32 unk_0;
    s32 unk_4;
    s32 unk_8;
} Struct_804B87DC_Inner;

typedef struct Struct_804B87DC {
    s8 pad[0x1c];
    Struct_804B87DC_Inner *inner;
} Struct_804B87DC;

extern Struct_804B87DC *D_80016000;

void func_80016FDC(void) {
    D_80016000->inner->unk_4 = 1696;
    D_80016000->inner->unk_8 = 1184;
}
