#include "shared/sprite_frame_state.h"
#include "shared/minigame_body.h"
#include "common.h"
#include "shared/entity_objects.h"
extern int abs(int);

typedef struct S_80023A00_0 {
    u8 pad_00[0x18];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    u8 pad_1A[0x10];
    u16 unk_2A;
} S_80023A00_0;   /* arg0 in func_80023A00 */


typedef struct S_80023A00_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80023A00_3;   /* caller_obj in func_80023A00 */


typedef struct {
    s32 words[6];
} Copy24;

extern void func_800211C4(void *, void *, void *);
extern void func_80047784(void *, s32, s32);
extern void func_800478B8(void *);

extern s32 D_80081458[];
extern s16 D_80083228;
extern u8 D_80083220[];

extern u8 D_800D2398[];
extern u8 D_800D23A0[];

/* Updates entity state and selects direction-dependent table entries. */
void func_80023A00(void *object, void *output, void *entity_data)
{
    u8 *caller_obj = object;
    u8 *output_bytes = output;
    u8 *state_base = (u8 *)&D_800834B8;
    s32 state;
    s32 initial_magnitude;
    s32 magnitude;
    u8 *direction_table;

    func_800478B8(entity_data);
    *(Copy24 *)output_bytes = *(Copy24 *)((u8 *)(&D_80083780));
    ((S_80023A00_0 *)object)->unk_2A =
        (0x1400 - (*(u16 *)&((MinigameBody *)state_base)->unk_10)) & 0xFFF;

    state = ((S_80023A00_0 *)object)->unk_18.s;
    switch (state) {
    case 0:
        ((S_80023A00_0 *)object)->unk_18.u++;
        return;

    case 1:
        initial_magnitude = D_80081458[0];
        ((SpriteFrameState *)entity_data)->frameTable = D_800D23A0;
        ((SpriteFrameState *)entity_data)->unk_28 = initial_magnitude;
        func_80047784(entity_data,
            D_800D23A0[((D_80083228 +
                ((S_80023A00_3 *)caller_obj)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80023A00_0 *)object)->unk_18.u++;
        /* fallthrough */
    case 2:
        if (((MinigameBody *)state_base)->unk_08 == 2) {
            (*(void * *)((u8 *)entity_data + 0x2C)) = D_800D2398;
            func_80047784(entity_data,
                D_800D2398[((*(s16 *)(D_80083220 + 8) +
                    ((S_80023A00_3 *)caller_obj)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_80023A00_0 *)object)->unk_18.u++;
        }
        break;

    case 3:
        magnitude = ((MinigameBody *)state_base)->unk_48;
        magnitude = abs(magnitude);
        if (0xFFFF >= magnitude) {
            (*(void * *)((u8 *)entity_data + 0x2C)) = D_800D23A0;
            func_80047784(entity_data,
                D_800D23A0[((D_80083228 + ((S_80023A00_3 *)caller_obj)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_80023A00_0 *)object)->unk_18.u++;
        }
        break;

    case 4:
        magnitude = ((MinigameBody *)state_base)->unk_48;
        magnitude = abs(magnitude);
        if (0xFFFF < magnitude) {
            direction_table = D_800D2398;
            (*(void * *)((u8 *)entity_data + 0x2C)) = direction_table;
            func_80047784(entity_data,
                direction_table[((D_80083228 + ((S_80023A00_3 *)caller_obj)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_80023A00_0 *)object)->unk_18.u--;
        }
        break;
    }

    if (((S_80023A00_0 *)object)->unk_18.s != 0) {
        func_800211C4(caller_obj, object, entity_data);
    }

    return;
}
