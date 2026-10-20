#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef s32 (*TownPairCallback)(s32, s32);
typedef s32 (*EventOpcodeHandler)(void);

void reset_dispatch_state_and_flags();                            /* extern */
void process_history_entries_by_mode(void);                            /* extern */
void func_8001E578(s32);                     /* extern */
void func_8001E5F0(s32);                     /* extern */
s32 func_8001E670();                             /* extern */
extern s16 D_800178BA[0x10];
extern EventOpcodeHandler D_800178E8[0x100];
extern s32 D_8001E95C[0x10];

typedef struct S_80019560_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x1C];
    s32 unk_40;
} S_80019560_0;   /* *(void **)D_80016000 in run_event_opcode_script */

/* Update script flags and dispatch opcodes until a handler returns a result. */
void run_event_opcode_script(s32 setup_arg0, s32 setup_arg1, s32 setup_arg2, s32 setup_arg3) {
    s32 opcode_result;
    u32 state_page_addr;
    u8 *state_page;
    EventOpcodeHandler *opcode_handlers;

    process_history_entries_by_mode();
    if (func_8001E670(F_end_ending_step0) != 0) {
        if (func_8001E670(F_guy_sword_pickup) == 0) {
            func_8001E578(F_sbs01_pad20);
        } else {
            func_8001E5F0(F_sbs01_pad20);
        }
        if (func_8001E670(F_ultima_egg_pickup) == 0) {
            if (((TownPairCallback *)((u8 *)((S_80019560_0 *)(*(void **)((s8 *)(&D_80016000))))->unk_20 + 0x350))[0](1,
                0x12) != 0) {
                func_8001E578(F_ultima_egg_pickup);
                func_8001E5F0(F_sbs01_pad21);
                state_page_addr = 0x80020000;
            } else {
                func_8001E578(F_sbs01_pad21);
                state_page_addr = 0x80020000;
            }
        } else {
            func_8001E5F0(F_sbs01_pad21);
            state_page_addr = 0x80020000;
        }
    } else {
        func_8001E5F0(F_sbs01_pad20);
        func_8001E5F0(F_sbs01_pad21);
        state_page_addr = 0x80020000;
    }
    state_page = (u8 *)state_page_addr;
    opcode_handlers = D_800178E8;
    *(u8 **)(state_page - 0x16B0) = ((S_80019560_0 *)(*(void **)((s8 *)(&D_80016000))))->unk_40 + 8;
    do {
        state_page_addr = opcode_handlers[**(u8 **)(state_page - 0x16B0)]();
        opcode_result = state_page_addr;
    } while (opcode_result == 0);
    D_8001E95C[0] = opcode_result;
    if (func_8001E670(D_800178BA[0]) == 0) {
        reset_dispatch_state_and_flags();
    }
}
