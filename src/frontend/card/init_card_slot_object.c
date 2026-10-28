#include "common.h"
#include "frontend/card/slot_assert_bytes.h"
#include "frontend/card.h"
#include "main/data.h"





extern s32 func_8003C714(s32 option, void *object, s32 param);
extern void func_80040560(s32 object, void *data);
extern s32 func_80047FD8(void *object);
extern void func_8007BEF0(s32 value);
extern void func_8007BFE0(void *object, s32 value);
extern void func_8007C040(void *first_ptr, void *second_ptr, s32 value);
extern s32 func_804075A8(s32 context);
extern s32 func_804075D0(void *object, s32 value);
extern u32 func_80407688(void *object, s32 option);
extern void assert_card_slot_and_set_high_bit(void *card_slot);


typedef struct S_800206C8_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800206C8_0;   /* base in func_800206C8 */

typedef struct S_800206C8_1 {
    u8 pad_00[0x5C];
    s32 unk_5C;
    s32 unk_60;
} S_800206C8_1;   /* slot_state in func_800206C8 */

/* Initializes the memory card slot object and its working state. */
void *init_card_slot_object(s32 init_option)
{
    S_800206C8_0 *base;
    S_800206C8_1 *slot_state;

    base = (S_800206C8_0 *)D_8040C318;
    slot_state = (S_800206C8_1 *)(D_8040C318 + 0x20);
    if (func_80047FD8(base) == 0) {
        base = (void *)(unsigned long)func_8003C714(0, base, 0x42);
        if (base == 0) {
            func_8007C040(card_slot_assert_format, card_slot_filename, 0x136);
            func_8007BEF0(1);
        }
        func_80040560((s32)(unsigned long)base, card_status_query_address);
    } else {
        assert_card_slot_and_set_high_bit(base);
        D_8040C336 &= 0x7FFF;
        func_8007BFE0(slot_state, 0xE4);
    }
    func_804075D0(slot_state, 4);
    base->unk_0C = (s32)(unsigned long)((u8 *)slot_state + 0x50);
    slot_state->unk_5C = func_804075A8(slot_state->unk_60);
    func_80407688(slot_state, init_option);
    base->unk_10 = (s32)(unsigned long)D_80407298;
    return base;
}
