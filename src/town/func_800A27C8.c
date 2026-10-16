#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townProcessEntriesInStateN19TriggersAssociatedSounds();                            /* extern */
void townProcessTableEntriesReferencedObjectsTypeHex13();                            /* extern */

/* Calls townProcessEntriesInStateN19TriggersAssociatedSounds followed by townProcessTableEntriesReferencedObjectsTypeHex13. */
void func_8009FF28(void) {
    townProcessEntriesInStateN19TriggersAssociatedSounds();
    townProcessTableEntriesReferencedObjectsTypeHex13();
}
