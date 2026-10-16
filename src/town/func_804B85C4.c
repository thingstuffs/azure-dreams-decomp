#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80019A10[];
/* Return the base address of D_80019A10. */
u8 *townGetSceneDataBase(void) {
    return D_80019A10;
}
