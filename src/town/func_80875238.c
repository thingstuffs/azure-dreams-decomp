#include "common.h"


typedef struct {
    u8 pad[8];
    s32 *value;
} ValueHolder;

typedef struct {
    u8 pad[0x34];
    u32 flags;
} State;

extern ValueHolder *D_80701988[3];
extern State *D_80701968[3];

extern s32 func_80700C9C(s32 arg0);
extern void func_80700D24(s32 arg0);
extern void func_80700D54(s32 arg0);
extern void func_80701404(void);
extern void func_807012B8(void) __attribute__((noreturn));

s32 func_80875238(s32 arg0) {

    if ((func_80700C9C(1) != 0) && (*D_80701988[0]->value >= 1)) {
        func_80700D24(1);
        D_80701968[0]->flags |= 1;
        func_80701404();
        func_807012B8();
    }
    func_80700D54(1);
    return arg0;
}
