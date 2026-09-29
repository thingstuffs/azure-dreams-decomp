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
extern s8 D_80129728;

/* Updates or clears table entries according to the request code. */
void func_80125DDC(Rec_func_801237A4_arg0 *request)
{
    s32 action_index;

    action_index = (s16)(request->unk_04.as_u16 - 1);
    switch (action_index) {
    case 0:
        func_801235EC();
        func_801247F8(request);
        return;
    case 7:
    case 8:
    case 9:
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
            do {
                entry = *entry_slot;
                entry_data = ((S_80125DDC_1 *)entry)->unk_08;
                field_value = ((S_80125DDC_2 *)entry_data)->unk_02;
                do {
                    entry_index++;
                } while (0);
                field_value += 0x100;
                ((S_80125DDC_2 *)entry_data)->unk_02 = field_value;
                entry_slot = (void **)((u8 *)entry_slot + 4);
            } while (entry_index < 0x62);
        }
        return;
    case 10:
        {
            s32 entry_index;
            u8 *entry_table;
            s32 **entry_slot;
            s32 *entry;

            entry_index = 0x1E;
            entry_table = (u8 *)&D_80129728;
            entry_slot = (s32 **)(entry_table + 0x78);
            do {
                do {
                    entry = *entry_slot;
                } while (0);
                entry_index++;
                *entry = 0;
                entry_slot = (s32 **)((u8 *)entry_slot + 4);
            } while (entry_index < 0x62);
        }
    case 11:
    case 12:
    case 13:
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
            do {
                entry = *entry_slot;
                entry_data = ((S_80125DDC_1 *)entry)->unk_08;
                field_value = ((S_80125DDC_2 *)entry_data)->unk_02;
                do {
                    entry_index++;
                } while (0);
                field_value += 0x100;
                ((S_80125DDC_2 *)entry_data)->unk_02 = field_value;
                entry_slot = (void **)((u8 *)entry_slot + 4);
            } while (entry_index < 0x62);
        }
        break;
    case 14:
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
            do {
                entry = *entry_slot;
                entry_data = ((S_80125DDC_1 *)entry)->unk_08;
                field_value = ((S_80125DDC_2 *)entry_data)->unk_02;
                do {
                    entry_index++;
                } while (0);
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
                do {
                    entry = *entry_slot;
                } while (0);
                entry_index++;
                *entry = 0;
                entry_slot = (s32 **)((u8 *)entry_slot + 4);
            } while (entry_index < 0x1E);
        }
    case 19:
    default:
        break;
    }
}
