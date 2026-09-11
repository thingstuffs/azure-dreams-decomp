#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
void func_800A56E0(s32, void *);
extern M2C_UNK D_80046398;
extern void *D_800814A8;
extern s8 D_80083160[];
extern s8 D_800B1F34[];

typedef struct S_800B2074_0 {
    u8 pad_00[0x1DC];
    s32 unk_1DC;
    u8 pad_1E0[0x10];
    s16 unk_1F0;
} S_800B2074_0;   /* temp_s4 in func_800B2074 */

typedef struct S_800B2074_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    u16 * unk_20;
} S_800B2074_1;   /* temp_v0 in func_800B2074 */

typedef struct S_800B2074_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800B2074_2;   /* temp_v1 in func_800B2074 */

typedef struct S_800B2074_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_800B2074_3;   /* temp_a1 in func_800B2074 */

typedef struct S_800B2074_4 {
    s16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_800B2074_4;   /* temp_s0 in func_800B2074 */

typedef struct S_800B2074_5 {
    u8 pad_00[0xE];
    u16 unk_0E;
    u8 pad_10[0x1A];
    u16 unk_2A;
} S_800B2074_5;   /* temp_dest in func_800B2074 */

/* Creates an object at the given map position and updates its tile record. */
void func_800B2074(s32 world_x, s32 world_z) {
    s32 tile_addr;
    void *object;
    s32 pos_x;
    s32 pos_z;
    void *init_object;
    void *init_data;
    void *callback;
    S_800B2074_5 *state_fields;
    register u16 inherited_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s8 *map_state;
    S_800B2074_3 *transform;
    S_800B2074_2 *render_state;

    pos_x = world_x;
    pos_z = world_z;
    map_state = D_80083160;
    tile_addr = ((S_800B2074_0 *)map_state)->unk_1DC;
    object = func_8003FC64(0x12);
    if (object != NULL) {
        init_object = object;
        ASM_KEEP(init_object);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        callback = D_800B1F34;
        init_data = &D_80046398;
        ASM_KEEP(init_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_800B2074_1 *)object)->unk_10 = callback;
        func_8004491C(init_object, init_data);
        render_state = ((S_800B2074_1 *)object)->unk_0C;
        render_state->unk_20 = 0x1000;
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        render_state->unk_08 = 2;
        render_state->unk_0C = 0x808080;
        transform = ((S_800B2074_1 *)object)->unk_08;
        transform->unk_16 = 6;
        transform->unk_02 = pos_x;
        transform->unk_06 = pos_z;
        tile_addr += (((s32) (pos_x << 0xA) >> 0x10) + (((s32) (pos_z << 0xA) >> 0x10) << ((S_800B2074_0 *)map_state)->unk_1F0)) * 6;
        do {
            ((S_800B2074_1 *)object)->unk_20 = (u16 *) (tile_addr + 2);
        } while (0);
        ((S_800B2074_4 *)tile_addr)->unk_00 = 3;
        transform->unk_0A = (s16) (0 - *((S_800B2074_1 *)object)->unk_20);
        ((S_800B2074_4 *)tile_addr)->unk_02 = (u16) (((S_800B2074_4 *)tile_addr)->unk_02 + 0x20);
        ((S_800B2074_4 *)tile_addr)->unk_04 = (u16) (((S_800B2074_4 *)tile_addr)->unk_04 | 1);
        func_800A56E0(0x603, transform);
        state_fields = D_800814A8;
        inherited_value = state_fields->unk_2A;
        state_fields = object + 0x20;
        ASM_KEEP(state_fields);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        state_fields->unk_0E = inherited_value;
    }
}
