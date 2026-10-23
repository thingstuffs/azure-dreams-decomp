/* Relinked copy of town/func_80880298 (func_80880298.c); its callback table puts the two entries at +0x64/+0x70 (twin +0x68/+0x74), otherwise retail differs only at relocation sites. */
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef void (*Callback3)(void *, void *, s32);
typedef void (*Callback1)(s32);

typedef struct {
    u8 pad68[0x64];
    Callback3 callback68;
    u8 pad6c[8];
    Callback1 callback74;
} CallbackTable;

typedef struct {
    u8 pad10[0x10];
    void *field10;
} GlobalState;

extern s32 D_A0700B30;
extern u8 D_A0700184[];
extern u8 D_A07001AC[];
extern s32 D_A0700B28[];
extern s32 *D_A0700B4C[];
extern CallbackTable *devkit_page_trace_methods[];
extern GlobalState *D_A0700B44[];
extern void shift_index_and_add_offset_c(void);

/* Selects a record list and resolves its indices through the global lookup table. */
void select_record_list_resolves_indices(s32 list_index) {
    void *records;

    if (D_A0700B30 != 0) {
        devkit_page_trace_methods[0]->callback68(D_A0700184, D_A07001AC, 0x59);
        devkit_page_trace_methods[0]->callback74(1);
    }
    D_A0700B30 = 1;
    shift_index_and_add_offset_c();
    D_A0700B44[0]->field10 = (void *)D_A0700B28[list_index];
    records = D_A0700B44[0]->field10;
    if (((u8 *)records)[1] != 0x80) {
        s32 end_tag = 0x80;
        s32 i = 0;
        u8 *tags = (u8 *)records + 1;
        do {
            *(s32 *)(tags + i * 0x14 + 0xB) = D_A0700B4C[0][*(s32 *)(tags + i * 0x14 + 0xB)];
            i++;
        } while (tags[i * 0x14] != end_tag);
    }
}
