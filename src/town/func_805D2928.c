#include "common.h"

extern s32 func_800161D8();
extern s32 func_80016228();
typedef struct {
    s32 value;
    s32 pad[2];
} Global32;

extern Global32 D_8001967C;
extern Global32 D_80019AFC;

void func_80016928(void) {
    D_8001967C.value = 2;
    if (3 == D_80019AFC.value) {
        func_80016228();
        return;
    }
    func_800161D8();
}
