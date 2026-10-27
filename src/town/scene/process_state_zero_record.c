#include "common.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in process_state_zero_record, addressed as arg0[-1] */

typedef struct S_80815160_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    const char *unk_04;
    s16 * unk_08;
    void * unk_0C;
} S_80815160_0;   /* arg0 in process_state_zero_record */

typedef struct S_80815160_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_80815160_1;
void func_80058588(s32 value, s32 query, const char *text);               /* extern */
s32 func_80071424(const char *);                             /* extern */
extern s32 scene_object_flags;

/* Processes a state-zero record and sets record/global flags if its linked record has bit 3 set. */
void process_state_zero_record(void *record) {
    ObjectStatusPrefix16 *record_view = record;
    u16 *flags;
    void *linked_record;

    linked_record = ((S_80815160_0 *)record)->unk_0C;
    if (((S_80815160_0 *)record)->unk_00 == 0) {
        func_80058588(*((S_80815160_0 *)record)->unk_08, func_80071424(((S_80815160_0 *)record)->unk_04),
            ((S_80815160_0 *)record)->unk_04);
        if (((S_80815160_1 *)linked_record)->unk_1A & 8) {
            flags = &record_view[-1].flags;
            *flags = (u16) (record_view[-1].flags | 0x8000);
            scene_object_flags |= 0x8000;
        }
    }
}
