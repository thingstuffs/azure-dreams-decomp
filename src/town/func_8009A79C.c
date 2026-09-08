#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_80095388();                 /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
M2C_UNK func_80098B30();        /* extern */
extern M2C_UNK D_800FE488;


/* Updates the record and selects a handler based on its computed threshold. */
void func_80097EFC(s32 context, Rec_D_800E3D7C *record, M2C_UNK action_data) {
    s16 threshold;

    func_80095C80(record);
    threshold = func_80095978(record, &D_800FE488);
    if (record->unk_08.at02_s16.v >= threshold) {
        func_80095A94(record, threshold, &D_800FE488);
        func_80098B30(context, record, action_data);
        return;
    }
    func_80095388(record, threshold);
}
