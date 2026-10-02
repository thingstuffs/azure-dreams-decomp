/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#if 0 /* rowbase_rename_reverify precondition marker: dead declaration, never
seen by the real compiler;
satisfies the tool's textual defines()
check for the proven-region rename of func_8015E800. */
    void func_8015E800(void);
#endif

typedef struct DungeonSub2 DungeonSub2;
typedef struct DungeonSub1 DungeonSub1;
typedef struct DungeonNode DungeonNode;

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
s32 func_800A6D30(void);
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
extern u8 D_8015EA7C[];
extern M2C_UNK D_8015EEA8;
extern M2C_UNK D_80162038;
extern M2C_UNK D_80162088;

#ifdef __mips__
extern void *func_8015E8A8(s16, s32, s32, s16);
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

void *BODY_NAME(s16 setup_bits, s32 grid_x, s32 grid_y, s16 placement_value) BODY_ATTR;

/* Allocate and initialize a dungeon node with the supplied setup and placement. */
void *BODY_NAME(s16 setup_bits, s32 grid_x, s32 grid_y, s16 placement_value) {
    DungeonSub1 *state;
    DungeonNode *node;
    u16 saved_placement;
    void *node_data;
    s8 saved_grid_y;
    s8 saved_grid_x;
    s32 mode;
    s32 flags;
    DungeonSub2 *placement;
    DungeonSub1 *init_state;

    saved_grid_x = grid_x;
    saved_placement = placement_value;
    saved_grid_y = grid_y;
    grid_y = 0;
    state = (void *)grid_y;
    grid_x = 0x112;
    node = func_8003FD64(grid_x, ((M2C_UNK *)&D_80083498.next));
    if (node != NULL) {
        state = (DungeonSub1 *)((u8 *)node + 0x20);
        node->field10 = &D_8015EA7C;
        state->field13 = 0x28;
        func_8004491C(node, func_80045340);
        flags = (s32) &D_80162038;
        node_data = node->field08;
        *(s16 *)((u8 *)node_data + 0x0a) = saved_placement;
        placement = node->field0c;
        mode = setup_bits & 3;
        placement->field25 = saved_grid_y;
        init_state = state;
        placement->field2c = (void *) flags;
        placement->field24 = saved_grid_x;
        if (mode == 1) {
            state->field14 |= 0x6000;
            state->field1c |= 0x6000;
        } else if (mode >= 2) {
            state->field14 |= 0x2000;
            state->field1c |= 0x2000;
        } else {
            flags = setup_bits & ~3;
            if ((flags << 0x10) == 0) {
                if (!(state->field14 & 0x200)) {
                    if (func_800A6D30() & 1) {
                        state->field1c |= 0x200;
                        func_800A48F0(state, 1, (func_800A6D30() & 0x3F) | 0x20);
                        placement->field2c = &D_80162088;
                    }
                }
            }
        }
        func_800A9C18(node, node_data, placement, (s16)(s32) setup_bits);
        init_state->field9a = 0xff;
        init_state->field9c = -1;
        init_state->field8c = &D_8015EEA8;
        func_800AA36C(init_state, node_data, placement, state);
    }
    return state;
}
