#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct CallbackTable {
    u8 pad_00[0x2C8];
    s32 (*callback)(s32);
} CallbackTable;

extern s32 D_80017908;
extern s32 *D_800179D8;

extern void func_800175FC(s32);
extern void func_80017674(s32);
extern s32 func_800176F4(s32);
extern s32 func_80017868(s32);

/* Initialize callback data, invoke the owner callback, and dispatch conditional updates. */
void func_800161D0(void)
{
    s32 zero = 0;
    s32 (*callback)(s32);
    Rec_D_80016000 *owner;
    CallbackTable *table;

    owner = D_80016000;
    table = ((CallbackTable *)owner->unk_20);
    callback = table->callback;
    D_800179D8 = &D_80017908;
    callback(zero);

    if (func_800176F4(0x942) != 0) {
        if (func_80017868(0xB) != 0) {
            func_800175FC(0xB0F);
            if (func_800176F4(0xB10) != 0) {
                goto final;
            }
        } else {
            func_80017674(0xB0F);
        }
        func_800175FC(0xB0E);
        return;
    }

final:
    func_80017674(0xB0E);
}
