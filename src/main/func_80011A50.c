#include "common.h"

typedef struct {
    u8 pad00[0x7C];
    s32 unk7C;
    s32 unk80;
} S_80011A50;

extern u8 D_80083E98;
extern void func_80024390(S_80011A50 *record);
extern void func_80024818(S_80011A50 *context);
extern void func_800249B4(S_80011A50 *context);

/* Dispatch to a handler based on the object's table entry and state. */
void func_80024A50(S_80011A50 *object)
{
    u8 *entry_table;
    register s32 state;

    entry_table = &D_80083E98;
    if (*(s32 *)(entry_table + (object->unk7C << 7)) != 0) {
        func_80024390(object);
        return;
    }
    state = object->unk80;
    if ((state != 0) && (state != 2)) {
        func_80024818(object);
        return;
    }
    func_800249B4(object);
}
