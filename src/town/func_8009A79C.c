#include "shared/position_query.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

void func_80095388();                 /* extern */
s16 func_80095978();               /* extern */
void func_80095A94();      /* extern */
void func_80095C80();                      /* extern */
void func_80098B30();        /* extern */


/* Updates the record and selects a handler based on its computed threshold. */
void func_80097EFC(s32 context, EntityRec *record, s32 action_data) {
    s16 threshold;

    func_80095C80(record);
    threshold = func_80095978(record, &D_800FE488);
    if (record->z.w.i >= threshold) {
        func_80095A94(record, threshold, &D_800FE488);
        func_80098B30(context, record, action_data);
        return;
    }
    func_80095388(record, threshold);
}
