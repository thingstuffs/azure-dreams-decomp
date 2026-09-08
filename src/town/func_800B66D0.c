#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800B3D84(s32);                            /* extern */
M2C_UNK func_800B3DC4();                         /* extern */

/* Runs the three update steps for an entry. */
void func_800B3E30(s32 entry_id) {
    func_800B3D84(entry_id);
    func_800B3C74(entry_id);
    func_800B3DC4(entry_id);
}
