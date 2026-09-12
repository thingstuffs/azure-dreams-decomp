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

/* Selects state data, invokes the object callback, and updates motion data and flags. */
void func_800C321C(s32 obj_addr, s32 callback_arg, void *motion_data) {
    s32 table_index;
    u8 state;
    register TargetObj *obj ASM_REG("$17") = (TargetObj *)obj_addr;
    void *motion = motion_data;

    u32 state_data;
    u32 motion_flags;

    state = obj->state70;
    if (state == 0) {
        state_data = 0x800d0000;
        ASM_KEEP_NV(state_data);
        state_data += 0x5028;
    } else if (state == 1) {
        state_data = 0x800d0000;
        ASM_KEEP_NV(state_data);
        state_data += 0x5040;
    } else {
        state_data = (u32)&D_800D5058;
    }
    obj->field0c = (void *)state_data;
    ASM_KEEP_NV(obj);
    obj->callback(obj, callback_arg, motion);
    if (!(*(u16 *)((u8 *)obj - 2) & 0x8000)) {
        table_index = func_800C2E1C(obj->field72, obj->field64);
        if (obj->field74 != table_index) {
            func_800C2CB0(obj, motion, obj->table78[table_index], *(s8 *)((u8 *)motion + 4));
            obj->field74 = table_index;
        }
        if (!(obj->flags71 & 1)) {
            if ((func_800C2F14(obj->field72, obj->field64) << 0x10) == 0) {
                motion_flags = (u16)(*(u16 *)((u8 *)motion + 0x14) & 0xfffe);
                goto store_motion_flags;
            }
            goto set_motion_flag;
        }
        if ((func_800C2F14(obj->field72, obj->field64) << 0x10) != 0) {
            motion_flags = *(u16 *)((u8 *)motion + 0x14);
            motion_flags &= 0xfffe;
            goto store_motion_flags;
        }
set_motion_flag:
        motion_flags = *(u16 *)((u8 *)motion + 0x14) | 1;
store_motion_flags:
        *(u16 *)((u8 *)motion + 0x14) = motion_flags;
        func_800C2C80(obj, motion, 0, 0);
    }
}
