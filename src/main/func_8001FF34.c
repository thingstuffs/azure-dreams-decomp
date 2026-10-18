#include "common.h"

typedef struct S_8001FF34_0 {
    s32 * unk_00;
} S_8001FF34_0;   /* arg0 in func_8001FF34; pointer addresses record offset 0x10 */


void card_devkit_highlight_selected_load_slot();                            /* extern */
void func_80400908(void);                            /* extern */
extern s32 D_80406DA0;

/* Process the record data, run the follow-up routine, and set its header pointer. */
void func_8001FF34(void *record_data) {
    card_devkit_highlight_selected_load_slot(record_data);
    func_80400908();
    ((S_8001FF34_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80406DA0;
}
