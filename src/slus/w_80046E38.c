#include "common.h"

typedef struct Info80046E38 {
    s32 *data;
    u16 count;
} Info80046E38;

typedef struct Pair80046E38 {
    s32 first;
    s32 second;
} Pair80046E38;

typedef struct State80046E38 {
    u8 pad[10];
    u8 mode;
    u8 tail;
} State80046E38;

extern s32 DrawSync(s32);
extern void Control_CD(s32, s32 *, s32);
extern void func_8003F320(void);
extern void func_8003F6D4(s32, s32, s32 *, s32);
extern u8 *func_8004068C(u8 *, u8 *);
extern void func_80046D64(u8 *, s16);

extern Info80046E38 *D_8006E7F0[];
extern s32 D_80080A7C;
extern u8 *D_80081480;
extern u8 *D_8008148C[3];
extern State80046E38 D_80082E60;

/* Processes the selected entry stream and updates the drawing buffer and mode mask. */
void func_80046E38(s16 entry_id, u8 *stream)
{
    Pair80046E38 pair;
    u8 *stream_pos;
    u8 *stream_start;
    s32 buffer_start;
    s32 data_offset;
    s32 remaining;
    register u8 *table_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    s32 table_offset;
    s32 shifted_id;
    Info80046E38 **entry_slot;
    Info80046E38 *entry;
    s32 *entry_data;

    stream_pos = stream;
    ASM_KEEP_NV(stream_pos);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    stream_start = stream;
    D_80081480 = D_8008148C[0];
    buffer_start = (s32)D_8008148C[0];
    DrawSync(0);

    shifted_id = entry_id << 16;
    table_base = (u8 *)D_8006E7F0;
    table_offset = shifted_id >> 14;
    entry_slot = (Info80046E38 **)(table_offset + (u32)table_base);
    entry_data = (*entry_slot)->data;
    pair = *(Pair80046E38 *)entry_data;
    entry = *entry_slot;
    remaining = entry->count;
    data_offset = entry->data[1];

    if (remaining > 0) {
        do {
            Control_CD(6, (s32 *)&pair, 0);
            data_offset += 0x10;
            func_8003F320();
            stream_pos = func_8004068C(D_8008148C[-3], stream_pos);
            remaining--;
            func_8003F6D4(0x10, 0, (s32 *)&pair, data_offset);
        } while (remaining > 0);
    }

    func_80046D64(stream_start, entry_id);
    {
        u32 state_page;

        state_page = 0x80080000;
        ASM_KEEP_NV(state_page);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
        shifted_id = *(u8 *)(state_page + 0x2E6A);
        {
            s32 mode_mask;

            mode_mask = 2;
            if (shifted_id != mode_mask) {
                D_80080A7C = 0x8000;
            } else {
                D_80080A7C = 0x4000;
            }
        }
    }
    D_80081480 = (u8 *)((buffer_start + 3) & ~3);
}
