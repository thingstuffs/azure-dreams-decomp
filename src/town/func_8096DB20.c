#include "common.h"
#include "records/Rec_func_801237A4_arg0.h"


typedef struct S_80125FB8_1 {
    s32 unk_00;
} S_80125FB8_1;   /* destination in func_80125FB8 */

typedef struct S_80125FB8_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80125FB8_2;   /* *objects in func_80125FB8 */

typedef struct S_80125FB8_3 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80125FB8_3;   /* object_data in func_80125FB8 */



typedef struct TownInitialPosition {
    void *data;
    volatile u16 x;
    volatile u16 y;
} TownInitialPosition;

extern void func_801232DC(void);
extern void func_80124188(void *);
extern void *D_8011AD58[];
extern TownInitialPosition D_80126AF8[5];
extern void *D_80129728[];

/* Updates town object data according to the current state. */
void func_80125FB8(Rec_func_801237A4_arg0 *state)
{
    static void *const switch_labels[] = {
        &&case_0,
        &&case_123,
        &&case_123,
        &&case_123,
        &&case_4,
        &&case_567,
        &&case_567,
        &&case_567,
        &&done,
        &&done,
        &&done,
        &&done,
        &&done
    };
    s32 state_index;
    s32 object_index;
    s32 initial_offset;
    s8 *initial_base;
    s32 *initial_entry;
    void **object_base;
    register void **objects ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_80125FB8_1 *object;
    S_80125FB8_3 *object_data;
    s32 initial_data;
    u16 data_value;

    state_index = (s16)(state->unk_04.as_u16 - 8);
    if ((u32)state_index >= 13) {
        goto done;
    }
    (void)switch_labels;
    goto *D_8011AD58[state_index];

case_0:
    object_index = 0x1C;
    initial_base = (s8 *)D_80126AF8;
    initial_offset = 0;
    object_base = D_80129728;
    objects = &object_base[0x1C];
    do {
        initial_entry = (s32 *)((u32)initial_offset + (u32)initial_base);
        initial_offset += 8;
        object = objects[0];
        ASM_KEEP(object);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        initial_data = *initial_entry;
        ASM_KEEP(initial_data);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        object_index += 1;
        object->unk_00 = initial_data;
        objects += 1;
    } while (object_index < 0x1E);

case_123:
    object_index = 0x1C;
    object_base = D_80129728;
    objects = &object_base[0x1C];
    do {
        object_data = ((S_80125FB8_2 *)(*objects))->unk_08;
        data_value = object_data->unk_02;
        ASM_KEEP(data_value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        object_index += 1;
        object_data->unk_02 = (u16)(data_value - 0x100);
        objects += 1;
    } while (object_index < 0x62);
    goto done;

case_4:
    func_801232DC();
    func_80124188(state);

case_567:
    object_index = 0x1C;
    object_base = D_80129728;
    objects = &object_base[0x1C];
    do {
        object_data = ((S_80125FB8_2 *)(*objects))->unk_08;
        data_value = object_data->unk_02;
        ASM_KEEP(data_value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        object_index += 1;
        object_data->unk_02 = (u16)(data_value - 0x100);
        objects += 1;
    } while (object_index < 0x62);

done:
    return;
}

/* MECHANISM: The true-space 0x801260D4 target is a local epilogue edge; a 13-way
   external-table dispatch preserves the 0x18 frame and sole s0 hold. Named bases,
   runtime a0/a1 pins, load-boundary keeps, and integer index-first addition close it. */
