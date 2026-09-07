#include "common.h"

typedef struct S_81960530_0 {
    u8 pad_00[0x140];
    union { s16 s; u16 u; } unk_140;   /* accessed as both */
    union { s16 s; u16 u; } unk_142;   /* accessed as both */
    s32 unk_144;
    s32 unk_148;
    s32 unk_14C;
    s16 unk_150;
    union { s16 s; u16 u; } unk_152;   /* accessed as both */
    union { struct { u32 v; } at00; struct { s16 v; } at00u; struct { u16 v; } at00p; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_154;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { s16 v; } at00u; struct { u16 v; } at00p; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_158;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { s16 v; } at00u; struct { u16 v; } at00p; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_15C;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { s16 v; } at00u; struct { u16 v; } at00p; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_160;   /* overlapping accesses */
} S_81960530_0;   /* scratch in func_81960530 */

typedef struct S_81960530_1 {
    u8 pad_00[0x4];
    u8 ** unk_04;
    u8 * unk_08;
    u8 * unk_0C;
    u8 pad_10[0x4];
    s16 unk_14;
} S_81960530_1;   /* pshift in func_81960530 */

typedef struct S_81960530_2 {
    u16 unk_00;
    u16 unk_02;
} S_81960530_2;   /* map_entry in func_81960530 */

typedef struct S_81960530_3 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_81960530_3;   /* best in func_81960530 */

typedef struct S_81960530_4 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x8];
    u16 unk_10;
    u8 pad_12[0x4];
    u8 unk_16;
    union { u8 u; s8 s; } unk_17;   /* accessed as both */
} S_81960530_4;   /* current in func_81960530 */

typedef struct S_81960530_5 {
    u32 unk_00;
} S_81960530_5;   /* copy_vertex in func_81960530 */

typedef struct S_81960530_6 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_81960530_6;   /* plane_ptr in func_81960530 */

typedef struct S_81960530_7 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_81960530_7;   /* dot_vertex in func_81960530 */

typedef struct S_81960530_8 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_81960530_8;   /* planes + ((S_81960530_3 *)best)->unk_10 * 8 in func_81960530 */

typedef struct S_81960530_9 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_81960530_9;   /* planes + ((S_81960530_4 *)current)->unk_10 * 8 in func_81960530 */


extern u8 D_8008333C[32];

#if 0
extern void func_80026018(void) __attribute__((noreturn));
#endif
extern void func_80026018(void);
extern s32 func_800BCE7C(void *);


