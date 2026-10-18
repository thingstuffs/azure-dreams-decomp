#include "common.h"
#include "m2c_compat.h"

void initialize_display_entry();               /* extern */
M2C_UNK func_800B640C();               /* extern */
void join_monster_status_display_chains();                 /* extern */
typedef struct S_800B6508_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s16 unk_08;
    u8 pad_0A[0xA];
    s32 unk_14;
    u8 pad_18[0x80];
    s32 unk_98;
} S_800B6508_0;   /* arg0 in process_object_data_by_mode */

/* extern */

/* Processes the object's embedded data, then selects a handler by its mode flag. */
void process_object_data_by_mode(void *object) {
    join_monster_status_display_chains(object + 0x88, ((S_800B6508_0 *)object)->unk_98);
    if (((S_800B6508_0 *)object)->unk_08 != 0) {
        func_800B640C(((S_800B6508_0 *)object)->unk_04, ((S_800B6508_0 *)object)->unk_98,
            ((S_800B6508_0 *)object)->unk_14);
        return;
    }
    initialize_display_entry(((S_800B6508_0 *)object)->unk_04, ((S_800B6508_0 *)object)->unk_98, ((S_800B6508_0 *)object)->unk_14);
}
