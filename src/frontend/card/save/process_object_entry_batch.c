#include "common.h"
#include "shared/object_node.h"
#include "frontend/card/service.h"
#include "frontend/card/save.h"

typedef struct S_8001EDE0_0 {
    u8 pad_00[0x2C];
    s32 unk_2C;
    u8 pad_30[4];
    void (*menu_update)(void);
    u8 pad_38[8];
    s32 unk_40;
} S_8001EDE0_0;   /* ptr in func_8001EDE0 */

extern s32 func_80400908(void);
extern s32 process_entry_with_table_value(s32, s32);
extern void func_80402214(void);
extern void initialize_card_message_object_with_code_0x10(void *);
extern void func_80404688(s32);
extern void func_80405AB4(void *);
extern void func_80405C44(s32);
extern void func_80405A3C(void);

/* Runs two card checks and processes five object entries; installs menu and message callbacks on failure. */
void process_object_entry_batch(void *ptr_arg) {
    S_8001EDE0_0 *ptr = ptr_arg;
    s32 value;
    s32 index;
    void *offset_ptr;
    ObjectNodeHeader *entry_ptr;

    if (read_and_update_indexed_record(ptr->unk_2C, 0x80010000) != 0) {
        *(s32 *)0x80010208 = 0;
        if (process_entry_with_table_value((*(s32 *)((u8 *)ptr + 0x28)), 0x80010000) != 0) {
            func_80405C44(0x80010000);
            index = 0;
            func_80402214();
            entry_ptr = ptr_arg;
            do {
                value = *(s32 *)&entry_ptr->pprev;
                entry_ptr = (u8 *)entry_ptr + 4;
                index += 1;
                func_80404688(value);
            } while (index < 5);
            func_80405AB4(ptr);
            func_80400908();
            ptr->unk_40 = 0;
            return;
        }
    }
    offset_ptr = (u8 *)ptr - 0x20;
    ptr->menu_update = handle_object_menu_input;
    initialize_card_message_object_with_code_0x10(offset_ptr);
    ((ObjectNodeHeader *)ptr)[-1].update_callback = (void *)func_80405A3C;
    func_80400908();
    ptr->unk_40 = 0;
}
