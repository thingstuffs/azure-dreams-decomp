#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern void func_80016CC4(void);

/* Call func_80016CC4, then run town service callback 0x2F8 with (0xE, 0x200); returns 0. */
s32 func_80018678(void) {
    func_80016CC4();
    D_80016000->unk_20->callback_2F8(0xE, 0x200);
    return 0;
}
