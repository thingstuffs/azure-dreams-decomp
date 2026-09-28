#include "common.h"
#include "shared/record_ptrs.h"

typedef struct {
    s32 unk_0;
    s32 unk_4;
    s32 unk_8;
} StructB;

typedef struct {
    s32 pad[7];
    StructB *unk_1c;
} StructA;


/* Set the linked structure's two values to 1248 and 1184. */
void func_8001707C(void) {
    ((StructA *)D_80016000)->unk_1c->unk_4 = 1248;
    ((StructA *)D_80016000)->unk_1c->unk_8 = 1184;
}
