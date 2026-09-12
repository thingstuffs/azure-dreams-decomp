#include "common.h"

#include "common.h"

typedef struct S_8004F684_Target {
    /* 0x00 */ u8 pad[0xA];
    /* 0x0A */ s16 field_A;
    /* 0x0C */ s16 field_C;
} S_8004F684_Target;

typedef struct S_8004F684_Obj {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ S_8004F684_Target *target;
} S_8004F684_Obj;

typedef struct S_8004F684_Entry {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ S_8004F684_Obj *obj;
} S_8004F684_Entry;

typedef struct S_8004F684 {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ S_8004F684_Entry *entries[8];
    /* 0x24 */ s32 count;
    /* 0x28 */ s32 divisor;
    /* 0x2C */ s32 multiplier;
    /* 0x30 */ s32 idxB;
    /* 0x34 */ s32 idxA;
} S_8004F684;

extern u8 D_80071784[];

/* Interpolate table values into each target's fields with scales of 30 and 12 and fixed offsets. */
void func_8004F684(S_8004F684 *state)
{
    S_8004F684 *settings;
    s32 entry_index;
    u8 *value_row;
    S_8004F684_Entry **entry_slot;
    s32 start_value;
    s32 value_delta;
    s32 scaled_weight;
    s32 offset;   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    s32 offset2;
    s32 offset3;
    s32 target_value;
    void *entry_or_target;
    S_8004F684_Obj *obj;

    settings = state;
    entry_index = 0;
    if (settings->count > 0) {
        value_row = D_80071784;
        entry_slot = (S_8004F684_Entry **)settings;
        do {
            start_value = value_row[settings->idxA];
            value_delta = value_row[settings->idxB] - start_value;

            scaled_weight = settings->multiplier * 30;
            offset = (value_delta * scaled_weight) / settings->divisor;
            entry_or_target = entry_slot[1];
            obj = ((S_8004F684_Entry *)entry_or_target)->obj;
            target_value = start_value * 30;
            offset2 = offset + 0x200;
            target_value = target_value + offset2;
            ((S_8004F684_Target *)obj->target)->field_C = (s16)target_value;

            scaled_weight = settings->multiplier * 12;
            offset2 = (value_delta * scaled_weight) / settings->divisor;
            entry_slot++;
            entry_index++;
            entry_or_target = obj->target;
            target_value = start_value * 12;
            offset3 = offset2 - 0x40;
            target_value = target_value + offset3;
            ((S_8004F684_Target *)entry_or_target)->field_A = (s16)target_value;

            value_row += 3;
        } while (entry_index < settings->count);
    }
    ASM_KEEP(entry_index);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
}
