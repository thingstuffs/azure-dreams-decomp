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
extern s32 func_8070168C();

/* When gate 2 and the counter both pass, set stage flag 8 and return the stage handler's result. */
s32 func_80701518(s32 entry) {

    if ((func_80700C9C(2) != 0) && (*D_80701988[0]->value >= 1)) {
        func_80700D24(2);
        D_80701968[0]->flags |= 8;
        return func_8070168C();
    }
    func_80700D54(2);
    return entry;
}
