#include "common.h"

typedef s32 (*TownCallback3)(void *, void *, s32);
typedef s32 (*TownCallback1)(s32);
typedef struct { u8 tag; u8 pad[0x13]; } TownRec;

typedef struct TownGlobals {
    u8 pad_0000[0x3514];
    u8 data3514[0x28];
    u8 data353C[4048];
    u8 data450C[0xB4];
    void *table[12];
    s32 flag45F0;
    u8 pad45F4[0x10];
    void *state4604;
    u8 pad4608[4];
    s32 *lookup460C;
    void *callbacks4610;
} TownGlobals;

extern TownGlobals D_town_data_view __asm__("D_00000000");
extern TownGlobals D_town_ptr_view __asm__("D_00000000");
extern TownGlobals D_town_flag_load_view __asm__("D_00000000");

extern s32 func_80003DCC(void);

/* Runs setup callbacks, chooses the mode-specific record list, and remaps fields until the terminator. */
void run_setup_and_remap_mode_records(s32 table_index, s32 mode) {
    void *entry_ptr;
    s32 sentinel;
    s32 i;
    TownRec *rec;
    if (D_town_flag_load_view.flag45F0 != 0) {
        (*(TownCallback3 *)((u8 *)D_town_ptr_view.callbacks4610 + 0x64))(
            D_town_data_view.data3514, D_town_ptr_view.data353C, 0xE1);
        (*(TownCallback1 *)((u8 *)D_town_ptr_view.callbacks4610 + 0x70))(1);
    }
    D_town_data_view.flag45F0 = 1;
    func_80003DCC();
    if (mode == 2) {
        *(void **)((u8 *)D_town_ptr_view.state4604 + 0x10) = D_town_ptr_view.data450C;
    } else {
        *(void **)((u8 *)D_town_ptr_view.state4604 + 0x10) = D_town_ptr_view.table[table_index];
    }
    entry_ptr = *(void **)((u8 *)D_town_ptr_view.state4604 + 0x10);
    if (*((u8 *)entry_ptr + 1) != 0x80) {
        sentinel = 0x80;
        rec = (TownRec *)((u8 *)entry_ptr + 1);
        i = 0;
        do {
            *(s32 *)((u8 *)&rec[i] + 0xB) =
                D_town_ptr_view.lookup460C[*(s32 *)((u8 *)&rec[i] + 0xB)];
            i++;
        } while (rec[i].tag != sentinel);
    }
}
