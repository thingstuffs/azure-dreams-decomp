#include "common.h"

typedef struct {
    u8 pad[0x34];
    u32 flags;
} State;

extern State *D_80701968[3];

extern s32 func_80700C9C(s32 arg0);
extern void func_80700D24(s32 arg0);
extern void func_80700D54(s32 arg0);
extern void func_80701604(void) __attribute__((noreturn));
extern void func_8070168C(void);


s32 func_808755AC(s32 arg0) {
    if (func_80700C9C(2) == 0) {
        s16 result;

        func_80700D54(2);
        result = arg0;
        ASM_TAILSLOT_PIN_TIED(result);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        func_80701604();
    }
    func_80700D24(2);
    D_80701968[0]->flags |= 0x10;
    func_8070168C();
}
