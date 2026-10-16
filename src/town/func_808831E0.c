#include "common.h"

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
extern void func_80700998(s32 group, s32 slot);

/* Post the entry's code when the gates allow it and return the handler's result; otherwise check slot 0 and return the id. */
s32 func_807009E0(s32 id) {
    if (func_80700C7C(D_80700716) == 0 && func_80700C7C(0x107) != 0 && func_80700928(id) != 0) {
        func_80700BD8(D_80700724[id].code);
        func_80700C28(0x107);
        return func_80700A78();
    }
    func_80700998(id, 0);
    return id;
}
