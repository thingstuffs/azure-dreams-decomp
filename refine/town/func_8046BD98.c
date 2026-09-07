#include "common.h"

typedef s32 (*IndexFunc)(s32);
typedef void (*UseFunc)(s16, s8);

extern s8 D_80016000[];
extern s8 *D_80018880[];
extern s16 D_8001888C[];
extern s8 *D_80018A1C;

extern s32 func_8001E670(u16);

/* Applies selected values to entries whose condition checks match their flags. */
void func_8001CD98(void) {
    s8 *selected_values;
    s8 *entry;
    s16 *value_id;
    register s32 first_index ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 entry_index;
    register s32 entry_offset ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    register s32 next_flags ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s8 **entry_page;
    void **root_page;
    s32 condition_result;
    void *context;
    void *callbacks;
    IndexFunc get_selection;
    UseFunc apply_value;

    context = *(void **)D_80016000;
    first_index = 0;
    entry_index = first_index;
    ASM_KEEP(first_index);   /* MATCH pin: retail immediate-load split depends on it */
    entry_offset = (s32)D_80018880;
    selected_values = *(s8 **)(entry_offset +
        (*(IndexFunc *)((s8 *)*(void **)((s8 *)context + 0x20) + 0x2D4))(first_index)
        * 4);
    entry_page = (s8 **)0x80020000;
    if ((((u8 *)*(s8 **)((s8 *)entry_page - 0x75E4))[1] & 0xC0) != 0x80) {
        entry_offset = entry_index;
        value_id = D_8001888C;
loop:
        entry = (s8 *)(entry_offset + (s32)*(s8 **)((s8 *)entry_page - 0x75E4));
        if (!((u8)entry[1] & 1)) {
            condition_result = func_8001E670(*(u16 *)(entry + 2));
            if (condition_result == 0) {
                goto next;
            }
            root_page = (void **)0x80010000;
            entry = selected_values + entry_index;
            goto use_entry;
        } else {
            condition_result = func_8001E670(*(u16 *)(entry + 2));
            if (condition_result == 1) {
                goto next;
            }
            root_page = (void **)0x80010000;
            entry = selected_values + entry_index;
        }

use_entry:
        context = *(void **)((s8 *)root_page + 0x6000);
        callbacks = *(void **)((s8 *)context + 0x20);
        apply_value = *(UseFunc *)((s8 *)callbacks + 0x304);
        apply_value(*value_id, *entry);

next:
        entry_offset += 0x14;
        value_id++;
        entry_index++;
        entry_page = (s8 **)0x80020000;
        next_flags = ((u8 *)(entry_offset + (s32)*(s8 **)((s8 *)entry_page - 0x75E4)))[1];
        if ((next_flags & 0xC0) != 0x80) {
            goto loop;
        }
    }
}
