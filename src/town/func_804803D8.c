#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


M2C_UNK func_80016A38();
void advanceTownEventsAndDispatchEntry();
extern M2C_UNK D_80019440;
extern s32 D_80019540;

/* Prepare D_80019440 for the callback and store its result in D_80019540. */
void func_800163D8(void) {
    advanceTownEventsAndDispatchEntry(&D_80019440, 0x100);
    func_80016A38(&D_80019440);
    D_80019540 = D_80016000->unk_20->callback_068(0, 1, 2, &D_80019440);
}
