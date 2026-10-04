#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct S_81978428_0 {
    u8 pad_00[0xF4];
    s32 unk_F4;
} S_81978428_0;   /* init_page in func_81978428 */

typedef struct S_81978428_1 {
    u16 unk_00;
} S_81978428_1;   /* self->part4 in func_81978428 */

typedef struct S_81978428_2 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0xE];
    u16 unk_A6;
    u8 unk_A8;
} S_81978428_2;   /* case0_global in func_81978428 */

typedef struct S_81978428_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_81978428_3;   /* angle_global in func_81978428 */

typedef struct S_81978428_5 {
    u8 pad_00[0x2A];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
} S_81978428_5;   /* player in func_81978428 */

typedef struct S_81978428_6 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_81978428_6;   /* work in func_81978428 */

typedef struct S_81978428_7 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_81978428_7;   /* fallback in func_81978428 */

typedef struct S_81978428_8 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_81978428_8;   /* case3_object in func_81978428 */

typedef struct S_81978428_9 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_81978428_9;   /* after_object in func_81978428 */

typedef struct S_81978428_10 {
    u8 pad_00[0xC];
    u32 unk_0C;
} S_81978428_10;   /* after_aux in func_81978428 */

typedef struct S_81978428_12_pre {
    u16 unk_00;
} S_81978428_12_pre;   /* the 0x2 bytes before self in func_81978428, addressed as self[-1] */



typedef struct {
    void *part0;
    void *part4;
    u8 kind;
    u8 effect;
    s16 state;
    u8 pad0C[2];
    u16 angle;
    u16 counter;
    u8 pad12[2];
    void *object;
    s16 timer;
    s16 flag;
} State81978428;

typedef struct {
    s16 pad0;
    u16 x;
    s16 pad4;
    u16 y;
    s16 pad8;
    s16 z;
    u8 pad0C[8];
} Scratch81978428;


extern void func_800243C0(void *, void *);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern void *func_800A05A4();
extern u16 func_800BCAD0(void *);
extern s32 func_800A45D8(u16, u16, s16);
extern void func_80025A9C(void *, void *, void *);
extern void func_80025508(void *, void *);
extern void func_8009CE1C(void *, s32, u8, s32, s16, void *, s32);

