#include "common.h"

typedef struct {
    u8 pad[0x34];
    u32 flags;
} State;

extern State *D_80701968[3];

extern s32 func_80700C9C(s32 arg0);
extern void func_80700D24(s32 arg0);
extern void func_80700D54(s32 arg0);
extern void func_8070168C(void);


s32 func_807015AC(s32 arg0) {
    if (func_80700C9C(2) == 0) {
        func_80700D54(2);
        return arg0;
    }
    func_80700D24(2);
    D_80701968[0]->flags |= 0x10;
    func_8070168C();
}