void *func_81960530(s32 arg0, s32 arg1, s16 arg2) {
    u8 *scratch;
    u8 *current;
    u8 *vertices;
    u8 *planes;
    u8 *best;
    u8 *map_entry;
    u8 *copy_vertex;
    u8 *dot_vertex;
    u8 *pshift;
    u8 *plane_ptr;
    s16 cell;
    s32 value;
    u16 x;
    u16 y;

    scratch = (u8 *)0x1F800000;
    ((S_81960530_0 *)scratch)->unk_148 = 0x400;
    ((S_81960530_0 *)scratch)->unk_140.s = arg0 & 0x3F;
    ((S_81960530_0 *)scratch)->unk_142.s = arg1 & 0x3F;
    ((S_81960530_0 *)scratch)->unk_14C = arg2;

    cell = (u16)arg0 >> 6;
    ((S_81960530_0 *)scratch)->unk_150 = cell;
    pshift = D_8008333C;
    cell += ((u16)arg1 >> 6) << ((S_81960530_1 *)pshift)->unk_14;
    (*(s16 *)((u8 *)scratch + 0x150)) = cell;
    map_entry = (u8 *)((long)cell * 6 + (unsigned long)*(u8 **)D_8008333C);
    vertices = ((S_81960530_1 *)pshift)->unk_08;
    planes = ((S_81960530_1 *)pshift)->unk_0C;
    best = 0;
    if (((S_81960530_2 *)map_entry)->unk_00 != 0) {
      ((S_81960530_0 *)scratch)->unk_152.s = -((S_81960530_2 *)map_entry)->unk_02;
      best = (*(u8 * *)((u8 *)(((S_81960530_1 *)pshift)->unk_04) + ((S_81960530_2 *)map_entry)->unk_00 * 4));
      current = best;
      if (((S_81960530_8 *)(planes + ((S_81960530_3 *)best)->unk_10 * 8))->unk_04 < -0x7FF) {
      do {
        if ((((S_81960530_4 *)current)->unk_17.u & 1) == 0) {
            x = ((S_81960530_0 *)scratch)->unk_140.u;
            y = ((S_81960530_0 *)scratch)->unk_142.u;

            copy_vertex = (u8 *)((unsigned long)((S_81960530_4 *)current)->unk_00 * 8 + (unsigned long)vertices);
            ((S_81960530_0 *)scratch)->unk_154.at00.v = ((S_81960530_5 *)copy_vertex)->unk_00;
            ((S_81960530_0 *)scratch)->unk_154.at00u.v = ((S_81960530_0 *)scratch)->unk_154.at00p.v - x;
            ((S_81960530_0 *)scratch)->unk_154.at02.v = ((S_81960530_0 *)scratch)->unk_154.at02u.v - y;

            copy_vertex = (u8 *)((unsigned long)((S_81960530_4 *)current)->unk_02 * 8 + (unsigned long)vertices);
            ((S_81960530_0 *)scratch)->unk_158.at00.v = ((S_81960530_5 *)copy_vertex)->unk_00;
            ((S_81960530_0 *)scratch)->unk_158.at00u.v = ((S_81960530_0 *)scratch)->unk_158.at00p.v - x;
            ((S_81960530_0 *)scratch)->unk_158.at02.v = ((S_81960530_0 *)scratch)->unk_158.at02u.v - y;

            copy_vertex = (u8 *)((unsigned long)((S_81960530_4 *)current)->unk_06 * 8 + (unsigned long)vertices);
            ((S_81960530_0 *)scratch)->unk_15C.at00.v = ((S_81960530_5 *)copy_vertex)->unk_00;
            ((S_81960530_0 *)scratch)->unk_15C.at00u.v = ((S_81960530_0 *)scratch)->unk_15C.at00p.v - x;
            ((S_81960530_0 *)scratch)->unk_15C.at02.v = ((S_81960530_0 *)scratch)->unk_15C.at02u.v - y;

            copy_vertex = (u8 *)((unsigned long)((S_81960530_4 *)current)->unk_04 * 8 + (unsigned long)vertices);
            ((S_81960530_0 *)scratch)->unk_160.at00.v = ((S_81960530_5 *)copy_vertex)->unk_00;
            ((S_81960530_0 *)scratch)->unk_160.at00u.v = ((S_81960530_0 *)scratch)->unk_160.at00p.v - x;
            ((S_81960530_0 *)scratch)->unk_160.at02.v = ((S_81960530_0 *)scratch)->unk_160.at02u.v - y;

            if (func_800BCE7C(scratch) != 0) {
                plane_ptr = (u8 *)((unsigned long)((S_81960530_4 *)current)->unk_10 * 8 + (unsigned long)planes);
                dot_vertex = (u8 *)((unsigned long)((S_81960530_4 *)current)->unk_00 * 8 + (unsigned long)vertices);
                value = (((S_81960530_6 *)plane_ptr)->unk_00 * (((S_81960530_7 *)dot_vertex)->unk_00 - (s16)((S_81960530_0 *)scratch)->unk_140.u) +
                         ((S_81960530_6 *)plane_ptr)->unk_02 * (((S_81960530_7 *)dot_vertex)->unk_02 - (s16)((S_81960530_0 *)scratch)->unk_142.u) +
                         ((S_81960530_6 *)plane_ptr)->unk_04 * ((S_81960530_7 *)dot_vertex)->unk_04) /
                        ((S_81960530_6 *)plane_ptr)->unk_04;
                ((S_81960530_0 *)scratch)->unk_144 = value;
                value += (s16)((S_81960530_0 *)scratch)->unk_152.u;
                ((S_81960530_0 *)scratch)->unk_144 = value;
                if (value >= ((S_81960530_0 *)scratch)->unk_14C &&
                    value < ((S_81960530_0 *)scratch)->unk_148) {
                    best = current;
                    ((S_81960530_0 *)scratch)->unk_148 = value;
                }
            }
        }

        if ((((S_81960530_4 *)current)->unk_16 & 0xF) == 1) {
            if (((S_81960530_4 *)current)->unk_17.s < 0) {
                break;
            }
            if ((((S_81960530_4 *)current)->unk_16 & 0xF0) != 0) {
                current += ((((S_81960530_4 *)current)->unk_16 >> 4) * 3) * 8 + 0x18;
                func_80026018();
            }
        }
        current += 0x18;
      } while (((S_81960530_9 *)(planes + ((S_81960530_4 *)current)->unk_10 * 8))->unk_04 < -0x7FF);
      }
    }

    return best;
}
