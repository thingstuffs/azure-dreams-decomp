#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) UA32;

extern s8 D_80016000[];
extern UA32 D_8001C31C;

/* Copies the header and coordinate entries, flags entries whose grid field is zero, and appends a terminator. */
UA32 *func_80018B64(UA32 *buffer)
{
    UA32 *result;
    u8 *global_page;
    u8 *grid_rows;
    u32 header_page;
    register UA32 *header ASM_REG("$7");   /* MATCH pin: retail delay-slot fill depends on it */
    UA32 **entry_ptr;
    register u8 *write_ptr ASM_REG("$7");   /* MATCH pin: retail delay-slot fill depends on it */
    u8 *entry_list;
    u8 *state;
    u8 y;
    u8 x;
    u8 *grid_row;

    result = buffer;
    global_page = (u8 *)0x80010000;
    ASM_KEEP(global_page);   /* MATCH pin: keeps a constant in a register as retail does */
    state = *(u8 **)(global_page + 0x6000);
    grid_rows = *(u8 **)(*(u8 **)(state + 0x24) + 0x6C);
    header_page = 0x80020000;
    ASM_KEEP(header_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    header = (UA32 *)(header_page - 0x3CE4);
    ASM_KEEP(header);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    *result = *header;
    ASM_KEEP(header_page);   /* MATCH pin: keeps a statement from moving across a call/branch */

    state = *(u8 **)(global_page + 0x6000);
    entry_list = *(u8 **)(state + 0x38);
    entry_ptr = (UA32 **)(entry_list + 0x29C);
    write_ptr = (u8 *)result + 4;
    if (*(UA32 **)(entry_list + 0x29C) != 0) {
        do {
            *(UA32 *)write_ptr = **entry_ptr;
            y = write_ptr[1];
            grid_row = (u8 *)((u32)(y * 0x14) + (u32)grid_rows);
            x = write_ptr[0];
            if (*(s16 *)(*(u8 **)(grid_row + 0xC) + (x * 0x14) + 0x12) == 0) {
                write_ptr[3] |= 0x80;
            }
            entry_ptr++;
            write_ptr += 4;
        } while (*entry_ptr != 0);
    }
    *(s32 *)write_ptr = 0;
    return result;
}

