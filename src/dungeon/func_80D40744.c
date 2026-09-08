#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800A4ACC(void *, s32, s32);
extern s32 D_80083460;
extern u16 D_80083462;

/* Initializes an entity action when the global state permits it. */
void func_80175F44(void *entity, s32 unused_1, s32 unused_2, s32 unused_3, s32 requested_mode)
{
    s32 state_or_flags;
    void *saved_entity = entity;
    u8 flags_71 = FIELD(entity, volatile u8, 0x71);
    register s32 initial_mode ASM_REG("$3") = requested_mode;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 raw_mode;

    flags_71 &= 0x7F;
    ASM_KEEP(flags_71);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    raw_mode = initial_mode;
    ASM_KEEP_NV(initial_mode);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    initial_mode = (s16)initial_mode;
    FIELD(entity, u8, 0x71) = flags_71;
    if (initial_mode != 2) {
        u8 *state = (u8 *)&D_80083460;

        state_or_flags = FIELD(state, u16, 2);
        if (state_or_flags & 0x2000) {
            goto reject_saved;
        }
        if (FIELD(state, void *, 0xC) == entity) {
            goto accepted;
        }
        if (FIELD(state, void *, 0xC) != 0) {
            goto reject_entity;
        }
        if (FIELD(state, void *, 0x10) != 0) {
            goto reject_entity;
        }
        if (!(state_or_flags & 8)) {
            goto accepted;
        }

reject_entity:
        FIELD(entity, u8, 0x9A) = 14;
        goto done;
    }

    state_or_flags = (s32)&D_80083460;
    if (FIELD((void *)state_or_flags, u16, 2) & 0x2000) {
        goto reject_saved;
    }
    if (FIELD((void *)state_or_flags, s16, 0xA) == 0) {
        goto increment_state;
    }

reject_saved:
    FIELD(saved_entity, u8, 0x9A) = 14;
    goto done;

increment_state:
    FIELD((void *)state_or_flags, s16, 0xA) =
        (u16)FIELD((void *)state_or_flags, s16, 0xA) + 1;

accepted:
    {
        s32 mode = (s16)raw_mode;

        if (mode == 0) {
            void *state = (u8 *)&D_80083462 - 2;
            FIELD(state, u16, 0xA)++;
        }
        FIELD(entity, s32, 0x8C) = 0;
        FIELD(entity, s8, 0x9A) = 0x19;
        FIELD(entity, s8, 0x9B) = 0;
        FIELD(entity, s16, 0x96) = 0;
        FIELD(entity, s8, 0xB3) = 0;
        FIELD(entity, s8, 0xB1) = 0;
        FIELD(entity, s8, 0xB2) = 0;
        FIELD(entity, s8, 0xB4) = raw_mode;
        if (mode == 0) {
            ASM_KEEP(mode);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            func_800A4ACC(saved_entity, mode, raw_mode);
            FIELD(saved_entity, u8, 0x6D)--;
        }
    }

done:
    return;
}

