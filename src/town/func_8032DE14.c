#include "common.h"

typedef struct Copy4 {
    u8 bytes[4];
} Copy4;

extern void func_800190C0(const Copy4 *);
extern s32 func_80019370(void);
extern void func_8001ACE8(s32);
extern s32 func_8001ADE0(s32);
extern Copy4 D_8001BE5C;
extern s32 D_8001EACC;
extern s32 D_8001EBCA;

/* Select the response and set flag 0xD80 when its prerequisite passes. */
s32 *func_80018614(void) {
    if (func_8001ADE0(0xD80) == 0) {
        if (func_80019370() != 0) {
            func_8001ACE8(0xD80);
            func_800190C0(&D_8001BE5C);
            return &D_8001EACC;
        }
    }
    return &D_8001EBCA;
}
