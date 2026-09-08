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
    register s32 held_entry_set ASM_REG("$22") = entry_set;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 start_entry;
    s32 buffer;
    s32 entry_index;
    s32 copied_count;
    register s32 write_ptr ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
    ASM_KEEP(start_entry);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    copy_count -= start_entry;
    if (copy_count >= 9) {
        copy_count = 8;
    }
    ASM_KEEP(held_entry_set);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
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
