#include "common.h"
#include "town/scene.h"

typedef struct DevEntry {
    u16 code;
    u16 unk_02;
} DevEntry;

extern u16 D_80700716;
extern DevEntry D_80700724[];

extern s32 func_80700C7C(s32 code);
extern s32 func_80700928(s32 id);
extern void func_80700BD8(s32 code);
extern void func_80700C28(s32 code);
extern s32 func_80700A78();

/* Post the entry's code when the gates allow it and return the handler's result; otherwise check slot 0 and return the id. */
s32 post_entry_gates_allow_handler(s32 id) {
    if (func_80700C7C(D_80700716) == 0 && func_80700C7C(0x107) != 0 && func_80700928(id) != 0) {
        func_80700BD8(D_80700724[id].code);
        func_80700C28(0x107);
        return func_80700A78();
    }
    post_code_0x107_when_slot_ready(id, 0);
    return id;
}
