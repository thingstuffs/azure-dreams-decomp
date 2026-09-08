#include "common.h"
#include "records/Rec_D_80016000.h"





typedef struct S_80018544_1 {
    u8 pad_00[0x78];
    M2C_UNK (*unk_78)(M2C_UNK);
} S_80018544_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80018544 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_80019A34(s32, s32);
extern void func_80019BC0(void);
extern void func_80019DFC(void *, void *, s32, s32);
extern void func_8001ACE8(s32);
extern s32 func_8001ADE0(s32);
extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_8001BE2C;
extern M2C_UNK D_8001BE44;
extern M2C_UNK D_8001C354;


/* Handles the conditional callback and selects data according to flag 0x1460. */
void func_80018544(s32 context, s32 unused, s32 event_code) {
    void *selected_data;

    if ((event_code == 0x1E) && (func_80019A34(0xD, 1) != 0)) {
        ((S_80018544_1 *)(D_80016000->unk_20))->unk_78(0);
        func_8001ACE8(0x1460);
        func_80019BC0();
    }

    if (func_8001ADE0(0x1460) != 0) {
        selected_data = &D_8001BE2C;
    } else {
        selected_data = &D_8001BE44;
    }
    func_80019DFC(selected_data, &D_8001C354, context, event_code);
}
