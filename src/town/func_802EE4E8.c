#include "common.h"


typedef s32 M2C_UNK;


extern M2C_UNK card_build_selected_slot_details();
extern void build_memory_task_text();
extern u8 D_8009DDD8[];

typedef struct S_802EE4E8_0 {
    u8 pad_00[0x7C];
    s32 unk_7C;
} S_802EE4E8_0;   /* arg0 in func_802EE4E8 */

/* Select the exit or fallback path using the indexed table entry. */
void select_memory_task_exit(S_802EE4E8_0 *object) {
    if (*(s32 *)(D_8009DDD8 + (object->unk_7C << 7)) != 0) {
        card_build_selected_slot_details();
    } else {
        build_memory_task_text();
    }
}
