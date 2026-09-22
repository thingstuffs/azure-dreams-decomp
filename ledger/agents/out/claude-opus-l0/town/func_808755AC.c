#include "common.h"

typedef struct {
    u8 pad[0x34];
    u32 flags;
} State;

extern State *D_80701968[3];

extern s32 func_80700C9C(s32 carry_value);
extern void func_80700D24(s32 carry_value);
extern void func_80700D54(s32 carry_value);
extern void func_8070168C(void);


/* Devkit page 2: pass the value through when idle, else set the redraw flag and rescan. */
s32 func_807015AC(s32 carry_value) {
    if (func_80700C9C(2) == 0) {
        func_80700D54(2);
        return carry_value;
    }
    func_80700D24(2);
    D_80701968[0]->flags |= 0x10;
    func_8070168C();
}
