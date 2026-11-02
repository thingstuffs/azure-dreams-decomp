#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Process the two embedded records at offsets 4 and 0x10. */
void card_dev_init_two_rows(s32 record_addr) {
    func_8004DCCC(record_addr + 4);
    func_8004DCCC(record_addr + 0x10);
}
