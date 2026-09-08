#include "common.h"

typedef struct S_808B2E74_0 {
    u8 pad_00[0xF1C];
    s16 unk_F1C;
} S_808B2E74_0;   /* (u32)D_A0700000 + index in func_808B2E74 */



extern u8 D_A0700000[];

/* Clears bitmap bits for three pairs of stored IDs. */
void func_808B2E74(void)
{
    s32 slot = 1;
    s32 bit_one = 1;
    s16 *first_id_ptr = (s16 *)(D_A0700000 + 0xF26);
    register s32 slot_offset ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    do {
        s32 first_id;
        register s32 first_bits ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u8 *first_byte ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u8 *state_base;

        first_id = *first_id_ptr;
        slot_offset = slot << 1;
        first_bits = first_id;
        if (first_id < 0)
            first_bits = first_id + 31;
        state_base = (u8 *)0xA0700000;
        first_byte = *(u8 **)(state_base + 0xF40);
        first_bits >>= 5;
        first_byte += first_bits;
        first_bits = first_id - (first_bits << 5);
        first_bits = bit_one << first_bits;
        *first_byte &= ~first_bits;
        {
            s32 second_id;
            register s32 second_bits ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            u8 *second_byte;
            register u8 *second_state_base;
            second_id = ((S_808B2E74_0 *)((u32)D_A0700000 + slot_offset))->unk_F1C;
            second_bits = second_id;
            if (second_id < 0)
                second_bits = second_id + 31;
            first_id_ptr = (s16 *)((u8 *)first_id_ptr + 2);
            slot += 1;
            second_state_base = (u8 *)0xA0700000;
            second_byte = *(u8 **)(second_state_base + 0xF40);
            second_bits >>= 5;
            second_byte += second_bits;
            second_bits = second_id - (second_bits << 5);
            second_bits = bit_one << second_bits;
            *second_byte &= ~second_bits;
        }
    } while (slot < 4);
}
