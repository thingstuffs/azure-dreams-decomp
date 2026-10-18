#include "common.h"
void func_80067014(s32);                     /* extern */
void func_800672D8(void *, s32);                  /* extern */
extern s16 D_80083D78[];


typedef struct S_800B5B20_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_800B5B20_0;

typedef struct DisplayTransferState {
    u8 pad_00[8];
    s16 slot_index;
    u16 texture_slot;
    u8 pad_0C[4];
    union { s32 palette_offset; u16 palette_slot; } palette;
    void *texture;
    u8 pad_18[0xB8];
    s32 transfer_phase;
    s32 transfer_pending;
    u8 pad_D8[8];
    s32 data;
} DisplayTransferState;

/* Transfer pending texture and palette data, then clear the transfer state. */
void complete_display_transfer(void *texture_state) {
    s32 table_index;
    struct { s16 x; s16 y; s16 w; s16 h; } rect;
    void *state = texture_state;
    void *texture;
    s16 *slot_table;

    if (((DisplayTransferState *)state)->transfer_pending != 0) {
        func_80067014(0);
        slot_table = D_80083D78;
        table_index = ((DisplayTransferState *)state)->slot_index;
        texture = ((DisplayTransferState *)state)->texture;
        ((DisplayTransferState *)state)->transfer_phase = 0;
        ((DisplayTransferState *)state)->transfer_pending = 0;
        slot_table[table_index * 2] = ((DisplayTransferState *)state)->texture_slot;
        slot_table[(((DisplayTransferState *)state)->slot_index * 2) + 1] = ((DisplayTransferState *)state)->palette.palette_slot;

        rect.x = ((u8) ((S_800B5B20_0 *)texture)->unk_08 >> 2) + ((((S_800B5B20_0 *)texture)->unk_04 << 6) & 0x3C0);
        rect.y = ((S_800B5B20_0 *)texture)->unk_09 + ((((S_800B5B20_0 *)texture)->unk_04 * 0x10) & 0x100);
        rect.w = (s16) ((u8) ((S_800B5B20_0 *)texture)->unk_0A >> 2);
        rect.h = (s16) ((S_800B5B20_0 *)texture)->unk_0B;
        func_800672D8(&rect, ((DisplayTransferState *)state)->data);
        if (((DisplayTransferState *)state)->slot_index != 0) {
            u16 palette_y;
            s32 palette_offset;
            s32 data_base;

            rect.x = (((S_800B5B20_0 *)texture)->unk_06 & 0x3F) * 0x10;
            palette_y = ((S_800B5B20_0 *)texture)->unk_06;
            rect.w = 0x10;
            rect.h = 1;
            palette_y >>= 6;
            rect.y = (s16) palette_y;

            palette_offset = ((DisplayTransferState *)state)->palette.palette_offset;
            data_base = ((DisplayTransferState *)state)->data;
            palette_offset <<= 5;
            palette_offset += 0x200;

            func_800672D8(&rect, data_base + palette_offset);
        }
        func_80067014(0);
    }
    ((DisplayTransferState *)state)->data = 0;
}
