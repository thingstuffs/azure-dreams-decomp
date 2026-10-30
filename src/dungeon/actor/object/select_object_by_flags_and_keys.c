#include "shared/actor_property_flags.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/object.h"

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


/* Selects an object by flags and comparison keys and writes the resolved low-bit mask. */
void *select_object_by_flags_and_keys(Func8180F0F4_Obj *first, Func8180F0F4_Obj *second, s16 *out_mask) {
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
                    choose_first = ((s16)g_dungeon_status.turn_counter) & 1;
                } else {
                    choose_first = second_key < first_key;
                }
                if (choose_first != 0) {
                    selected = first;
                }
            }
        } else {
            selected = first;
        }
        result = selected;
        first_traits = first->field14;
        /* BYTES: sched1/sched2 region barrier or tie: unwrap reorders independent insns (no memory dependence) (ledger/onetrip_loadbearing.jsonl: dungeon/func_8180F0F4). */
        do {
            second_traits = second->field14;
        } while (0);
        first_mask = first_traits & ACTOR_ELEMENT_MASK;
        resolved_mask = second_traits & ACTOR_ELEMENT_MASK;
        if (first_mask == resolved_mask) {
            resolved_mask = first_mask;
        } else if (first_traits & ACTOR_ELEMENT_FIRE) {
            resolved_mask = ACTOR_ELEMENT_FIRE;
            if (second_traits & ACTOR_ELEMENT_WATER) {
                resolved_mask = ACTOR_ELEMENT_WATER;
            }
        } else if (first_traits & ACTOR_ELEMENT_WATER) {
            resolved_mask = ACTOR_ELEMENT_WATER;
            if (second_traits & ACTOR_ELEMENT_WIND) {
                resolved_mask = ACTOR_ELEMENT_WIND;
            }
        } else if (first_traits & ACTOR_ELEMENT_WIND) {
            resolved_mask = ACTOR_ELEMENT_WIND;
            if (second_traits & ACTOR_ELEMENT_FIRE) {
                resolved_mask = ACTOR_ELEMENT_FIRE;
            }
        }
        *out_mask = resolved_mask;
        return result;
    }
    return NULL;
}
