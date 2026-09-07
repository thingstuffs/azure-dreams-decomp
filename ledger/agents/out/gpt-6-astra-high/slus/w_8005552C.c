#include "common.h"

#include "common.h"

extern s32 func_8005405C(s32 n);
extern void func_8005560C(s32 a0, s32 a1);
extern void func_80055730(s32 a0, s32 a1);

/* Decode a packed selector and dispatch its index and offset if its code is available. */
void func_8005552C(s32 selector) {
    /* Pin keeps andi a0,a0 (not CSE-from-saved_selector) and value temps in $v0. */
    register s32 type_bits ASM_REG("$4") = selector;   /* MATCH pin: slus-diff */
    register s32 selected_code ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 saved_selector;
    s32 dispatch_code;
    s32 entry_index;
    s32 entry_offset;

    saved_selector = type_bits;
    type_bits = type_bits & 0xF00;
    if (type_bits == 0x600) {
        goto case_600;
    }
    if (type_bits < 0x601) {
        selected_code = 1;
        goto merge;
    }
    if (type_bits == 0x700) {
        goto case_700;
    }
    if (type_bits == 0x800) {
        goto case_800;
    }
    /* default: selected_code→dispatch_code then jump past merge (delay-slot duplicate of merge) */
    selected_code = 1;
    goto setcode_after;
case_600:
    selected_code = 2;
    goto merge;
case_700:
    selected_code = 3;
    goto merge;
case_800:
    selected_code = 0;
merge:
    dispatch_code = selected_code;
    goto after;
setcode_after:
    dispatch_code = selected_code;
after:
    if ((func_8005405C(dispatch_code) << 0x10) != 0) {
        entry_index = (dispatch_code << 8) | ((u32)(saved_selector & 0xFF) >> 4);
        entry_offset = ((saved_selector & 0xF) << 0xA) + 0x1C00;
        if (dispatch_code == 0) {
            entry_index += 0x10;
        }
        if (saved_selector & 0x1000) {
            func_80055730(entry_index, entry_offset);
            return;
        }
        func_8005560C(entry_index, entry_offset);
    }
}
