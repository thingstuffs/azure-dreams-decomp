#include "common.h"
#include "records/Rec_func_801237A4_arg0.h"


typedef struct S_80125DDC_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80125DDC_1;   /* entry in func_80125DDC */

typedef struct S_80125DDC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80125DDC_2;   /* inner in func_80125DDC */



extern void func_801235EC(void);
extern void func_801247F8(void *);
extern void *D_8011AD08[];
extern s8 D_80129728;

/* Updates or clears table entries according to the request code. */
void func_80125DDC(Rec_func_801237A4_arg0 *request)
{
    static void *const dispatch_labels[20] = {
        &&case_0,
        &&done, &&done, &&done, &&done, &&done, &&done,
        &&case_789, &&case_789, &&case_789,
        &&case_10,
        &&case_111213, &&case_111213, &&case_111213,
        &&case_14,
        &&done, &&done, &&done, &&done, &&done
    };
    s32 action_index;

    action_index = (s16)(request->unk_04.as_u16 - 1);
    if ((u32)action_index >= 20) {
        goto done;
    }
    (void)dispatch_labels;
    goto *D_8011AD08[action_index];

case_0:
    func_801235EC();
    func_801247F8(request);
    goto done;

case_789:
    {
        s32 entry_index;
        u8 *entry_table;
        void **entry_slot;
        void *entry;
        void *entry_data;
        u16 field_value;

        entry_index = 0x1C;
        entry_table = (u8 *)&D_80129728;
        entry_slot = (void **)(entry_table + 0x70);
        ASM_KEEP(entry_index);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        do {
            entry = *entry_slot;
            entry_data = ((S_80125DDC_1 *)entry)->unk_08;
            field_value = ((S_80125DDC_2 *)entry_data)->unk_02;
            ASM_KEEP(field_value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            entry_index++;
            field_value += 0x100;
            ((S_80125DDC_2 *)entry_data)->unk_02 = field_value;
            entry_slot = (void **)((u8 *)entry_slot + 4);
        } while (entry_index < 0x62);
    }
    goto done;

case_10:
    {
        s32 entry_index;
        u8 *entry_table;
        s32 **entry_slot;
        s32 *entry;

        entry_index = 0x1E;
        entry_table = (u8 *)&D_80129728;
        entry_slot = (s32 **)(entry_table + 0x78);
        do {
            entry = *entry_slot;
            ASM_KEEP(entry);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            entry_index++;
            *entry = 0;
            entry_slot = (s32 **)((u8 *)entry_slot + 4);
        } while (entry_index < 0x62);
    }

case_111213:
    {
        s32 entry_index;
        u8 *entry_table;
        void **entry_slot;
        void *entry;
        void *entry_data;
        u16 field_value;

        entry_index = 0x1C;
        entry_table = (u8 *)&D_80129728;
        entry_slot = (void **)(entry_table + 0x70);
        ASM_KEEP(entry_index);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        do {
            entry = *entry_slot;
            entry_data = ((S_80125DDC_1 *)entry)->unk_08;
            field_value = ((S_80125DDC_2 *)entry_data)->unk_02;
            ASM_KEEP(field_value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            entry_index++;
            field_value += 0x100;
            ((S_80125DDC_2 *)entry_data)->unk_02 = field_value;
            entry_slot = (void **)((u8 *)entry_slot + 4);
        } while (entry_index < 0x62);
    }
    goto done;

case_14:
    {
        s32 entry_index;
        u8 *entry_table;
        void **entry_slot;
        void *entry;
        void *entry_data;
        u16 field_value;

        entry_index = 0x1C;
        entry_table = (u8 *)&D_80129728;
        entry_slot = (void **)(entry_table + 0x70);
        ASM_KEEP(entry_index);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        do {
            entry = *entry_slot;
            entry_data = ((S_80125DDC_1 *)entry)->unk_08;
            field_value = ((S_80125DDC_2 *)entry_data)->unk_02;
            ASM_KEEP(field_value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            entry_index++;
            field_value += 0x100;
            ((S_80125DDC_2 *)entry_data)->unk_02 = field_value;
            entry_slot = (void **)((u8 *)entry_slot + 4);
        } while (entry_index < 0x62);
    }
    {
        s32 entry_index;
        u8 *entry_table;
        s32 **entry_slot;
        s32 *entry;

        entry_index = 0x1C;
        entry_table = (u8 *)&D_80129728;
        entry_slot = (s32 **)(entry_table + 0x70);
        do {
            entry = *entry_slot;
            ASM_KEEP(entry);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            entry_index++;
            *entry = 0;
            entry_slot = (s32 **)((u8 *)entry_slot + 4);
        } while (entry_index < 0x1E);
    }

done:
    return;
}
