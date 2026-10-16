#include "common.h"

extern s32 func_80017990(s32);
extern void func_80016CD8(void);
extern void func_80016D80(s32, s32);

/* If flag 7 is set, call func_80016CD8 first; then func_80016D80(target, value). */
void func_80016550(s32 target, s32 value) {
    if (func_80017990(7) != 0) {
        func_80016CD8();
    }
    func_80016D80(target, value);
}
