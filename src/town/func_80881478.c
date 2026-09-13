#include "common.h"


extern s32 D_80700630[];
extern u8 D_80700000[];
extern void func_807007D8(s32);
extern void func_80700868(s32);
extern void func_8070096C(s32, s32);

/* Read the selected table value between mode-one setup and completion calls. */
s32 func_80881478(void) {
    s32 entry_value;
    s32 entry_index;

    func_80700868(1);
    entry_index = D_80700630[0];
    entry_value = *(s32 *)(D_80700000 + (entry_index * 0x10) + 0x674);
    func_8070096C(entry_index, 1);
    func_807007D8(1);
    return entry_value;
}
