#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800B62A4_0 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_800B62A4_0;   /* var_s2 in func_800B62A4 */



M2C_UNK bzero();            /* extern */
M2C_UNK func_800B58B8();             /* extern */
M2C_UNK func_800B6094();            /* extern */
M2C_UNK func_800B61C0();            /* extern */

/* Fill up to three output slots from source entries and clear unused slots. */
void func_800B62A4(void *source, s32 output) {
    void *entries[3];
    s32 index;
    register s32 slot_count ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 scan_base;
    s32 has_room;
    void *entry;
    s32 *slot_value;
    void *slot_cursor;
    void *source_cursor;

    slot_count = 0;
    index = slot_count;
    scan_base = 8;
    source_cursor = source;
    do {
        if (((S_800B62A4_0 *)source_cursor)->unk_08 != 0) {
            func_800B6094(source + scan_base, output, slot_count);
            slot_count += 1;
        }
        scan_base += 3;
        index += 1;
        source_cursor += 3;
    } while (index < 3);
    bzero(entries, 0xC);
    func_800B58B8(entries, source);
    index = 0;
    has_room = slot_count < 3;
    scan_base = slot_count;
    if (has_room != 0) {
        source_cursor = entries;
        do {
            entry = *(void **)source_cursor;
            if (entry != NULL) {
                func_800B61C0(entry, output, slot_count);
                slot_count += 1;
            }
            index += 1;
            source_cursor = (void *)((s8 *)source_cursor + 4);
        } while ((index + scan_base) < 3);
        has_room = slot_count < 3;
    }
    index = slot_count;
    if ((has_room != 0) && (((Rec_D_800E3D7C *)source)->unk_48.at01_u8.v != 0)) {
        func_800B61C0(source + 0x48, output, slot_count);
        slot_count += 1;
        ASM_KEEP(slot_count);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        index = slot_count;
    }
    if (index < 3) {
        slot_cursor = (index * 4) + output;
        do {
            slot_value = (*(s32 * volatile *)((u8 *)slot_cursor + 0x38));
            index += 1;
            *slot_value = 0;
            do {
                slot_cursor += 4;
            } while (0);
        } while (index < 3);
    }
}
/* MECHANISM: A 3-pointer stack array forces the retail 0x40 frame; unified loop-role
   live ranges plus guarded $s1/$s3/$s2 pins reproduce the hold set.
   cdk-G0's zero-equivalence copy and a volatile $v0 tail load with post-store keep fence
   place $s0++ in the load delay and preserve the retail loop schedule. */
