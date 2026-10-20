#include "common.h"
#include "records/Rec_func_801237A4_arg0.h"


extern s32 is_catalog_entry_available(s32);
extern void layout_catalog_entry_grid(void);
extern void layout_catalog_frame(void);
extern void initialize_catalog_slot_records(void);
extern void select_paired_value_tables(void *);
extern void refresh_catalog_entry_grid(void *);
extern void initialize_catalog_view_records(void *, void *, void *);

/* Initialize state defaults and run the associated setup routines. */
void initialize_catalog_state(void *state) {
    s32 one = 1;

    ((Rec_func_801237A4_arg0 *)state)->unk_04.as_s16 = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_06 = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_08 = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_0A = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_0B = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_0C = one;
    ((Rec_func_801237A4_arg0 *)state)->unk_0D = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_0E = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_0F = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_10 = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_11 = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_12 = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_13 = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_14 = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_16 = 0;
    ((Rec_func_801237A4_arg0 *)state)->unk_17 = 0xFF;
    ((Rec_func_801237A4_arg0 *)state)->unk_18 = 0xFF;

    if ((is_catalog_entry_available(0x31) & 0xFF) ||
        (is_catalog_entry_available(0x30) & 0xFF)) {
        ((Rec_func_801237A4_arg0 *)state)->unk_15 = 0;
    } else {
        ((Rec_func_801237A4_arg0 *)state)->unk_15 = one;
    }

    initialize_catalog_view_records((u8 *)state + 0x48, (u8 *)state + 0x20,
                  (u8 *)state + 0x30);
    select_paired_value_tables(state);
    initialize_catalog_slot_records();
    layout_catalog_frame();
    layout_catalog_entry_grid();
    refresh_catalog_entry_grid(state);
}
