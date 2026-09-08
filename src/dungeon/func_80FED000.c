/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#if 0 /* rowbase_rename_reverify precondition marker: dead declaration, never
         seen by the real compiler; satisfies the tool's textual defines()
         check for the proven-region rename of func_8015E800. */
void func_8015E800(void);
#endif

typedef struct DungeonSub2 DungeonSub2;
typedef struct DungeonSub1 DungeonSub1;
typedef struct DungeonNode DungeonNode;
typedef union DungeonArgBits DungeonArgBits;

union DungeonArgBits {
    void *p;
    s32 i;
};

struct DungeonSub2 {
    u8 pad00[0x24];
    s8 field24;
    s8 field25;
    u8 pad26[6];
    void *field2c;
};

struct DungeonNode {
    u8 pad00[8];
    void *field08;
    DungeonSub2 *field0c;
    void *field10;
    u8 pad14[0x0c];
};

struct DungeonSub1 {
    u8 pad00[0x13];
    s8 field13;
    s32 field14;
    u8 pad18[4];
    s32 field1c;
    u8 pad20[0x6c];
    void *field8c;
    u8 pad90[0x0a];
    u8 field9a;
    u8 pad9b[1];
    s8 field9c;
};

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern u8 D_8015EA7C[];
extern M2C_UNK D_8015EEA8;
extern M2C_UNK D_80162038;
extern M2C_UNK D_80162088;

#ifdef __mips__
extern void *func_8015E8A8(s32, s8, s8, s16);
extern void *func_8015F2B8(void);
extern void *func_8015F2E4(void);
extern void *func_8015F264(void);
extern void *func_8015F1F4(void);
extern void *func_8015F1E4(void);
extern void *func_8015F2A8(void);
extern void *func_80160AC4(void);
extern void *func_80160ABC(void);
extern void *func_80160AB4(void);
extern void *func_80160ACC(void);
extern void *func_80160A74(void);
extern void *func_80160A6C(void);
extern void *func_80160A64(void);

static const u32 data_prefix[] __asm__("func_8015E800")
    __attribute__((section(".text.func_8015E800"), aligned(4))) = {
    (u32)func_8015E8A8,
    (u32)D_8015EA7C,
    (u32)func_8015F2B8,
    (u32)func_8015F2B8,
    (u32)func_8015F2B8,
    (u32)func_8015F2E4,
    (u32)func_8015F264,
    (u32)func_8015F264,
    (u32)func_8015F264,
    (u32)func_8015F1F4,
    (u32)func_8015F1E4,
    (u32)func_8015F2E4,
    (u32)func_8015F2E4,
    (u32)func_8015F2A8,
    (u32)func_80160AC4,
    (u32)func_80160ABC,
    (u32)func_80160AB4,
    (u32)func_80160ACC,
    (u32)func_80160A74,
    (u32)func_80160A6C,
    (u32)func_80160A64,
    0x89824081,
    0x40819382,
    0x93829082,
    0x83829982,
    0x85828882,
    0x7C818482,
    0x90829582,
    0x00004481,
    0x92824081,
    0x96828582,
    0x81828582,
    0x85828C82,
    0x40818482,
    0x94828982,
    0x40819382,
    0x92829482,
    0x85829582,
    0x90824081,
    0x97828F82,
    0x92828582,
    0x74004481,
};
__asm__(".globl func_8015E800\n"
        ".size func_8015E800, 636");
#define BODY_NAME func_8015E8A8
#define BODY_ATTR __attribute__((section(".text.func_8015E800")))
#else
#define BODY_NAME func_8015E800
#define BODY_ATTR
#endif

void *BODY_NAME(s32 setup_bits, s8 grid_x, s8 grid_y, s16 placement_value) BODY_ATTR;

/* Allocate and initialize a dungeon node with the supplied setup and placement. */
void *BODY_NAME(s32 setup_bits, s8 grid_x, s8 grid_y, s16 placement_value) {
    s32 unused_byte_neg_d58;
    s32 unused_byte_a64;
    s32 unused_slot_24;
    s32 unused_slot_28;
    s32 mode;
    register s32 call_count ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *call_target ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *check_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s8 saved_grid_x;
    s16 saved_placement;
    s8 saved_grid_y;
    DungeonSub2 *placement;
    register void *node_data ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    DungeonNode *node;
    DungeonSub1 *state;
    DungeonSub1 *init_state;
    register void *setup_alias ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    DungeonArgBits saved_setup;
    s32 state_flags;
    register s32 status_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 setup_mask ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    state = NULL;
    call_count = 0x112;
    saved_grid_x = grid_x;
    call_target = &D_80083498;
    saved_placement = placement_value;
    saved_grid_y = grid_y;
    ASM_KEEP_DEP_NV(saved_grid_x, call_count);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_DEP_NV(saved_placement, call_target);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_DEP_NV(saved_grid_y, call_target);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    unused_byte_a64 = (s32) *(s8 *)0xA64;
    unused_byte_neg_d58 = (s32) *(s8 *)-0xD58;
    node = func_8003FD64(call_count, call_target);
    if (node != NULL) {
        setup_alias = (void *) setup_bits;
        do {
            saved_setup.p = (void *) setup_bits;
        } while (0);
        state = (DungeonSub1 *)((u8 *)node + 0x20);
        node->field10 = &D_8015EA7C;
        state->field13 = 0x28;
        func_8004491C(node, &D_80045340);
        node_data = node->field08;
        *(s16 *)((u8 *)node_data + 0x0a) = saved_placement;
        placement = node->field0c;
        mode = (s32) setup_alias & 3;
        placement->field25 = saved_grid_y;
        init_state = state;
        placement->field2c = &D_80162038;
        placement->field24 = saved_grid_x;
        if (mode == 1) {
            state_flags = state->field14;
            status_flags = state->field1c;
            state_flags |= 0x6000;
            status_flags |= 0x6000;
            goto store_flags;
        }
        else if (mode >= 2) {
            state_flags = state->field14;
            status_flags = state->field1c;
            state_flags |= 0x2000;
            status_flags |= 0x2000;
store_flags:
            state->field14 = state_flags;
            state->field1c = status_flags;
            goto final_call;
        }
        setup_mask = ((s32) setup_alias & ~3) << 0x10;
        if (setup_mask == 0) {
            check_obj = node;
            if (!(state->field14 & 0x200)) {
                call_target = node_data;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
                if (func_800A6D30(check_obj, call_target) & 1) {
                    state->field1c |= 0x200;
                    func_800A48F0(state, 1, (func_800A6D30(check_obj) & 0x3F) | 0x20);
                    placement->field2c = &D_80162088;
                }
            }
        }
final_call:
        func_800A9C18(node, node_data, placement, (s16) saved_setup.i);
        init_state->field9a = 0xff;
        init_state->field9c = -1;
        init_state->field8c = &D_8015EEA8;
        func_800AA36C(init_state, node_data, placement, state);
    }
    return state;
}
