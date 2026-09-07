#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80077854;
extern M2C_UNK D_801714AC;
extern s16 D_80173AFC[];
extern void *D_80175D54;
extern void *D_80175DB8;

typedef struct S_801715D0_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801715D0_0;   /* D_80175D54 in func_801715D0 */

typedef struct S_801715D0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801715D0_1;   /* temp_v0 in func_801715D0 */

typedef struct S_801715D0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_801715D0_2;   /* temp_v1 in func_801715D0 */

typedef struct S_801715D0_3 {
    u8 pad_00[0x24];
    void * unk_24;
    u8 pad_28[0x30];
    s8 unk_58;
    s8 unk_59;
} S_801715D0_3;   /* temp_s3 in func_801715D0 */

typedef struct S_801715D0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801715D0_4;   /* temp_a0 in func_801715D0 */

typedef struct S_801715D0_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801715D0_5;   /* temp_s2 in func_801715D0 */

typedef struct S_801715D0_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801715D0_6;   /* temp_s1 in func_801715D0 */

typedef struct S_801715D0_7 {
    s16 unk_00;
    s16 unk_02;
} S_801715D0_7;   /* entry in func_801715D0 */

typedef struct S_801715D0_8 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_801715D0_8;   /* temp_v1_2 in func_801715D0 */

/* Creates and initializes an object offset in its owner's facing direction. */
void func_801715D0(void) {
    s32 owner_x;
    s32 owner_y;
    s32 tile_x;
    s32 tile_y;
    register S_801715D0_4 *object_pos ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    S_801715D0_6 *owner_state;
    S_801715D0_5 *owner_pos;
    u8 *direction;
    u8 *direction_table;
    register S_801715D0_3 *object_state ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *object;
    S_801715D0_2 *render_flags;
    register S_801715D0_8 *sprite ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

    owner_pos = ((S_801715D0_0 *)D_80175D54)->unk_08;
    owner_state = D_80175D54 + 0x20;
    object = func_8003FD64(0x12, D_80175D54);
    if (object != NULL) {
        ((S_801715D0_1 *)object)->unk_10 = &D_801714AC;
        func_8004491C(object, &D_80045340);
        render_flags = ((S_801715D0_1 *)object)->unk_0C;
        object_state = object + 0x20;
        render_flags->unk_14 = (u16) ((render_flags->unk_14 & 0xFFF3) | 0x80);
        object_state->unk_24 = owner_state;
        object_pos = ((S_801715D0_1 *)object)->unk_08;
        object_pos->unk_02 = (u16) owner_pos->unk_02;
        object_pos->unk_06 = (u16) owner_pos->unk_06;
        object_pos->unk_0A = (u16) owner_pos->unk_0A;
        direction_table = (u8 *) 0x80170000;
        ASM_KEEP(direction_table);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        direction_table += 0x3AFC;
        direction = (u8 *) ((u32) (((u16) owner_state->unk_2A >> 7) & 0x1C) + (u32) direction_table);
        object_pos->unk_02 = (u16) (object_pos->unk_02 + (((S_801715D0_7 *)direction)->unk_00 * 6));
        direction = (u8 *) ((u32) (((u16) owner_state->unk_2A >> 7) & 0x1C) + (u32) direction_table);
        object_pos->unk_06 = (u16) (object_pos->unk_06 + (((S_801715D0_7 *)direction)->unk_02 * 6));
        sprite = ((S_801715D0_1 *)object)->unk_0C;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        owner_x = (s16) owner_pos->unk_02;
        tile_x = owner_x - 0x20;
        if (tile_x < 0) {
            tile_x = (s32) (owner_x + 0x1F) >> 6;
        } else {
            tile_x >>= 6;
        }
        object_state->unk_58 = (s8) tile_x;
        owner_y = (s16) owner_pos->unk_06;
        tile_y = owner_y - 0x20;
        if (tile_y < 0) {
            tile_y = (s32) (owner_y + 0x1F) >> 6;
        } else {
            tile_y >>= 6;
        }
        object_state->unk_59 = (s8) tile_y;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        sprite->unk_08 = &D_80077854;
        D_80175DB8 = object;
    }
}

/* MECHANISM: Last-use pins hold the object+0x20 base in s3 and the a0/v0/v1 live-range roles, yielding the retail 0x28 frame.
   A held 0x80170000 page plus addiu 0x3AFC prevents the direction_table low half from folding into its signed halfword loads.
   Named integer-form index+base sums preserve addu v0,v0,a1; shared v0 normalization and u8 color stores close the tail. */
