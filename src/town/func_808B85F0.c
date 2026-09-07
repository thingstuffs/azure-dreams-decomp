#include "common.h"

typedef s32 (*TownCallback3)(void *, void *, s32);
typedef s32 (*TownCallback1)(s32);
typedef struct { u8 pad[0xB]; s32 word_B; } TownEntry;

typedef struct { u8 pad[0x3514]; u8 data[1]; } Data3514;
typedef struct { u8 pad[0x353C]; u8 data[1]; } Data353C;
typedef struct { u8 pad[0x450C]; u8 data[1]; } Data450C;
typedef struct { u8 pad[0x45C0]; void *table[12]; } Table45C0;
typedef struct { u8 pad[0x45F0]; s32 value; } Flag45F0;
typedef struct { u8 pad[0x4604]; void *value; } State4604;
typedef struct { u8 pad[0x460C]; s32 *value; } Lookup460C;
typedef struct { u8 pad[0x4610]; void *value; } Callbacks4610;

extern Data3514 D_data_3514 __asm__("D_00000000");
extern Data353C D_data_353C __asm__("D_00000000");
extern Data450C D_data_450C __asm__("D_00000000");
extern Table45C0 D_table_45C0 __asm__("D_00000000");
extern Flag45F0 D_flag_load_45F0 __asm__("D_00000000");
extern Flag45F0 D_flag_store_45F0 __asm__("D_00000000");
extern State4604 D_state_4604 __asm__("D_00000000");
extern Lookup460C D_lookup_460C __asm__("D_00000000");
extern Callbacks4610 D_callbacks_4610 __asm__("D_00000000");

extern s32 func_80003DCC(void);
extern void func_80003EAC(void) __attribute__((noreturn));

void func_808B85F0(s32 arg0, s32 arg1) {
    volatile u8 *var_a0;
    void *temp_a0;
    s32 sentinel;
    if (D_flag_load_45F0.value != 0) {
        (*(TownCallback3 *)((u8 *)D_callbacks_4610.value + 0x64))(
            D_data_3514.data, D_data_353C.data, 0xE1);
        (*(TownCallback1 *)((u8 *)D_callbacks_4610.value + 0x70))(1);
    }
    D_flag_store_45F0.value = 1;
    func_80003DCC();
    if (arg1 == 2) {
        *(void **)((u8 *)D_state_4604.value + 0x10) = D_data_450C.data;
        func_80003EAC();
    }
    *(void **)((u8 *)D_state_4604.value + 0x10) = D_table_45C0.table[arg0];
    temp_a0 = *(void **)((u8 *)D_state_4604.value + 0x10);
    var_a0 = (volatile u8 *)temp_a0;
    if (*((u8 *)var_a0 + 1) != 0x80) {
        sentinel = 0x80;
        var_a0 = (volatile u8 *)((u8 *)var_a0 + 1);
        do {
            *(volatile s32 *)((u8 *)var_a0 + 0xB) =
                D_lookup_460C.value[*(volatile s32 *)((u8 *)var_a0 + 0xB)];
            var_a0 = (volatile u8 *)((u8 *)var_a0 + 0x14);
        } while (*(u8 *)var_a0 != sentinel);
    }
}
