#include "shared/runtime_dispatch.h"
#include "common.h"



typedef struct S_8006CE80 {
    u16 unk0;
    u16 unk2;
    void *unk4;
    void *unk8;
} S_8006CE80;

extern S_8006CE80 D_8006CE80[100];

extern void func_801768AC(void);
extern void func_80040B88(void);
extern void func_800411FC(u16 a0);
extern void func_800499BC(void);

/* Refreshes dispatch state and resets it unless the resulting entry has type 4. */
void func_80041818(void) {
    S_8006CE80 *dispatch_entry;

    dispatch_entry = &D_8006CE80[D_80082E60.field_B];
    func_801768AC();
    D_80082E60.unk_08 = dispatch_entry->unk2;
    func_80040B88();

    dispatch_entry = &D_8006CE80[D_80082E60.field_B];
    if (dispatch_entry->unk0 != 4) {
        func_800411FC(0);
        func_800499BC();
    }
}
