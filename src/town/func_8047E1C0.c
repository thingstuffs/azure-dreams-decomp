/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800175E0();
extern M2C_UNK D_8001624C;
extern M2C_UNK D_800177C8;
extern M2C_UNK *D_8001794C[3];
extern M2C_UNK D_8001802A;
extern u8 D_80010000[];

typedef void (*TownCall)(s32, s32, void *);

typedef struct S_func_8047E1C0_0 {
    u8 pad_00[0x6000];
    void *unk_6000;
} S_func_8047E1C0_0;

typedef struct S_func_8047E1C0_1 {
    u8 pad_00[0x08];
    s32 unk_08;
    u8 pad_0C[0x10];
    void *unk_1C;
    void *unk_20;
    u8 pad_24[0x1C];
    s32 unk_40;
} S_func_8047E1C0_1;

typedef struct S_func_8047E1C0_2 {
    u8 pad_00[0x40];
    void *unk_40;
} S_func_8047E1C0_2;

typedef struct S_func_8047E1C0_3 {
    u8 pad_00[0x2EC];
    TownCall unk_2EC;
} S_func_8047E1C0_3;

/* Updates town state pointers and dispatches a town call. */
void func_8047E1C0(void) {
    void *state_data;
    s32 call_code;
    register S_func_8047E1C0_3 *dispatch_table ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    call_code = 0x3B0;
    state_data = &D_8001802A;
    ((S_func_8047E1C0_2 *)((S_func_8047E1C0_1 *)(*(void **)((u8 *)D_80010000 + 0x6000)))->unk_1C)->unk_40 = state_data;
    dispatch_table = *(void **)((u8 *)(*(void **)((u8 *)D_80010000 + 0x6000)) + 0x20);
    *(volatile M2C_UNK **)&D_8001794C[0] = &D_800177C8;
    dispatch_table->unk_2EC(call_code, 0x100, (*(void **)((u8 *)D_80010000 + 0x6000)));
    func_800175E0(0x98);
    *(void **)((s8 *)((S_func_8047E1C0_1 *)(*(void **)((u8 *)D_80010000 + 0x6000)))->unk_40 + ((S_func_8047E1C0_1 *)(*(void **)((u8 *)D_80010000 + 0x6000)))->unk_08 * 8) = &D_8001624C;
}
