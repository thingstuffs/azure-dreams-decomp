#include "common.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80016D1C_1 {
    u8 pad_00[0x1C];
    void ** unk_1C;
} S_80016D1C_1;   /* ((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_ppv.v in func_80016D1C */

typedef struct S_80016D1C_2 {
    u8 pad_00[0x40];
    s32 ** unk_40;
} S_80016D1C_2;   /* ((S_80016D1C_1 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_ppv.v))->unk_1C in func_80016D1C */



extern s8 D_80016000[];
extern s32 D_80018FE0;
extern s32 *D_8001917C;
extern s32 D_8001C328;
extern s32 D_8001C7C4;

extern s32 func_80018B5C(s32);
extern void func_80018ADC(s32);

void func_80016D1C(void) {
    D_8001917C = &D_80018FE0;
    if (func_80018B5C(0x5C2) != 0) {
        if (func_80018B5C(0x5BF) != 0) {
            ((S_80016D1C_2 *)(((S_80016D1C_1 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_ppv.v))->unk_1C))->unk_40 = &D_8001C328;
        } else {
            ((S_80016D1C_2 *)(((S_80016D1C_1 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_ppv.v))->unk_1C))->unk_40 = &D_8001C7C4;
        }
        func_80018ADC(0x5C2);
        return;
    }
    func_80018ADC(0x5C4);
}
