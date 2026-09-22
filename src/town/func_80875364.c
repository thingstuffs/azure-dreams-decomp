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

extern s32 func_80700C9C(s32 entry);
extern void func_80700D24(s32 entry);
extern void func_80700D54(s32 entry);
extern s32 func_80701404();

/* When the gate and the counter both pass, set the stage flag and return the stage handler's result. */
s32 func_80875364(s32 entry) {

    if ((func_80700C9C(1) != 0) && (*D_80701988[0]->value >= 3)) {
        func_80700D24(1);
        D_80701968[0]->flags |= 4;
        return func_80701404();
    }
    func_80700D54(1);
    return entry;
}
