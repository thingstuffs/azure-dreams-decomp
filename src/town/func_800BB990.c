#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef struct
{
    u8 x;
    u8 y;
    u8 w;
    u8 h;
    u8 pad[2];
    u8 id;
    u8 pad7;
}
Entry;
extern u8 D_800D3814[12];
extern u8 D_800D2EA4[];
extern u8 D_80082E60[];
extern u16 D_80082E76;
extern s8 D_800D381A;
extern s32 func_80041094();
/* Passes the selected entry's bottom-center coordinates to func_80041094 and clears the selection. */
void func_800B90F0(void)
{
    s32 entry_index = 0x20;
    u8 *selection_state = D_800D3814;
    u8 *shared_state = D_80082E60;
    u8 *entries = D_800D2EA4;
    u8 *entry = entries + 0x100;
    u8 *id_cursor = (u8 *) 0x80010040;
    u8 *fallback_entries;
    u8 *fallback_entry;
scan_entries:
    entry_index--;

    if (id_cursor[0x33A4] == selection_state[6]) {
        func_80041094(0xB, ((entry[0] + (entry[2] >> 1)) << 6) | 0x20, ((entry[1] + entry[3]) << 6) | 0x20, 0,
            (*((u16 *) (&shared_state[0x16]))) ^ 1);
        selection_state[6] = 0;
        return;
    }
    entry -= 8;
    id_cursor -= 2;
    if (entry_index <= 0) {
        fallback_entries = D_800D2EA4;
        fallback_entry = fallback_entries + (entry_index * 8);
        func_80041094(0xB, ((fallback_entry[0] + (fallback_entry[2] >> 1)) << 6) | 0x20,
            ((fallback_entry[1] + fallback_entry[3]) << 6) | 0x20, 0, D_80082E76 ^ 1);
        D_800D381A = 0;
        return;
    }
    goto scan_entries;
}
