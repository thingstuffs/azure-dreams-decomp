#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

extern s32 func_80045C34();
/* Pass the buffer, value, and data to func_80045C34 and return zero. */
s32 process_linked_menu_effect(u8 *buffer, s32 value, void *data) {
    func_80045C34(buffer, value, data);
    return 0;
}
