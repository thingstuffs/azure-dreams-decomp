#include "common.h"

typedef struct CallbackTable {
    u8 pad_00[0x2C8];
    void (*callback)(s32, void *);
} CallbackTable;

typedef struct CallbackOwner {
    u8 pad_00[0x20];
    CallbackTable *table;
} CallbackOwner;

typedef struct DataPage {
    u8 pad_00[0x79D8];
    s32 *callback_data;
} DataPage;

extern CallbackOwner *D_80016000;
extern s32 D_80017908;

extern void func_800175FC(s32);
extern void func_80017674(s32);
extern s32 func_800176F4(s32);
extern s32 func_80017868(s32);

/* Initialize callback data, invoke the owner callback, and dispatch conditional updates. */
void func_800161D0(void)
{
    s32 zero = 0;
    DataPage *data_page = (DataPage *)0x80010000;
    register void (*callback)(s32, void *) ASM_REG("$2");
    CallbackOwner *owner;
    CallbackTable *table;

    owner = D_80016000;
    ASM_KEEP(zero);
    table = owner->table;
    callback = table->callback;
    data_page->callback_data = &D_80017908;
    callback(zero, data_page);

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
