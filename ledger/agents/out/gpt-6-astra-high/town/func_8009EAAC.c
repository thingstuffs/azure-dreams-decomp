#include "common.h"

extern s32 func_800644B8(s32 arg0);
extern s32 func_80064584(s32 arg0);
extern void func_8009539C(void *arg0);
extern void func_8008F664(void *arg0, void *arg1);
extern s32 D_800834B8;
extern void *D_8009BC44;

/* Initialize heading-based motion, apply it to the object, and update the owner state. */
void func_8009C20C(void *owner, void *object, void *motion) {
    s32 *global_state = &D_800834B8;
    s32 source_z;

    *(s8 *)((u8 *)object + 0x15) = 1;
    *(s32 *)((u8 *)motion + 0xC) = func_800644B8(*(s16 *)((u8 *)global_state + 0x10)) << 6;
    *(s32 *)((u8 *)motion + 0x10) = func_80064584(*(s16 *)((u8 *)global_state + 0x10)) << 6;
    *(s32 *)((u8 *)motion + 0x14) = 0xFFF20000;
    source_z = *(s32 *)((u8 *)(*(void **)((u8 *)global_state - 0x18)) + 0x14);
    if (source_z < 0) {
        *(s32 *)((u8 *)motion + 0x14) = source_z + 0xFFF20000;
    }
    func_8009539C(motion);
    func_8008F664(object, motion);
    *(void **)((u8 *)owner + 0x50) = &D_8009BC44;
}
