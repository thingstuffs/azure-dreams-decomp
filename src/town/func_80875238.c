#include "common.h"

#ifdef NON_MATCHING
#define ASM_UNDEF(var) ((var) = 0)
#else
#endif

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
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

    if ((func_80700C9C(zero | 1) != 0) && (*D_80701988[0]->value >= 1)) {
        ASM_UNDEF(zero);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        func_80700D24(zero | 1);
        D_80701968[0]->flags |= 1;
        func_80701404();
        func_807012B8();
    }
    func_80700D54(zero | 1);
    return arg0;
}
