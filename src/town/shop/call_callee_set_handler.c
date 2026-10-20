#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8009EE9C_arg0.h"

void unlink_node_if_registered(void *block_data);
extern M2C_UNK D_8009F2A8;


/* Call unlink_node_if_registered and set the record handler. */
void call_callee_80033_d_08_set_handler(Rec_func_8009EE9C_arg0 *record, s32 value) {
    unlink_node_if_registered(record);
    record->unk_50.as_pm = &D_8009F2A8;
}
