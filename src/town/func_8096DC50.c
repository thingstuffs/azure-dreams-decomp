#include "common.h"
#include "records/Rec_func_801237A4_arg0.h"
#include "shared/object_payload.h"


typedef struct S_801260E8_1 {
    s32 unk_00;
    u8 pad_04[0x6C];
    void * unk_70;
} S_801260E8_1;   /* clear_target in animate_catalog_previous_detail */

typedef struct S_801260E8_2 {
    s32 unk_00;
} S_801260E8_2;   /* destination in animate_catalog_previous_detail */



typedef struct S_801260E8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_801260E8_4;   /* object_data in animate_catalog_previous_detail */


typedef struct TownInitialPosition {
    void *data;
    u16 x;
    u16 y;
} TownInitialPosition;

extern void store_cached_value_at_pointer(void);
extern void initialize_linked_value_records(void);
extern void swap_paired_entry_values_and_node_halfwords(u8 *state);
extern void backup_and_clear_linked_values(void *);
extern void restore_linked_values_from_backup(void *);
extern void refresh_catalog_secondary_detail(void *);
extern void refresh_catalog_primary_detail(void *);
extern TownInitialPosition D_80126AF8[5];
extern void *D_80129728[];

/* Initializes, updates, or clears town objects according to the current action. */
void animate_catalog_previous_detail(Rec_func_801237A4_arg0 *context)
{
    s32 action_index;
    s32 object_index;
    s32 initial_offset;
    s8 *initial_base;
    s32 *initial_data;
    S_801260E8_2 *target_object;
    S_801260E8_4 *object_data;
    s32 data_word;
    u16 object_word;

    action_index = (s16)(context->unk_04.as_u16 - 1);
    switch (action_index) {
    case 0:
    {
        S_801260E8_1 *clear_target;

        clear_target = context->unk_58;
        clear_target = clear_target->unk_70;
        clear_target->unk_00 = 0;
    }
        initialize_linked_value_records();
        refresh_catalog_secondary_detail(context);
        store_cached_value_at_pointer();
        refresh_catalog_primary_detail(context);
        swap_paired_entry_values_and_node_halfwords(context);
        backup_and_clear_linked_values(context);
        {
            s32 clear_index;
            u8 *clear_base;
            s32 **clear_cursor;
            s32 *clear_entry;

            clear_index = 14;
            clear_base = (u8 *)D_80129728;
            clear_cursor = (s32 **)(clear_base + 0x38);
            do {
                clear_entry = *clear_cursor++;
                clear_index += 1;
                *clear_entry = 0;
            } while (clear_index < 16);
        }
        return;
    case 7:
        object_index = 14;
        initial_base = (s8 *)D_80126AF8;
        initial_offset = 0;
        do {
            initial_data = (s32 *)((u32)initial_offset + (u32)initial_base);
            initial_offset += 8;
            target_object = D_80129728[object_index];
            data_word = *initial_data;
            object_index += 1;
            target_object->unk_00 = data_word;
        } while (object_index < 16);
    case 8:
    case 9:
    case 10:
        object_index = 14;
        do {
            object_data = ((CatalogObjectPayloadView *)(D_80129728[object_index]))->unk_08;
            object_word = object_data->unk_02;
            object_index += 1;
            object_data->unk_02 = (u16)(object_word - 0x100);
        } while (object_index < 28);
        return;
    case 11:
        restore_linked_values_from_backup(context);
    case 12:
    case 13:
    case 14:
        object_index = 14;
        do {
            object_data = ((CatalogObjectPayloadView *)(D_80129728[object_index]))->unk_08;
            object_word = object_data->unk_02;
            object_index += 1;
            object_data->unk_02 = (u16)(object_word - 0x100);
        } while (object_index < 28);
        break;
    case 16:
        swap_paired_entry_values_and_node_halfwords(context);
        {
            s32 clear_index;
            u8 *clear_base;
            s32 **clear_cursor;
            s32 *clear_entry;

            clear_index = 14;
            clear_base = (u8 *)D_80129728;
            clear_cursor = (s32 **)(clear_base + 0x38);
            do {
                clear_entry = *clear_cursor++;
                clear_index += 1;
                *clear_entry = 0;
            } while (clear_index < 28);
        }
    case 19:
    default:
        break;
    }
}

/* MECHANISM: The one-argument ABI plus external 20-way table/local epilogue edges yields the
   retail 0x18 frame and CFG. Scoped clear-loop locals recover v1/v0 coloring and the cursor
   delay slot; a0/a1 loop roles plus load-boundary keeps preserve the remaining schedules. */
