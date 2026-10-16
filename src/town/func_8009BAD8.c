#include "common.h"
#include "m2c_compat.h"

void townCallTheHandlerSelectsNonzeroEntry();              /* extern */
void townSetPlayerTravelTiming();       /* extern */
extern M2C_UNK D_800D0130;

/* Initialize the record from fixed data and apply its update parameters. */
void townInitializeRecordWithUpdateParameters(s32 record, s32 update_value, s32 init_context) {
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0130, record, init_context);
    townSetPlayerTravelTiming(record, update_value, init_context);
}
