#include "common.h"

typedef struct S_80172CC0_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
    u8 pad_49[0x28];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80172CC0_0;   /* state in func_80172CC0 */

typedef struct S_80172CC0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80172CC0_1;   /* arg2 in func_80172CC0 */

typedef struct S_80172CC0_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80172CC0_2;   /* entry in func_80172CC0 */

typedef struct S_80172CC0_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_80172CC0_3;   /* arg0 in func_80172CC0 */

typedef struct S_80172CC0_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80172CC0_4;   /* (u8 *)state + ((S_80172CC0_0 *)state)->unk_8A.s in func_80172CC0 */



extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern s32 func_80173678();

extern s16 D_80083228;
extern u16 D_80083462;
extern s32 D_80175DC4;
extern s32 D_80175DCC;
extern s32 D_80175DD4;

/* Advances the actor along its stored path and updates its movement state. */
void func_80172CC0(void *movement, s32 actor_index, void *actor, void *path_state)
{
    void *state = path_state;
    s32 cell_flags;
    s32 move_result;
    s16 heading;
    s32 x;
    s32 y;
    s32 move_kind;
    s32 path_length;
    unsigned long direction_addr;
    u8 *direction_table;
    u8 *current_table;
    u8 *path_entry;

    if (((S_80172CC0_0 *)state)->unk_71.s <= 0) {
        return;
    }
    path_length = ((S_80172CC0_0 *)state)->unk_71.u;
    if (!(((S_80172CC0_0 *)state)->unk_8A.s < path_length)) {
        return;
    }

    move_kind = ((S_80172CC0_0 *)state)->unk_48;
    if (move_kind == 0xE) {
        goto kind_0e;
    }
    if ((s32)move_kind < 0xF) {
        if (move_kind == 0xD) {
            goto kind_0d;
        }
        goto setup;
    }
    if (move_kind == 0xF) {
        goto kind_0f;
    }
    goto setup;

kind_0d:
    current_table = ((S_80172CC0_1 *)actor)->unk_2C;
    direction_table = (u8 *)&D_80175DC4;
    goto selected_kind;

kind_0e:
    current_table = ((S_80172CC0_1 *)actor)->unk_2C;
    direction_table = (u8 *)&D_80175DCC;
    goto selected_kind;

kind_0f:
    current_table = ((S_80172CC0_1 *)actor)->unk_2C;
    direction_table = (u8 *)&D_80175DD4;

selected_kind:
    if (current_table != direction_table) {
        (*(u8 * *)((u8 *)actor + 0x2C)) = direction_table;
        direction_addr =
            ((D_80083228 + ((S_80172CC0_0 *)state)->unk_2A + 0x100) >> 9) & 7;
        direction_addr += (unsigned long)direction_table;
        func_80047784(actor, *(u8 *)direction_addr, 0);
    }

setup:
    cell_flags = 0x3000;
    x = ((S_80172CC0_1 *)actor)->unk_24;
    y = ((S_80172CC0_1 *)actor)->unk_25;
    if (((S_80172CC0_0 *)state)->unk_1C & 0x2000) {
        cell_flags = 0x300;
    }
    func_8009A3D0(x, y, cell_flags);

    heading = func_800A0818(x, y,
        ((S_80172CC0_4 *)((u8 *)state + ((S_80172CC0_0 *)state)->unk_8A.s))->unk_74,
        ((S_80172CC0_4 *)((u8 *)state + ((S_80172CC0_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)movement + 0x98);
    move_result = (s16)func_8009A66C(heading, actor, state, 0x20);

    path_entry = (u8 *)state + ((S_80172CC0_0 *)state)->unk_8A.s;
    ((S_80172CC0_1 *)actor)->unk_24 = ((S_80172CC0_2 *)path_entry)->unk_74;
    cell_flags = 0x3000;
    path_entry = (u8 *)state + ((S_80172CC0_0 *)state)->unk_8A.s;
    ((S_80172CC0_1 *)actor)->unk_25 = ((S_80172CC0_2 *)path_entry)->unk_7C;
    ((S_80172CC0_0 *)state)->unk_8A.u++;
    {
        s32 next_x = ((S_80172CC0_1 *)actor)->unk_24;
        s32 next_y = ((S_80172CC0_1 *)actor)->unk_25;

        if (((S_80172CC0_0 *)state)->unk_1C & 0x2000) {
            cell_flags = 0x300;
        }
        func_8009A21C(next_x, next_y, cell_flags);
    }

    ASM_KEEP(move_result);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ((S_80172CC0_0 *)state)->unk_2A = heading;
    if (move_result == 3) {
        if (!(D_80083462 & 0x80) && !(((S_80172CC0_1 *)actor)->unk_14 & 0x8000)) {
            func_80173678(movement, actor_index, actor, state);
            ((S_80172CC0_3 *)movement)->unk_8C = 0;
            goto finish_state;
        }
    }

    ((S_80172CC0_3 *)movement)->unk_9A = 0xF;
    ((S_80172CC0_3 *)movement)->unk_8C = 0;

finish_state:
    (*(s32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (D_80083462 & 0x80) {
        ((S_80172CC0_3 *)movement)->unk_96 = 0;
        return;
    }

    ((S_80172CC0_3 *)movement)->unk_96 = 8;
    x = ((S_80172CC0_0 *)state)->unk_71.u;
    if (x > 0) {
        ((S_80172CC0_3 *)movement)->unk_96 = 8 / x;
    }
}
