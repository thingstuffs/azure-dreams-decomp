#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800197FC();
extern M2C_UNK func_8001A554();
extern M2C_UNK func_8001A5CC();
extern s32 func_8001A64C();
extern s8 D_80016000[];
extern M2C_UNK D_8002116C;

M2C_UNK *func_80016D18(void) {
    if (func_800197FC(0xD, 6) != 0) {
        M2C_FIELD(M2C_FIELD(*(void **)D_80016000, void **, 0x20), M2C_UNK (**)(M2C_UNK), 0x78)(0);
        func_8001A554(0x92C);
        func_8001A554(0x92D);
        func_8001A554(0x92E);
        func_8001A554(0x92F);
        func_8001A554(0x930);
        func_8001A5CC(0x943);
        return &D_8002116C;
    }
    if (func_8001A64C(0x930) != 0) {
        return (M2C_UNK *)((s8 *)&D_8002116C + 0x21A);
    }
    return 0;
}
