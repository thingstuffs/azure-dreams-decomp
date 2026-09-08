#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_800190C0(M2C_UNK *);
extern s32 func_80019370(void);
extern M2C_UNK func_8001ACE8(M2C_UNK);
extern s32 func_8001ADE0(M2C_UNK);
extern M2C_UNK D_8001BE5C;
extern M2C_UNK D_8001EACC;
extern M2C_UNK D_8001EBCA;

/* Select the response and set flag 0xD80 when its prerequisite passes. */
M2C_UNK *func_80018614(void) {
    if (func_8001ADE0(0xD80) == 0) {
        if (func_80019370() != 0) {
            func_8001ACE8(0xD80);
            func_800190C0(&D_8001BE5C);
            return &D_8001EACC;
        }
    }
    return &D_8001EBCA;
}
