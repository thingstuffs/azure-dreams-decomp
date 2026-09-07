#include "common.h"

extern s32 func_80026EC0();
extern s32 func_80026F04();
extern s32 func_8004B404();
extern void strncpy();

typedef struct {
    u8 bytes[0x13];
} Entry19;

/* Copy up to eight selected entries into a packed buffer of 18-byte records. */
s32 func_80027008(s32 entry_set, s32 position, s32 entry_count) {
    register s32 held_entry_set ASM_REG("$22") = entry_set;   /* MATCH pin: retail address form (%hi/%lo vs entries+offset) depends on it */
    s32 start_entry;
    s32 buffer;
    s32 entry_index;
    s32 copied_count;
    register s32 write_ptr ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    s32 copy_count;
    Entry19 *entries;

    entry_index = position;
    entry_index /= 72;
    copy_count = entry_count;
    buffer = func_8004B404(0x91);
    if (buffer == 0) {
        goto end;
    }
    start_entry = entry_index * 8;
    ASM_KEEP(start_entry);   /* MATCH pin: load-bearing for the whole function shape */
    copy_count -= start_entry;
    if (copy_count >= 9) {
        copy_count = 8;
    }
    ASM_KEEP(held_entry_set);   /* MATCH pin: retail schedule: same instructions, different order without it */
    entry_index = func_80026EC0(held_entry_set, start_entry);
    copied_count = 0;
    if (copy_count > 0) {
        entries = (Entry19 *)0x800157C0;
        write_ptr = buffer;
        do {
            strncpy(write_ptr,
                    (u8 *)((u32)(entry_index * 0x13) + (u32)entries), 0x12);
            entry_index = func_80026F04(held_entry_set, entry_index + 1);
            copied_count += 1;
            write_ptr += 0x12;
        } while (copied_count < copy_count);
    }
end:
    return buffer;
}

/* MECHANISM: The in-place /72 quotient forces the retail 0x30 frame and s0/s3/s6 argument holds.
   Exact callee arity plus guarded a1/s2 runtime roles reproduce the return-slot and loop coloring.
   Integer index-first addition preserves the retail addu a1,a1,s5 operand order. */
