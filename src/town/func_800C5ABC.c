#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad0[0x0C];
    M2C_UNK * volatile field0c;
    u8 pad10[0x40];
    M2C_UNK (* volatile callback)(void *, s32, void *);
    u8 pad54[0x10];
    s16 field64;
    u8 pad66[0x0A];
    u8 state70;
    u8 flags71;
    s16 field72;
    s16 field74;
    u8 pad76[2];
    M2C_UNK **table78;
} TargetObj;

M2C_UNK func_800C2C80(TargetObj *, void *, s32, s32);
M2C_UNK func_800C2CB0();
s32 func_800C2E1C();
s32 func_800C2F14();
extern M2C_UNK D_800D5028;
extern M2C_UNK D_800D5040;
extern M2C_UNK D_800D5058;

void func_800C321C(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_v0;
    u8 temp_v1;
    register TargetObj *obj ASM_REG("$17") = (TargetObj *)arg0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *motion = arg2;

    u32 ret;
    u32 tail_result;

    temp_v1 = obj->state70;
    if (temp_v1 == 0) {
        ret = 0x800d0000;
        ASM_KEEP_NV(ret); /* MATCH: preserve the first selection arm. */
        ret += 0x5028;
    } else if (temp_v1 == 1) {
        ret = 0x800d0000;
        ASM_KEEP_NV(ret); /* MATCH: keep the high half in the branch delay slot. */
        ret += 0x5040;
    } else {
        ret = (u32)&D_800D5058;
    }
    obj->field0c = (void *)ret;
    ASM_KEEP_NV(obj);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    obj->callback(obj, arg1, motion);
    if (!(*(u16 *)((u8 *)obj - 2) & 0x8000)) {
        temp_v0 = func_800C2E1C(obj->field72, obj->field64);
        if (obj->field74 != temp_v0) {
            func_800C2CB0(obj, motion, obj->table78[temp_v0], *(s8 *)((u8 *)motion + 4));
            obj->field74 = temp_v0;
        }
        if (!(obj->flags71 & 1)) {
            if ((func_800C2F14(obj->field72, obj->field64) << 0x10) == 0) {
                tail_result = *(u16 *)((u8 *)motion + 0x14);
                ASM_KEEP_NV(tail_result); /* MATCH: keep the first clear-bit arm separate. */
                tail_result &= 0xfffe;
                goto block_17;
            }
            goto block_16;
        }
        if ((func_800C2F14(obj->field72, obj->field64) << 0x10) != 0) {
            tail_result = *(u16 *)((u8 *)motion + 0x14);
            tail_result &= 0xfffe;
            goto block_17;
        }
block_16:
        tail_result = *(u16 *)((u8 *)motion + 0x14) | 1;
block_17:
        *(u16 *)((u8 *)motion + 0x14) = tail_result;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800C2C80(obj, motion, 0, 0);
    }
}
