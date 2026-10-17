#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"

extern int func_80049490();
extern void townPopulateItemMenuPageEntries();
extern void townUpdateItemMenuEnabledRecord(Rec_func_800AF254_arg1 *);
extern void townPopulateItemMenuLowerEntries();
extern void townPopulateCurrentItemMenuPage();
extern void townUpdateItemMenuPageBounds();
extern void townItemMenuNoOp();


typedef struct S_800AFFA8_1 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x4];
    s32 * unk_20;
} S_800AFFA8_1;

/* Runs the record handlers, then processes the selected entry. */
void townProcessItemMenuSelectedEntry(Rec_func_800AF254_arg1 *record) {
    S_800AFFA8_1 *selection;

    townUpdateItemMenuEnabledRecord(record);
    townPopulateItemMenuLowerEntries(record);
    townPopulateCurrentItemMenuPage(record);
    townUpdateItemMenuPageBounds(record);
    townPopulateItemMenuPageEntries(record->unk_A8.as_s32, record);
    townItemMenuNoOp(record->unk_A8.as_s32, record);
    selection = record->unk_00;
    func_80049490(selection->unk_20[selection->unk_18]);
}
