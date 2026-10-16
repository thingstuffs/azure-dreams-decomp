#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"


typedef struct S_800AFD00_1 {
    u8 pad_00[0x98];
    s32 unk_98;
    s32 unk_9C;
} S_800AFD00_1;   /* ((Rec_func_800AF254_arg1 *)arg0)->unk_A8.as_pv in townResetItemMenuEntityState */


M2C_UNK func_800497F4();                /* extern */
s32 advanceTimedTaggedStream();                         /* extern */
void townUpdateItemMenuSelection();                      /* extern */


/* Reset the entity sub-object and its two linked handles, then finalize the update. */
void townResetItemMenuEntityState(void *entity) {
    advanceTimedTaggedStream(entity + 0x1C);
    func_800497F4(((S_800AFD00_1 *)(((Rec_func_800AF254_arg1 *)entity)->unk_A8.as_pv))->unk_98, 0);
    func_800497F4(((S_800AFD00_1 *)(((Rec_func_800AF254_arg1 *)entity)->unk_A8.as_pv))->unk_9C, 0);
    townUpdateItemMenuSelection(entity);
}
