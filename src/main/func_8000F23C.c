#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"


/* Call cardBootEraseSlotFile with argument 5. */
void cardBootEraseTemporaryFile(void) {
    cardBootEraseSlotFile(5);
}
