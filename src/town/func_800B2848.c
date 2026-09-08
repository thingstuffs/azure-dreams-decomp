#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AF254_arg1.h"

extern int func_80049490();
extern M2C_UNK func_800AF254();
extern M2C_UNK func_800AF448(Rec_func_800AF254_arg1 *);
extern M2C_UNK func_800AF520();
extern M2C_UNK func_800AF674();
extern M2C_UNK func_800AF784();
extern M2C_UNK func_800AF858();


typedef struct S_800AFFA8_1 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x4];
    s32 * unk_20;
} S_800AFFA8_1;   /* temp_v1 in func_800AFFA8 */

/* Runs the record handlers, then processes the selected entry. */
void func_800AFFA8(Rec_func_800AF254_arg1 *record) {
    S_800AFFA8_1 *selection;

    func_800AF448(record);
    func_800AF520(record);
    func_800AF674(record);
    func_800AF784(record);
    func_800AF254(record->unk_A8.as_s32, record);
    func_800AF858(record->unk_A8.as_s32, record);
    selection = record->unk_00;
    func_80049490(selection->unk_20[selection->unk_18]);
}
