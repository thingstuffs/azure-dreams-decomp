#include "common.h"

typedef struct TownObject {
    u8 pad0[0x70];
    s16 state;
    s16 value72;
    u8 pad74[2];
    s16 random76;
} TownObject;

typedef struct TownState {
    TownObject *objects[3];
    s16 state;
    s16 timer;
    s16 table_x;
    s16 field12;
    s16 threshold;
    u16 counter;
    s16 table_y;
    u16 flags;
} TownState;

extern u16 D_800135BE;
extern void *D_80020164[6];
extern u8 D_80026F80[];
extern int D_800814A0;
extern u8 D_80082E80[];
extern u32 D_80082E8C;
extern u8 D_80083160[];
extern s16 D_800834C8;
extern s32 D_80083780[];

extern void func_800252B8(s32, s32, s32, s32);
extern void func_80033B78(s32);
extern void func_80033B9C(s32);
extern void func_8003F540(s32, s32, s32, s32);
extern void func_800483AC(s32);
extern void func_80048568(s32);
extern void SD_Call(s32);
extern s32 rand(void);
extern void func_8009AC0C(void);
extern void func_8009AC8C(void);
extern void tw_sd_sq_ld_call(s32, s32);

/* Advances a three-object shuffle sequence and handles its effects and completion. */
void func_80025BC8(TownState *state)
{
    u8 *scene_data;
    s32 phase;
    s32 loop_index;
    s32 particle_x;
    static void *const case_labels[6] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4, &&case_5
    };

    scene_data = D_80083160;
    (void)case_labels;
    if (*(u32 *)(scene_data + 0x10) & 0x40) {
        state->counter = 0;
    }
    state->counter++;

    phase = state->state;
    if ((u32)phase >= 6) {
        goto cleanup;
    }
    goto *D_80020164[phase];

case_0:
    {
        TownState *init_state = state;
        s32 target_offset;
        TownObject *first_object;
        u16 round_delay;

        func_80048568(5);
        func_8009AC0C();
        init_state->state = 1;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        target_offset = -0x80;
        *(s16 *)(scene_data + 0xAC) +=
            (target_offset - *(s16 *)(scene_data + 0xAC)) >> 1;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        first_object = init_state->objects[0];
        if (first_object->state != 1) {
            goto cleanup;
        }
        *(s16 *)(scene_data + 0xAC) = target_offset;
        init_state->counter = 0;
        round_delay = *(u16 *)(D_80026F80 +
                        init_state->table_x * 40 + init_state->table_y * 400);
        init_state->state = 2;
        init_state->timer = round_delay;
        goto cleanup;
    }

case_1:
    D_800834C8 = 0x400;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    {
        u16 flags = state->flags;

        if (flags & 1) {
            state->flags = flags & ~1;
            state->table_x++;
            if (state->table_x >= 10) {
                state->state = 3;
                state->timer = 30;
                goto done;
            }
            state->timer = *(u16 *)(D_80026F80 +
                                    state->table_x * 40 + state->table_y * 400);
            goto done;
        }
    }

    state->timer--;
    if (state->timer > 0) {
        goto cleanup;
    }
    state->flags |= 1;
    do {
        TownObject **object_slot;

        loop_index = 2;
        object_slot = &state->objects[2];
        do {
            (*object_slot)->random76 = rand() % 3;
            object_slot--;
            loop_index--;
        } while (loop_index >= 0);
    } while (state->objects[0]->random76 == state->objects[1]->random76 ||
             state->objects[1]->random76 == state->objects[2]->random76 ||
             state->objects[2]->random76 == state->objects[0]->random76);
    goto cleanup;

case_2:
    if (state->flags & 4) {
        goto cleanup;
    }
    state->timer--;
    if (state->timer > 0) {
        goto cleanup;
    }
    SD_Call(0xB1);
    {
        TownObject **object_slot;
        s32 object_state;

        loop_index = 2;
        object_state = loop_index;
        object_slot = &state->objects[2];
        do {
            u8 *object_body = (u8 *)*object_slot + 0x20;

            object_slot--;
            loop_index--;
            *(s16 *)(object_body + 0x52) = 0;
            *(s16 *)(object_body + 0x50) = object_state;
        } while (loop_index >= 0);
    }
    func_8009AC8C();
    func_8009AC0C();
    state->timer = 25;
    state->state = 4;
    goto cleanup;

case_3:
    if (state->timer < 15) {
        *(s16 *)(scene_data + 0xAC) >>= 1;
    }
    state->timer--;
    if (state->timer >= 0) {
        u8 *color_data = D_80082E80;

        loop_index = 7;
        color_data[0xE] += (0x90 - color_data[0xE]) >> 1;
        color_data[0xD] = color_data[0xE];
        color_data[0xC] = color_data[0xE];
        do {
            particle_x = D_80083780[0] +
                (((rand() & 0x3F) - 0x20) << 16);
            func_800252B8(0xF0F0F0, particle_x,
                          D_80083780[1] +
                              (((rand() & 0x3F) - 0x20) << 16),
                          0);
            loop_index--;
        } while (loop_index >= 0);
    }
    if (state->flags & 2) {
        goto cleanup;
    }
    if (state->timer > 0) {
        goto cleanup;
    }
    *(s16 *)(scene_data + 0xAC) = 0;
    state->state = 5;
    state->flags |= 8;
    goto cleanup;

case_4:
    {
        u16 progress;
        s32 threshold;

        tw_sd_sq_ld_call(0x20, 0x200);
        func_8009AC8C();
        progress = D_800135BE;
        threshold = state->threshold;
        ASM_KEEP(progress);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if ((s16)progress < threshold) {
            func_8003F540(0, 0x2C3D, 0x01000001, 0x01000271);
            SD_Call(0x300);
            D_800135BE = state->threshold;
            func_80033B9C(0xAE4);
        } else {
            func_8003F540(0, 0x2C3D, 0, 0x01000290);
            SD_Call(0x300);
            func_80033B78(0xAE4);
        }
        func_800483AC(2);
        D_80082E8C = 0x00808080;
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto cleanup;
    }

case_5:
cleanup:
    state->flags &= ~6;
done:
    return;
}
