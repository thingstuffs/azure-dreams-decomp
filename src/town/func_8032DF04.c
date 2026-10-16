#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_8001BE60;
/* Passes the address of D_8001BE60 to townAppendShopEntry. */
void townPassGlobalRecordToHandler(void) {
    townAppendShopEntry(&D_8001BE60);
}
