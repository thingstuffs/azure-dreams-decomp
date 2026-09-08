#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B0870_0 {
    u8 unk_00;
    union { s8 s; u8 u; } unk_01;   /* accessed as both */
    u8 unk_02;
    u8 unk_03;
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u8 unk_0A;
    u8 unk_0B;
} S_800B0870_0;   /* arg0 in func_800B0870 */

typedef struct S_800B0870_1 {
    u8 unk_00;
    u8 pad_01[0x1];
    u8 unk_02;
    u8 pad_03[0x1];
    u8 unk_04;
    u8 pad_05[0x1];
    u8 unk_06;
} S_800B0870_1;   /* arg1 in func_800B0870 */


/* Initializes two consecutive records with source bytes and fixed control values. */
void func_800B0870(void *destination, S_800B0870_1 *source) {
    u8 sourceByte4;
    u8 sourceByte6;

    ((S_800B0870_0 *)destination)->unk_01.s = 0x2A;
    sourceByte4 = source->unk_04;
    ((S_800B0870_0 *)destination)->unk_0A = sourceByte4;
    sourceByte6 = source->unk_06;
    ((S_800B0870_0 *)destination)->unk_04.at00.v = 0x401010;
    ((S_800B0870_0 *)destination)->unk_0B = sourceByte6;
    ((S_800B0870_0 *)destination)->unk_02 = (u8) source->unk_00;
    ((S_800B0870_0 *)destination)->unk_03 = (u8) source->unk_02;
    destination += 0xC;
    ((S_800B0870_0 *)destination)->unk_01.u = 0x81;
    ((S_800B0870_0 *)destination)->unk_04.at00u.v = 0;
    ((S_800B0870_0 *)destination)->unk_04.at02.v = 1;
    ((S_800B0870_0 *)destination)->unk_00 = (u8) (((S_800B0870_0 *)destination)->unk_00 | 0x80);
}
