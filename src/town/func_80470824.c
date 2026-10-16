#include "modules/town_ovl_3ef1c8.h"

s32 townInitializeIndexedEntryOnFirst479(S_80017824_0 *obj, s32 index) {
    s32 offset;
    S_80017824_1 *entry;

    if ((func_8001A510(0x479) == 0) && (townCheckInteraction13Type3() != 0)) {
        func_8001A418(0x479);
        offset = index * 0x10;
        ((S_80017824_2 *)((offset + obj->unk_10)))->handler = townSelectInteractionResultWithRefresh;
        entry = offset + obj->unk_10;
        entry->unk_08 = &D_8001B718;
        townMarkProgressStateReady();
    }
    return 0;
}
