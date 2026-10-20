#include "common.h"

extern void call_script(void *value);
extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
extern void func_800988C8(void *block, s32 header_param_08, s32 header_param_0c);
extern void clear_entity_record_fields(s32 record);

extern u8 D_8006CADE[];
extern u8 D_800834B8[];
extern u8 D_800D0078[];

/* Set the block's 12-bit value and apply its header parameters. */
void set_player_block_value(s32 value)
{
    void *block;
    void *header;
    s32 header_param_0c;
    s32 header_param_08;

    block = D_800834B8;
    header = (s8 *)block - 0x20;
    header_param_08 = *(s32 *)((s8 *)header + 8);
    header_param_0c = *(s32 *)((s8 *)header + 0xC);
    clear_entity_record_fields(header_param_08);
    *(s16 *)((s8 *)block + 0x10) = value & 0xFFF;
    call_the_handler_selects_nonzero_entry(D_800D0078, block, header_param_0c);
    func_800988C8(block, header_param_08, header_param_0c);
    call_script(D_8006CADE);
}
