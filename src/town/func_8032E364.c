#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef struct {
    u32 value;
} __attribute__((packed)) UA32;

extern UA32 D_8001C31C;

/* Copies the header and coordinate entries, flags entries whose grid field is zero, and appends a terminator. */
UA32 *func_80018B64(UA32 *buffer)
{
    UA32 *result;
    u8 *global_page;
    u8 *grid_rows;
    u32 header_page;
    UA32 *header;
    UA32 **entry_ptr;
    u8 *write_ptr;
    TownStateRecord *entry_list;
    Rec_D_80016000 *state;
    u8 y;
    u8 x;

    result = buffer;
    global_page = (u8 *)0x80010000;
    state = D_80016000;
    grid_rows = *(u8 **)(state->unk_24 + 0x6C);
    header_page = 0x80020000;
    header = &D_8001C31C;
    *result = *header;

    state = D_80016000;
    entry_list = state->unk_38;
    entry_ptr = (UA32 **)entry_list->entries;
    write_ptr = (u8 *)result + 4;
    if (*(UA32 **)entry_list->entries != 0) {
        do {
            {
                *(UA32 *)write_ptr = **entry_ptr;
                y = write_ptr[1];
                x = write_ptr[0];
                if (*(s16 *)(*(u8 **)(grid_rows + y * 0x14 + 0xC) + (x * 0x14) + 0x12) == 0) {
                    write_ptr[3] |= 0x80;
                }
                entry_ptr++;
                write_ptr += 4;
            }
        } while (*entry_ptr != 0);
    }
    *(s32 *)write_ptr = 0;
    return result;
}

