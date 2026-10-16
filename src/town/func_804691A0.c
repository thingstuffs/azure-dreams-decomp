/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

void copyTownRecordPairFields();


/* Pass the callback-selected table value to the destination handler. */
void townCopyCallbackValueToDestination(s32 destination, s32 *values) {
    copyTownRecordPairFields(destination, *((D_80016000->unk_20->callback_2D4(0)) + values));
}
