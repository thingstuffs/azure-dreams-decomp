#include "common.h"

extern void *D_800E3D7C[];
extern u8 D_80083780[];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern u8 D_80083460[];
extern u8 D_800C152C[];
extern u8 D_800DF514[];
extern u8 D_800E14A6[];

s32 func_80098864(s32, s32);
void func_8008D344(void *, void *, void *, s32);
void func_800A6480(void *, s32);
s32 func_800AD6FC(void *, s32, s32);
void func_800A5F38(void *, s32);
s32 func_800BBA40(u32, u32, s32, void *, s32, s32, void *);
void func_800997FC(void *);
void func_80098B38(s32);

/* Dispatches a target action according to its type and address. */
s32 func_800C15B4(void *target, s32 action_id, s16 action_type, s32 action_arg) {
    void *target_data;
    u8 *counter_state;

    if (action_type == 0xD) {
        return func_80098864(action_id, action_arg);
    }
    if (target == D_800E3D7C[0]) {
        *(s32 *)((u8 *)target + 0x110) = action_id;
        func_8008D344(target, D_80083780, D_80082E80, 0);
        return 0;
    }
    if ((u32)target <= 0x9FFFFFFFU) {
        func_800A6480(target, action_id);
        if (func_800AD6FC(target, D_800DDE84[*(u8 *)((u8 *)target + 0x13)] & 3, action_id) == 0) {
            func_800A5F38(target, action_id);
            return 1;
        }
        counter_state = D_80083460;
        *(u16 *)(counter_state + 10) = *(u16 *)(counter_state + 10) - 1;
        goto finish_action;
    }
    target_data = *(void **)((u8 *)target - 0x14);
    if (func_800BBA40(*(u8 *)((u8 *)target_data + 0x24), *(u8 *)((u8 *)target_data + 0x25), *(s16 *)((u8 *)target + 0x88), &D_800DF514, 0x2800, 0x802020, &D_800C152C) == 0) {
        return 0;
    }
    func_800997FC(&D_800E14A6);
finish_action:
    func_80098B38(action_id);
    return 1;
}
