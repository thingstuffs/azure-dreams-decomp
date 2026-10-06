#include "common.h"

typedef s32 (*TownCallback3)(void *, void *, s32);
typedef s32 (*TownCallback1)(s32);
typedef struct { u8 tag; u8 pad[0x13]; } TownRec;

typedef struct { u8 pad[0x3514]; u8 data[1]; } Data3514;
typedef struct { u8 pad[0x353C]; u8 data353C[4048]; u8 data450C[1]; } DataPair;
typedef struct { u8 pad[0x45F0]; s32 value; } Flag45F0;
typedef struct { u8 pad[0x45C0]; void *table[12]; u8 pad45F0[0x14]; void *state4604; u8 pad4608[4]; s32 *lookup460C; void *callbacks4610; } Ptrs4604;

extern Data3514 D_data_3514 __asm__("D_00000000");
extern DataPair D_pair __asm__("D_00000000");
extern Ptrs4604 D_ptrs __asm__("D_00000000");
extern Flag45F0 D_flag_load_45F0 __asm__("D_00000000");
extern Flag45F0 D_flag_store_45F0 __asm__("D_00000000");

extern s32 func_80003DCC(void);
extern void func_80003EAC(void) __attribute__((noreturn));

/* Optionally fires two setup callbacks, then either takes a noreturn exit for mode 2 or selects a table entry and remaps each record's field through a lookup table until the terminator tag. */
void func_808B85F0(s32 table_index, s32 mode) {
    void *entry_ptr;
    s32 sentinel;
    s32 i;
    TownRec *rec;
    if (D_flag_load_45F0.value != 0) {
        (*(TownCallback3 *)((u8 *)D_ptrs.callbacks4610 + 0x64))(
            D_data_3514.data, D_pair.data353C, 0xE1);
        (*(TownCallback1 *)((u8 *)D_ptrs.callbacks4610 + 0x70))(1);
    }
    D_flag_store_45F0.value = 1;
    func_80003DCC();
    if (mode == 2) {
        *(void **)((u8 *)D_ptrs.state4604 + 0x10) = D_pair.data450C;
        func_80003EAC();
    }
    *(void **)((u8 *)D_ptrs.state4604 + 0x10) = D_ptrs.table[table_index];
    entry_ptr = *(void **)((u8 *)D_ptrs.state4604 + 0x10);
    if (*((u8 *)entry_ptr + 1) != 0x80) {
        sentinel = 0x80;
        rec = (TownRec *)((u8 *)entry_ptr + 1);
        i = 0;
        do {
            *(s32 *)((u8 *)&rec[i] + 0xB) =
                D_ptrs.lookup460C[*(s32 *)((u8 *)&rec[i] + 0xB)];
            i++;
        } while (rec[i].tag != sentinel);
    }
}
