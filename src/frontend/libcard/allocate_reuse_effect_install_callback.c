#include "common.h"
#include "main/data.h"

typedef struct { u8 pad[0x1E]; u16 flags; u8 pad20[0x20]; void *work; void *other; } Node;
extern void func_8007C040(void *, void *, s32);
extern void func_8007BEF0(s32);
extern u8 D_8040086C[], D_80400894[];
typedef struct { u8 pad[0x10]; void *callback; } Effect;
extern s32 func_80047FD8(Effect *);
extern Effect *func_8003C714(s32, Effect *, s32);
extern void memory_process_handles_and_mark_object(Effect *);
extern void func_8007BFE0(void *, s32);
extern void set_record_values(void *, void *, void *);
extern Effect D_8040C5C0;
/* Reuse or allocate a devkit effect, initialize its payload, and attach its callback. */
Effect *allocate_or_reuse_effect_and_install_callback(void *first, void *second) {
    Effect *effect = &D_8040C5C0;
    void *work = (u8 *)effect + 0x20;
    if (func_80047FD8(effect) ||
        ((effect = func_8003C714(0, effect, 0x19)) == 0 &&
         (func_8007C040(D_8040086C, D_80400894, 0x173), func_8007BEF0(1), 1))) {
        memory_process_handles_and_mark_object(effect);
        D_8040C5DE &= 0x7FFF;
        func_8007BFE0(work, 0x44);
    }
    set_record_values(work, first, second);
    effect->callback = D_804083A0;
    return effect;
}
