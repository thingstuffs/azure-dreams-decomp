#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

extern s32 func_80047FD8(void *object);
extern void *func_8003C714(s32 option, void *object, s32 param);
extern void func_80040560(void *object, void *data);
extern void func_8007BEF0(s32 value);
extern void func_8007BFE0(void *object, s32 value);
extern void func_8007C040(void *first_ptr, void *second_ptr, s32 value);
extern void process_embedded_data_and_propagate_flags(void *object);
extern s32 dispatch_context_through_four_entry_table(void *context);
extern void func_80407B14(void *object, s32 value);
extern void func_80407BD0(void *object, s32 option);

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
s32 init_card_sme_object(s32 init_option) {
    Obj *obj = (Obj *)&D_8040C420;
    Sub *card_state = (Sub *)((u8 *)obj + 0x20);
    s32 state_value;

    if (func_80047FD8(obj) == 0) {
        obj = (Obj *)func_8003C714(0, obj, 0x68);
        if (obj == 0) {
            func_8007C040(D_804007D8, D_80400800, 0xEE);
            func_8007BEF0(1);
        }
        func_80040560(obj, D_8040861C);
    } else {
        process_embedded_data_and_propagate_flags(obj);
        {
            u16 flags = D_8040C420.flags;
            flags &= 0x7FFF;
            D_8040C420.flags = flags;
        }
        func_8007BFE0(card_state, 0x180);
    }
    func_80407B14(card_state, 4);
    obj->field_0C = (s32)((u8 *)card_state + 0xE0);
    state_value = dispatch_context_through_four_entry_table((u8 *)card_state + 0xF0);
    card_state->field_EC = state_value;
    func_80407BD0(card_state, init_option);
    return (s32)obj;
}
