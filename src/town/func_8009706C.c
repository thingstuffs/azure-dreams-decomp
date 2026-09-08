#include "common.h"
#include "records/Rec_func_80094268_arg0.h"




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80094984();
extern u8 D_80093458[];
extern M2C_UNK D_800D00A0;


typedef struct S_800947CC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800947CC_1;   /* arg1 in func_800947CC */

/* Initialize an object with its handler, two settings, and a state value of 20. */
void func_800947CC(Rec_func_80094268_arg0 *object, S_800947CC_1 *settings) {
    u16 secondSetting;
    M2C_UNK *handler;

    func_80094984(&D_800D00A0, object);
    object->unk_30 = (u16) settings->unk_02;
    handler = (M2C_UNK *) D_80093458;
    secondSetting = settings->unk_06;
    object->unk_00.as_pm = handler;
    object->unk_0A.as_s16 = 0x14;
    object->unk_32 = secondSetting;
}
