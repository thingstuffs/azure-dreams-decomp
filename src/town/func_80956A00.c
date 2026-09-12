#include "common.h"
extern int abs(int);

typedef struct S_80023A00_0 {
    u8 pad_00[0x18];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    u8 pad_1A[0x10];
    u16 unk_2A;
} S_80023A00_0;   /* arg0 in func_80023A00 */

typedef struct S_80023A00_1 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x6];
    u16 unk_10;
    u8 pad_12[0x36];
    s32 unk_48;
} S_80023A00_1;   /* state_base in func_80023A00 */

typedef struct S_80023A00_2 {
    u8 pad_00[0x28];
    s32 unk_28;
    void * unk_2C;
} S_80023A00_2;   /* entity in func_80023A00 */

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

extern void *D_800201A0[];
extern s32 D_80081458[];
extern s16 D_80083228;
extern u8 D_80083220[];
extern s32 D_800834B8;
extern u8 D_80083780[];
extern u8 D_800D2398[];
extern u8 D_800D23A0[];

/* Updates entity state and selects direction-dependent table entries. */
void func_80023A00(void *object, void *output, void *entity_data)
{
    u8 *caller_obj = object;
    u8 *output_bytes = output;
    register u8 *entity ASM_REG("$18") = entity_data;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *state_base = (u8 *)&D_800834B8;
    s32 state;
    s32 initial_magnitude;
    s32 magnitude;
    u8 *direction_table;
    static void *const switch_keep[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4
    };

    func_800478B8(entity);
    *(Copy24 *)output_bytes = *(Copy24 *)D_80083780;
    ((S_80023A00_0 *)object)->unk_2A =
        (0x1400 - ((S_80023A00_1 *)state_base)->unk_10) & 0xFFF;

    state = ((S_80023A00_0 *)object)->unk_18.s;
    if ((u32)state >= 5) {
        goto common;
    }
    (void)switch_keep;
    goto *D_800201A0[state];

case_0:
    ((S_80023A00_0 *)object)->unk_18.u++;
    goto done;

case_1:
    initial_magnitude = D_80081458[0];
    ((S_80023A00_2 *)entity)->unk_2C = D_800D23A0;
    ((S_80023A00_2 *)entity)->unk_28 = initial_magnitude;
    func_80047784(entity,
        D_800D23A0[((D_80083228 +
            ((S_80023A00_3 *)caller_obj)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80023A00_0 *)object)->unk_18.u++;
    if (((S_80023A00_1 *)state_base)->unk_08 != 2) {
        goto common;
    }
    (*(void * *)((u8 *)entity + 0x2C)) = D_800D2398;
    func_80047784(entity,
        D_800D2398[((*(s16 *)(D_80083220 + 8) +
            ((S_80023A00_3 *)caller_obj)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80023A00_0 *)object)->unk_18.u++;
    goto common;

case_2:
    magnitude = ((S_80023A00_1 *)state_base)->unk_48;
    magnitude = abs(magnitude);
    if (0xFFFF < magnitude) {
        goto common;
    }
    (*(void * *)((u8 *)entity + 0x2C)) = D_800D23A0;
    func_80047784(entity,
        D_800D23A0[((D_80083228 + ((S_80023A00_3 *)caller_obj)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80023A00_0 *)object)->unk_18.u++;
    goto common;

case_3:
    magnitude = ((S_80023A00_1 *)state_base)->unk_48;
    magnitude = abs(magnitude);
    if (0xFFFF >= magnitude) {
        goto common;
    }
    direction_table = D_800D2398;
    (*(void * *)((u8 *)entity + 0x2C)) = direction_table;
    func_80047784(entity,
        direction_table[((D_80083228 + ((S_80023A00_3 *)caller_obj)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80023A00_0 *)object)->unk_18.u--;
    goto common;

case_4:
common:
    if (((S_80023A00_0 *)object)->unk_18.s != 0) {
        func_800211C4(caller_obj, object, entity);
    }

done:
    return;
}
