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

extern void func_80016258(void) __attribute__((noreturn));
extern void func_80016260(void) __attribute__((noreturn));
extern void func_800175FC(s32);
extern void func_80017674(s32);
extern s32 func_800176F4(s32);
extern s32 func_80017868(s32);

void func_800161D0(void)
{
    register s32 zero ASM_REG("$4") = 0;
    register DataPage *page ASM_REG("$5") = (DataPage *)0x80010000;
    register void (*callback)(s32, void *) ASM_REG("$2");
    CallbackOwner *owner;
    CallbackTable *table;

    owner = D_80016000;
    ASM_KEEP(zero);
    ASM_KEEP(page);
    table = owner->table;
    callback = table->callback;
    page->callback_data = &D_80017908;
    callback(zero, page);

    if (func_800176F4(0x942) == 0) {
        goto final;
    }
    if (func_80017868(0xB) == 0) {
        goto alternate;
    }
    func_800175FC(0xB0F);
    if (func_800176F4(0xB10) == 0) {
        goto shared;
    }
    func_80016258();

alternate:
    func_80017674(0xB0F);

shared:
    func_800175FC(0xB0E);
    func_80016260();

final:
    func_80017674(0xB0E);
}
