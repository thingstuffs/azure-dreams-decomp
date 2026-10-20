#include "common.h"
typedef struct { u8 pad[0x7C]; s32 index; } Owner;
void select_memory_task_exit(Owner *owner);                      /* extern */
void func_80405900(void *);                      /* extern */

typedef struct S_8001EA00_0 {
    u8 pad_00[0x9C];
    s32 unk_9C;
} S_8001EA00_0;   /* arg0 in card_info_set_value_and_refresh */

/* Store the value and process embedded data when the object exists. */
void card_info_set_value_and_refresh(void *object, s32 value) {
    void *embedded_data;

    if (object != 0) {
        ((S_8001EA00_0 *)object)->unk_9C = value;
        embedded_data = object + 0x20;
        func_80405900(embedded_data);
        select_memory_task_exit(embedded_data);
    }
}
