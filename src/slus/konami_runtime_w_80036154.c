#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80036154_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_80036154_1;   /* arg0 in func_80036154 */

typedef struct S_80036154_2 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x71];
    s8 unk_85;
} S_80036154_2;   /* ((S_80036154_1 *)arg0)->unk_74 in func_80036154 */


typedef struct S_80036154_0 {
    u8 pad_00[0x68];
    M2C_UNK * unk_68;
    u8 pad_6C[0x8];
    void * unk_74;
} S_80036154_0;   /* arg0 in func_80036154 */


M2C_UNK func_80036988();              /* extern */
extern M2C_UNK func_80036210;
extern M2C_UNK func_800362D0;
extern M2C_UNK func_800364EC;
extern M2C_UNK func_8003666C;
extern M2C_UNK func_800368D0;
extern M2C_UNK func_80038478;
extern M2C_UNK func_80038588;
extern M2C_UNK func_800385E8;
extern M2C_UNK func_80038648;
extern M2C_UNK func_80038A00;

/* Selects a handler from the linked object, initializes its data, and sets its flag. */
void func_80036154(void *object) {
    M2C_UNK *handler;
    s32 source_handler;

    source_handler = ((S_80036154_2 *)(((S_80036154_1 *)object)->unk_74))->unk_10;
    if (source_handler == &func_80038478) {
        handler = &func_80036210;
        goto set_handler;
    }
    if (source_handler == &func_80038588) {
        handler = &func_800362D0;
        goto set_handler;
    }
    if (source_handler == &func_800385E8) {
        handler = &func_800364EC;
        goto set_handler;
    }
    if (source_handler == &func_80038648) {
        handler = &func_8003666C;
        goto set_handler;
    }
    if (source_handler == &func_80038A00) {
        handler = &func_800368D0;
set_handler:
        ((S_80036154_0 *)object)->unk_68 = handler;
    }
    func_80036988(object + 0xC, ((S_80036154_0 *)object)->unk_74);
    ((S_80036154_2 *)(((S_80036154_1 *)object)->unk_74))->unk_85 = 1;
}
