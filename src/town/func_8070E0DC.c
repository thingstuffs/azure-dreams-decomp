#include "common.h"
#include "records/Rec_D_80016000.h"





typedef struct S_800170DC_1 {
    u8 pad_00[0x2F8];
    M2C_UNK (*unk_2F8)(M2C_UNK, M2C_UNK);
} S_800170DC_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_800170DC */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80016CC4();
extern M2C_UNK func_80016DBC();
extern s32 func_8001991C();
extern M2C_UNK func_80019988();
extern M2C_UNK func_8001A554();
extern M2C_UNK func_8001A5CC();
extern s32 func_8001A64C();
extern Rec_D_80016000 *D_80016000;


s32 func_800170DC(s32 arg0, M2C_UNK arg1) {
    func_80016CC4();
    func_80016DBC();
    func_8001A554(0x94B);
    if (func_8001A64C(0x943) == 0) {
        ((S_800170DC_1 *)(D_80016000->unk_20))->unk_2F8(0xE, 0x200);
        return 0;
    }
    func_80019988();
    if (func_8001991C(arg0, arg1) == 0) {
        ((S_800170DC_1 *)(D_80016000->unk_20))->unk_2F8(0xE, 0x200);
        return 0;
    }
    func_8001A5CC(0x943);
    return 1;
}
