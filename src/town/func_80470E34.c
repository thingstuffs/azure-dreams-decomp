#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct SubStruct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} SubStruct;


/* Set the substructure's unk4 and unk8 fields to 864 and 1056. */
void func_80017E34(void) {
    ((SubStruct *)D_80016000->unk_1C)->unk4 = 864;
    ((SubStruct *)D_80016000->unk_1C)->unk8 = 1056;
}
