#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8009402C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0xF8];
    void * unk_124;
} S_8009402C_0;   /* arg0 in func_8009402C */


typedef struct S_8009402C_2 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_8009402C_2;   /* temp_v0_2 in func_8009402C */

typedef struct S_8009402C_3 {
    u8 pad_00[0x8A];
    s16 unk_8A;
} S_8009402C_3;   /* tail_base in func_8009402C */

typedef struct S_8009402C_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8009402C_4;   /* temp_v0_3 in func_8009402C */

typedef struct S_8009402C_5 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8009402C_5;   /* ((((S_8009402C_3 *)tail_base)->unk_8A * 4) + arg0) in func_8009402C */

typedef struct DungeonSlot {
    u8 pad_00[0x1C];
    u32 flags;
} DungeonSlot;

M2C_UNK func_80094E34();
M2C_UNK func_8009A21C();
M2C_UNK func_8009A3D0();
s32 func_8009B88C();
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern DungeonSlot *D_800E3DF0[];

/* Check the forward tile and selected slot, then clear the actor action flags on success. */
s32 func_8009402C(void *actor, void *unused, void *position, s16 *out_x, s16 *out_y, void *target) {
    register s32 shifted_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 next_y;
    s16 saved_x;
    s16 saved_y;
    s16 next_x;
    s32 probe_result;
    s32 direction_offset;
    s32 blocked_result;
    s16 *x_coord;
    void *actor_base;
    void *status;
    void *selected_slot;

    actor_base = actor;
    x_coord = out_x;
    if (target != NULL) {
        blocked_result = 3;
        ASM_CLOBBER("$7");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (!(D_800E3DF0[(*(u8 *)((u8 *)target + 3)) & 0x1F]->flags & 0x04000000)) {
            direction_offset = ((u16) ((S_8009402C_0 *)actor)->unk_2A >> 8) & 0xE;
            next_x = ((Rec_D_80082E80 *)position)->unk_24 + *(u16 *)(&D_8006CCD8 + direction_offset);
            next_y = ((Rec_D_80082E80 *)position)->unk_25 + *(u16 *)(&D_8006CCE8 + direction_offset);
            if (((func_8009B88C(0, next_x, next_y, x_coord, out_y) << 0x10) == 0) ||
                ((((S_8009402C_0 *)actor)->unk_1C & 0x100000) &&
                 (status = ((S_8009402C_0 *)actor)->unk_124, (status != NULL)) &&
                 (((S_8009402C_2 *)status)->unk_13 > 0) &&
                 (saved_x = *x_coord, saved_y = *out_y,
                  func_8009A21C(saved_x, saved_y, 0x8000),
                  probe_result = func_8009B88C(0, next_x, next_y, x_coord, out_y),
                  func_8009A3D0(saved_x, saved_y, 0x8000),
                  (shifted_result = probe_result << 0x10, shifted_result == 0)))) {
                return 1;
            }
            goto check_slot;
        }
        return blocked_result;
    }
check_slot:
    selected_slot = ((S_8009402C_5 *)(((((S_8009402C_3 *)actor_base)->unk_8A * 4) + actor)))->unk_AC;
    if ((selected_slot != NULL) && !(((S_8009402C_4 *)selected_slot)->unk_1C & 0x20000)) {
        return 2;
    }
    func_80094E34();
    return 0;
}
