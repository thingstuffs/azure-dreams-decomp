#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

extern s32 func_80047FD8(void *object);
extern void *func_8003C714(s32 option, void *object, s32 param);
extern void func_8007C040(void *first_ptr, void *second_ptr, s32 value);
extern void func_8007BEF0(s32 value);
extern void func_80040560(void *object, void *data);
extern void func_804059A8(void *object);
extern void func_8007BFE0(void *object, s32 value);
extern void initialize_menu_primitive_entries(void *object, s32 value);
extern s32 register_owner_handler_table(void *value);
extern void initialize_menu_overlay_objects(void *object, s32 option);

typedef struct {
    u8 pad_00[0x1E];
    u16 flags;
} Root;

extern Root D_8040B4F8;

/* Initializes the memory card information object and its working state. */
void *init_card_info_object(s32 init_option, s32 info_value) {
    void *base;
    void *card_state;

    base = &D_8040B4F8;
    card_state = (u8 *)base + 0x20;
    if (func_80047FD8(base) == 0) {
        base = func_8003C714(0, base, 0x387);
        if (base == 0) {
            func_8007C040(D_80400738, D_80400760, 0x1A0);
            func_8007BEF0(1);
        }
        func_80040560(base, D_8040861C);
    } else {
        func_804059A8(base);
        D_8040B4F8.flags &= 0x7FFF;
        func_8007BFE0(card_state, 0xDFC);
    }
    *(s32 *)((u8 *)card_state + 0x7C) = info_value;
    initialize_menu_primitive_entries(card_state, 0x15);
    *(void **)((u8 *)base + 0xC) = (u8 *)card_state + 0xAF8;
    *(s32 *)((u8 *)card_state + 0xB04) = register_owner_handler_table((u8 *)card_state + 0xB08);
    initialize_menu_overlay_objects(card_state, init_option);
    *(s32 *)((u8 *)base + 0x10) = 0;
    return base;
}
