#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Func8180F0F4_Obj {
    u8 pad00[0x11];
    u8 field11;
    u8 pad12[2];
    u16 field14;
    u8 pad16[2];
    u32 field18;
    u8 pad1c[0x38];
    s32 field54;
} Func8180F0F4_Obj;

extern s16 D_8008347E;

/* Selects an object by flags and comparison keys and writes the resolved low-bit mask. */
void *func_800280F4(Func8180F0F4_Obj *first, Func8180F0F4_Obj *second, s16 *out_mask) {
    s16 first_mask;
    u16 resolved_mask;
    s32 first_flags;
    s32 second_flags;
    s32 choose_first;
    u16 first_traits;
    u16 second_traits;
    u32 second_key;
    u32 first_key;
    Func8180F0F4_Obj *selected;
    void *result;

    first_flags = first->field54;
    second_flags = second->field54;
    if (!(first_flags & second_flags & 0x800000)) {
        if (!(first_flags & 0x800000) && !(second_flags & 0x400000)) {
            if ((second_flags & 0x800000) || (first_flags & 0x400000)) {
                selected = second;
            } else {
                first_key = first->field11;
                second_key = second->field11;
                selected = second;
                if ((first_key == second_key) &&
                    (first_key = first->field18,
                     second_key = second->field18,
                     (first_key == second_key))) {
                    choose_first = D_8008347E & 1;
                } else {
                    choose_first = second_key < first_key;
                }
                if (choose_first != 0) {
                    goto select_first;
                }
            }
        } else {
    select_first:
            selected = first;
        }
        result = selected;
        first_traits = first->field14;
        do {
            second_traits = second->field14;
        } while (0);
        first_mask = first_traits & 7;
        resolved_mask = second_traits & 7;
        if (first_mask == resolved_mask) {
            resolved_mask = first_mask;
        } else if (first_traits & 1) {
            resolved_mask = 1;
            if (second_traits & 2) {
                resolved_mask = 2;
            }
        } else if (first_traits & 2) {
            resolved_mask = 2;
            if (second_traits & 4) {
                resolved_mask = 4;
            }
        } else if (first_traits & 4) {
            resolved_mask = 4;
            if (second_traits & 1) {
                resolved_mask = 1;
            }
        }
        *out_mask = resolved_mask;
        return result;
    }
    return NULL;
}
