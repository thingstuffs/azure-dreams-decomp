#include "common.h"
#include "shared/record_ptrs.h"

typedef struct SubStruct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} SubStruct;

typedef struct MainStruct {
    s8 pad[0x1C];
    SubStruct *sub;
} MainStruct;


/* Set the substructure's unk4 and unk8 fields to 864 and 1056. */
void func_80017E34(void) {
    ((MainStruct *)D_80016000)->sub->unk4 = 864;
    ((MainStruct *)D_80016000)->sub->unk8 = 1056;
}
