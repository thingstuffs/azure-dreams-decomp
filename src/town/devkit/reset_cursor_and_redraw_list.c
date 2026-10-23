/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

extern s32 devkit_cursor_state[];
extern s32 D_80700630_return[];
extern void func_80700868(s32);
extern s32 scan_table_entry_query_rejects(void);
extern void func_80700BCC(void);
extern void func_80700ED8(s32, s32);


/* Devkit scene step: reset the cursor, rebuild the list, latch its length and redraw. */
s32 reset_cursor_and_redraw_list(void) {
    s32 list_length;

    func_80700868(0);
    func_80700BCC();
    list_length = scan_table_entry_query_rejects();
    devkit_cursor_state[0] = list_length;
    func_80700ED8(list_length, devkit_cursor_state[1]);
    return D_80700630_return[0];
}
