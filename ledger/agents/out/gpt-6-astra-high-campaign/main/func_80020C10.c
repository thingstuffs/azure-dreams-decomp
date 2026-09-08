#include "common.h"

extern u8 D_804007D8[];
extern u8 D_80400800[];
extern u8 D_8040861C[];

extern s32 func_80047FD8(void *arg0);
extern void *func_8003C714(s32 arg0, void *arg1, s32 arg2);
extern void func_80040560(void *arg0, void *arg1);
extern void func_8007BEF0(s32 arg0);
extern void func_8007BFE0(void *arg0, s32 arg1);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_80403D24(void *arg0);
extern s32 func_80407AEC(void *arg0);
extern void func_80407B14(void *arg0, s32 arg1);
extern void func_80407BD0(void *arg0, s32 arg1);
extern s32 func_80407CC4(void *arg0);

typedef struct {
    u8 unk_00[0x0C];
    u32 field_0C;
} Obj;

typedef struct {
    u8 unk_00[0xEC];
    u32 field_EC;
} Sub;

typedef struct {
    u8 unk_00[0x1E];
    u16 flags;
    u8 unk_20[0x100];
} Root;

extern Root D_8040C420;

/* Initializes the memory card state object and its working data. */
s32 func_80020C10(s32 init_option) {
    Obj *obj = (Obj *)&D_8040C420;
    Sub *card_state = (Sub *)((u8 *)obj + 0x20);
    void *allocated_obj;
    s32 state_value;

    if (func_80047FD8(obj) == 0) {
        allocated_obj = func_8003C714(0, obj, 0x68);
        if (allocated_obj == 0) {
            func_8007C040(D_804007D8, D_80400800, 0xEE);
            func_8007BEF0(1);
        }
        func_80040560(allocated_obj, D_8040861C);
        return func_80407CC4(card_state);
    }
    func_80403D24(obj);
    ASM_KEEP_NV(obj);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    {
        u16 flags = D_8040C420.flags;
        flags &= 0x7FFF;
        D_8040C420.flags = flags;
    }
    func_8007BFE0(card_state, 0x180);
    func_80407B14(card_state, 4);
    obj->field_0C = (s32)((u8 *)card_state + 0xE0);
    state_value = func_80407AEC((u8 *)card_state + 0xF0);
    {
        Sub *tail = card_state;
        ASM_KEEP_NV(tail);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        tail->field_EC = state_value;
        func_80407BD0(tail, init_option);
    }
    return (s32)obj;
}