/* Advances the object effect through placement, animation, and cleanup states. */
void func_81978428(State81978428 *state, s32 *position_out)
{
    State81978428 *self = state;
    s32 *position = position_out;
    void *target_pos;
    s32 step_count;
    u8 *tile_map;
    u8 *tint_data;
    Scratch81978428 fallback_pos;
    void *spawned_object;
    u16 timer;
    s32 state_index;
    s32 tile_step;
    s32 tile_step_2;
    s32 tile_step_3;
    s32 tile_step_4;

    timer = self->counter;
    state_index = self->state;
    timer++;
    self->counter = timer;
    switch (state_index) {
    case 0:
        {
            u8 *init_page;
            u16 next_state;

            next_state = self->state;
            init_page = (u8 *)D_800814A8;
            self->counter = 0;
            next_state++;
            self->state = next_state;
            ((S_81978428_0 *)init_page)->unk_F4 = 0;
            func_800243C0((u8 *)self->part0 - 0x20, self->part4);
        }
    case 1:
        {
            u8 *player_page;
            u8 *player_state;
            u8 *facing_player;

            if ((((S_81978428_1 *)(self->part4))->unk_00 & 0x80) == 0) {
                break;
            }
            player_page = (u8 *)0x80080000;
            player_state = *(u8 **)(player_page + 0x14A8);
            self->timer = 10;
            ((S_81978428_2 *)player_state)->unk_96 = 8;
            ((S_81978428_2 *)player_state)->unk_A6--;
            ((S_81978428_2 *)player_state)->unk_A8 = self->kind;
            facing_player = *(u8 **)(player_page + 0x14A8);
            self->angle = ((S_81978428_3 *)facing_player)->unk_2A;
            self->state++;
            if (func_80053EF0(4) != 2) {
                func_800A56E0(0x300);
                break;
            }
            func_800A56E0(0x4300);
            break;
        }

    case 2:
        timer = self->timer;
        timer--;
        self->timer = timer;
        if ((s32)((u32)timer << 16) > 0) {
            break;
        }

        {
            u8 *player;
            s32 spawn_angle;
            s32 player_x;
            player_x = D_80083780.x.v;
            player = (u8 *)D_800814A8;
            position[0] = player_x;
            position[1] = D_80083780.y.v;
            position[2] = (s32)((S_81978428_5 *)player)->unk_88.s << 16;
            spawn_angle = ((S_81978428_5 *)player)->unk_2A.s;
            tile_map = (u8 *)&D_80082E80;
            spawned_object = func_800A05A4(player, tile_map[0x24], tile_map[0x25], spawn_angle, 8);
        }
        self->object = spawned_object;
        if (spawned_object != 0) {
            target_pos = *(void **)((u8 *)spawned_object - 0x18);
        } else {
            target_pos = &fallback_pos;
            {
                u8 tile_x;
                u8 tile_y;

                tile_x = tile_map[0x24];
                ((S_81978428_6 *)target_pos)->unk_02.s = (tile_x << 6) + 0x20;
                tile_y = tile_map[0x25];
                ((S_81978428_6 *)target_pos)->unk_06.s = (tile_y << 6) + 0x20;
            }

            for (step_count = 0; step_count < 8; step_count++) {
                {
                    u8 *player;

                    player = (u8 *)D_800814A8;
                    tile_step = dirStepX[(((S_81978428_5 *)player)->unk_2A.u >> 9) & 7];
                    ((S_81978428_6 *)target_pos)->unk_02.u += tile_step << 6;
                    tile_step_2 = dirStepY[(((S_81978428_5 *)player)->unk_2A.u >> 9) & 7];
                    ((S_81978428_6 *)target_pos)->unk_06.u += tile_step_2 << 6;
                    ((S_81978428_6 *)target_pos)->unk_0A.s = ((S_81978428_5 *)player)->unk_88.u;
                }
                ((S_81978428_6 *)target_pos)->unk_0A.s = func_800BCAD0(target_pos);
                if (((S_81978428_6 *)target_pos)->unk_0A.u >= 0x201) {
                    u8 *player;
                    player = (u8 *)D_800814A8;
                    ((S_81978428_6 *)target_pos)->unk_0A.s = ((S_81978428_5 *)player)->unk_88.u;
                }

                if ((func_800A45D8(((S_81978428_6 *)target_pos)->unk_02.s, ((S_81978428_6 *)target_pos)->unk_06.s,
                                    ((S_81978428_6 *)target_pos)->unk_0A.u) << 16) != 0) {
                    u8 *player;

                    player = (u8 *)D_800814A8;
                    tile_step_3 = dirStepX[(((S_81978428_5 *)player)->unk_2A.u >> 9) & 7];
                    ((S_81978428_6 *)target_pos)->unk_02.u -= tile_step_3 << 6;
                    tile_step_4 = dirStepY[(((S_81978428_5 *)player)->unk_2A.u >> 9) & 7];
                    ((S_81978428_6 *)target_pos)->unk_06.u -= tile_step_4 << 6;
                    ((S_81978428_6 *)target_pos)->unk_0A.s = ((S_81978428_5 *)player)->unk_88.u;
                    ((S_81978428_6 *)target_pos)->unk_0A.s = func_800BCAD0(target_pos);
                    if (((S_81978428_6 *)target_pos)->unk_0A.u >= 0x201) {
                        u8 *height_player;
                        height_player = (u8 *)D_800814A8;
                        ((S_81978428_6 *)target_pos)->unk_0A.s = ((S_81978428_7 *)height_player)->unk_88;
                    }
                    break;
                }
            }
        }

        func_80025A9C(self, position, target_pos);
        {
            u16 next_state = self->state;
            u16 wait_frames;
            wait_frames = 0x10;
            self->timer = wait_frames;
            self->state = next_state + 1;
        }
        break;

    case 3:
        timer = self->timer;
        timer--;
        self->timer = timer;
        if ((s32)((u32)timer << 16) > 0) {
            break;
        }
        {
            u16 next_state = 0x18;
            void *spawned_object;

            self->timer = next_state;
            next_state = self->state;
            spawned_object = self->object;
            next_state++;
            self->state = next_state;
            if (spawned_object != 0) {
                func_80025508(self, *(void **)((u8 *)spawned_object - 0x18));
            }
        }
        break;

    case 4:
        {
            u8 *tinted_object = self->object;

            if (tinted_object != 0) {
                u8 *reloaded_object;
                s16 tint_timer;

                ((S_81978428_8 *)tinted_object)->unk_1C |= 0x10000000;
                tint_timer = self->timer;
                reloaded_object = *(u8 **)((u8 *)self + 0x14);
                tint_data = *(u8 **)(reloaded_object - 0x14);
                if (tint_timer >= 0xC) {
                    u8 blue = tint_data[0xE] + 8;
                    tint_data[0xE] = blue;
                    if (tint_data[0xC] >= 0xE1) {
                        tint_data[0xC] = 0xE0;
                    }
                } else {
                    u8 blue = tint_data[0xE] - 8;
                    tint_data[0xE] = blue;
                    if (blue < 0x80) {
                        tint_data[0xE] = 0x80;
                    }
                }
            }
        }

        {
            u32 map_flags = D_80082E80.unk_014;
            if ((map_flags & 0x8000) == 0) {
                timer = self->timer;
                timer--;
                self->timer = timer;
                if ((s32)((u32)timer << 16) >= 0) {
                    break;
                }
            }
        }

        {
            u8 *effect_object = self->object;

            if (effect_object != 0) {
                s32 effect_size = 10;
                s32 effect_scale;
                effect_scale = effect_size;
                func_8009CE1C(self->object, effect_size, self->effect, effect_scale,
                              (s16)((self->angle << 9) + 0x800), self->part0, 1);
                {
                    u32 clear_tint_mask = 0xEFFFFFFF;
                    u32 neutral_color = 0x00808080;
                    u8 *reset_object = self->object;
                    tint_data = *(u8 **)(reset_object - 0x14);

                    ((S_81978428_9 *)reset_object)->unk_1C &= clear_tint_mask;
                    ((S_81978428_10 *)tint_data)->unk_0C = neutral_color;
                }
            }
        }
        if (self->flag != 0) {
            self->state++;
            break;
        }
        dungeonStatus.unk_0C = 0;
        dungeonStatus.unk_0A--;
        ((S_81978428_12_pre *)self)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;

    case 5:
        if (self->flag != 0) {
            break;
        }

        dungeonStatus.unk_0C = 0;
        dungeonStatus.unk_0A--;
        ((S_81978428_12_pre *)self)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }
    self->flag = 0;
}
