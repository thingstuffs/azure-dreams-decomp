#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A48F0_0 {
    u8 pad_00[0x2C];
    s8 unk_2C;
    union { u8 s; s8 u; } unk_2D;   /* accessed as both */
} S_800A48F0_0;   /* var_s0 in func_800A48F0 */

typedef struct S_800A48F0_1 {
    u8 pad_00[0x2C];
    s8 unk_2C;
    u8 unk_2D;
} S_800A48F0_1;   /* var_s0_2 in func_800A48F0 */


M2C_UNK func_80042BDC(void *, s32, s32, s32);
extern s32 func_800A48F0__self_recurse(void *, s8, s8) __asm__("func_800A48F0");
M2C_UNK func_800A4B88(void *, s8);
M2C_UNK func_80042B68(void *, s32);

/* Updates or inserts a four-slot entry, clearing conflicts or evicting an entry when full. */
s16 func_800A48F0(void *object, s32 id, s32 value) {
    s32 min_id;
    s32 result_shift;
    s32 slot_index;
    s32 slot_id;
    s32 sign_diff;
    s8 used_id;
    register void *entry_owner ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 entry_id ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 entry_value;
    s32 id_shift;
    s32 match_id;
    s32 insert_id;
    void *match_slot;
    void *free_slot;
    s32 signed_value;

    entry_owner = object;
    slot_id = id;
    signed_value = value;
    entry_id = slot_id;
    entry_value = signed_value;
    min_id = 0x100;
    ASM_KEEP4_NV(entry_owner, entry_id, entry_value, min_id);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    slot_index = 3;
    id_shift = slot_id << 24;
    match_id = id_shift >> 24;
    signed_value <<= 24;
    signed_value >>= 24;
    match_slot = entry_owner + 6;
find_match:
    slot_id = ((S_800A48F0_0 *)match_slot)->unk_2C;
    if (slot_id == match_id) {
        sign_diff = ((S_800A48F0_0 *)match_slot)->unk_2D.s;
        sign_diff = (entry_value ^ sign_diff) & 0x80;
        if (sign_diff || (signed_value == 0)) {
            func_80042BDC(entry_owner, slot_id, signed_value, min_id);
            ((S_800A48F0_0 *)match_slot)->unk_2C = 0;
            ((S_800A48F0_0 *)match_slot)->unk_2D.u = 0;
        } else {
            ((S_800A48F0_0 *)match_slot)->unk_2D.s = (u8) entry_value;
        }
        func_800A4B88(entry_owner, (s8)(id_shift >> 24));
        ASM_SCHED_BARRIER(); /* MATCH: preserve the separate call and shared return tail. */
        result_shift = slot_index << 16;
        goto return_tail;
    }
    slot_index -= 1;
    match_slot -= 2;
    if (slot_index < 0) {
        slot_index = 3;
        id_shift = entry_id << 24;
        insert_id = id_shift >> 24;
        free_slot = entry_owner + 6;
find_free:
        used_id = ((S_800A48F0_1 *)free_slot)->unk_2C;
        if (used_id == 0) {
            {
                void *clear_owner;
                register s32 conflict_id;
                if (insert_id == 1) {
                    clear_owner = entry_owner;
                    conflict_id = 4;
                } else {
                    if (insert_id != 4) {
                        goto insert_entry;
                    }
                    clear_owner = entry_owner;
                    conflict_id = 1;
                }
                func_80042B68(clear_owner, conflict_id);
            }
insert_entry:
            ((S_800A48F0_1 *)free_slot)->unk_2C = entry_id;
            ((S_800A48F0_1 *)free_slot)->unk_2D = entry_value;
            func_800A4B88(entry_owner, (s8)(id_shift >> 24));
            result_shift = slot_index << 16;
            goto return_tail;
        }
        if (used_id < (s16) min_id) {
            min_id = used_id;
        }
        slot_index -= 1;
        free_slot -= 2;
        if (slot_index < 0) {
            register s32 retry_id_shift ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 lowest_id;
            s32 retry_id;

            retry_id_shift = entry_id << 24;
            lowest_id = (s16) min_id;
            retry_id = retry_id_shift >> 24;

            ASM_KEEP_NV(retry_id_shift);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP_NV(lowest_id);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            ASM_KEEP_NV(retry_id);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            if (retry_id < lowest_id) {
                goto replace_entry;
            }

            return -1;

replace_entry:
            func_80042B68(entry_owner, (s8) min_id);
            result_shift = func_800A48F0__self_recurse(entry_owner, (s8)(retry_id_shift >> 24), (s8)entry_value) << 16;
            goto return_tail;
        }
        goto find_free;
    }
    goto find_match;
return_tail:
    return result_shift >> 16;
}
