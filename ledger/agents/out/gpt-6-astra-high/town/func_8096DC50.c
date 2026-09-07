#include "common.h"

typedef struct S_801260E8_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x52];
    void * unk_58;
} S_801260E8_0;   /* arg0 in func_801260E8 */

typedef struct S_801260E8_1 {
    s32 unk_00;
    u8 pad_04[0x6C];
    void * unk_70;
} S_801260E8_1;   /* clear_target in func_801260E8 */

typedef struct S_801260E8_2 {
    s32 unk_00;
} S_801260E8_2;   /* destination in func_801260E8 */

typedef struct S_801260E8_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801260E8_3;   /* *objects_a1 in func_801260E8 */

typedef struct S_801260E8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_801260E8_4;   /* object_data in func_801260E8 */



typedef struct TownInitialPosition {
    void *data;
    volatile u16 x;
    volatile u16 y;
} TownInitialPosition;

extern void func_801235EC(void);
extern void func_80123700(void);
extern void func_801237E8(void *);
extern void func_80123898(void *);
extern void func_801238E4(void *);
extern void func_80124728(void *);
extern void func_801247F8(void *);
extern void *D_8011AD90[];
extern TownInitialPosition D_80126AF8[5];
extern void *D_80129728[];

/* Initializes, updates, or clears town objects according to the current action. */
void func_801260E8(S_801260E8_0 *context)
{
    static void *const switch_labels[] = {
        &&case_0,
        &&done,
        &&done,
        &&done,
        &&done,
        &&done,
        &&done,
        &&case_7,
        &&case_8_10,
        &&case_8_10,
        &&case_8_10,
        &&case_11,
        &&case_12_14,
        &&case_12_14,
        &&case_12_14,
        &&done,
        &&case_16,
        &&done,
        &&done,
        &&done
    };
    s32 action_index;
    s32 object_index;
    s32 initial_offset;
    s8 *initial_base;
    s32 *initial_data;
    void **object_table;
    register void **object_cursor ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    S_801260E8_2 *target_object;
    S_801260E8_4 *object_data;
    s32 data_word;
    u16 object_word;

    action_index = (s16)(context->unk_04 - 1);
    if ((u32)action_index >= 20) {
        goto done;
    }
    (void)switch_labels;
    goto *D_8011AD90[action_index];

case_0:
    {
        S_801260E8_1 *clear_target;

        clear_target = context->unk_58;
        clear_target = clear_target->unk_70;
        clear_target->unk_00 = 0;
    }
    func_80123700();
    func_80124728(context);
    func_801235EC();
    func_801247F8(context);
    func_801237E8(context);
    func_80123898(context);
    {
        s32 clear_index;
        u8 *clear_base;
        s32 **clear_cursor;
        s32 *clear_entry;

        clear_index = 14;
        clear_base = (u8 *)D_80129728;
        clear_cursor = (s32 **)(clear_base + 0x38);
        do {
            clear_entry = *clear_cursor;
            ASM_KEEP(clear_entry);   /* MATCH pin: keeps a statement from moving across a call/branch */
            clear_index += 1;
            *clear_entry = 0;
            clear_cursor = (s32 **)((u8 *)clear_cursor + 4);
        } while (clear_index < 16);
    }
    goto done;

case_7:
    object_index = 14;
    initial_base = (s8 *)D_80126AF8;
    initial_offset = 0;
    object_table = D_80129728;
    object_cursor = &object_table[14];
    do {
        initial_data = (s32 *)((u32)initial_offset + (u32)initial_base);
        initial_offset += 8;
        target_object = *object_cursor;
        ASM_KEEP(target_object);   /* MATCH pin: retail schedule: same instructions, different order without it */
        data_word = *initial_data;
        ASM_KEEP(data_word);   /* MATCH pin: load-bearing for the whole function shape */
        object_index += 1;
        target_object->unk_00 = data_word;
        object_cursor += 1;
    } while (object_index < 16);

case_8_10:
    object_index = 14;
    object_table = D_80129728;
    object_cursor = &object_table[14];
    do {
        object_data = ((S_801260E8_3 *)(*object_cursor))->unk_08;
        object_word = object_data->unk_02;
        ASM_KEEP(object_word);   /* MATCH pin: retail schedule: same instructions, different order without it */
        object_index += 1;
        object_data->unk_02 = (u16)(object_word - 0x100);
        object_cursor += 1;
    } while (object_index < 28);
    goto done;

case_11:
    func_801238E4(context);

case_12_14:
    object_index = 14;
    object_table = D_80129728;
    object_cursor = &object_table[14];
    do {
        object_data = ((S_801260E8_3 *)(*object_cursor))->unk_08;
        object_word = object_data->unk_02;
        ASM_KEEP(object_word);   /* MATCH pin: retail schedule: same instructions, different order without it */
        object_index += 1;
        object_data->unk_02 = (u16)(object_word - 0x100);
        object_cursor += 1;
    } while (object_index < 28);
    goto done;

case_16:
    func_801237E8(context);
    {
        s32 clear_index;
        u8 *clear_base;
        s32 **clear_cursor;
        s32 *clear_entry;

        clear_index = 14;
        clear_base = (u8 *)D_80129728;
        clear_cursor = (s32 **)(clear_base + 0x38);
        do {
            clear_entry = *clear_cursor;
            ASM_KEEP(clear_entry);   /* MATCH pin: keeps a statement from moving across a call/branch */
            clear_index += 1;
            *clear_entry = 0;
            clear_cursor = (s32 **)((u8 *)clear_cursor + 4);
        } while (clear_index < 28);
    }

done:
    return;
}

/* MECHANISM: The one-argument ABI plus external 20-way table/local epilogue edges yields the
   retail 0x18 frame and CFG. Scoped clear-loop locals recover v1/v0 coloring and the cursor
   delay slot; a0/a1 loop roles plus load-boundary keeps preserve the remaining schedules. */
