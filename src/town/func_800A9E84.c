#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800A75E4_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800A75E4_0;   /* entry in func_800A75E4 */

typedef struct S_800A75E4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800A75E4_1;   /* object in func_800A75E4 */

typedef struct S_800A75E4_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A75E4_2;   /* part_data in func_800A75E4 */

typedef struct S_800A75E4_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800A75E4_3;   /* part in func_800A75E4 */

typedef struct S_800A75E4_4 {
    u8 pad_00[0x50];
    s32 unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
    u8 pad_92[0x3];
    s8 unk_95;
    s8 unk_96;
} S_800A75E4_4;   /* body in func_800A75E4 */



typedef struct {
    s32 unk0;
    void *value;
} EntryRecord;

extern void func_80033CD8();
extern void *func_8009C390();
extern s32 D_80045340;
extern EntryRecord D_80082660[];
extern u8 D_800A76F0;
extern s32 D_800D0E24[];
extern s32 D_800D0E3C[];

void func_800A75E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 saved_arg1;
    s32 saved_arg2;
    s32 saved_arg3;
    void *call_arg0;
    void *call_arg1;
    void *call_arg2;
    S_800A75E4_0 *entry;
    void *object;
    u8 *body;
    S_800A75E4_3 *part;
    register s32 *value_slot ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_800A75E4_2 *part_data;

    saved_arg1 = arg1;
    saved_arg2 = arg2;
    saved_arg3 = arg3;
    call_arg0 = NULL;
    call_arg1 = call_arg0;
    if (arg0 != 0) {
        entry = D_80082660[arg0].value;
        if (entry != NULL) {
            call_arg0 = entry;
            call_arg1 = entry->unk_08;
        }
    }
    call_arg2 = &D_800A76F0;

    object = func_8009C390(call_arg0, call_arg1, call_arg2, 0);
    body = (u8 *)object + 0x20;
    if (object != NULL) {
        call_arg0 = body;
        ASM_KEEP(call_arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        entry = D_800D0E24;
        value_slot = (s32 *)(((u32)saved_arg1 << 2) + (u32)entry);
        ASM_KEEP(value_slot);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        part = ((S_800A75E4_1 *)object)->unk_08;
        part_data = ((S_800A75E4_1 *)object)->unk_0C;
        part_data->unk_08 = *value_slot;
        func_80033CD8(call_arg0, &D_80045340, part_data);
        part->unk_0A = part->unk_0A - 0x62;
        ((S_800A75E4_4 *)body)->unk_90 = 0xA;
        ((S_800A75E4_4 *)body)->unk_6C = saved_arg3;
        ((S_800A75E4_4 *)body)->unk_95 = saved_arg1;
        ((S_800A75E4_4 *)body)->unk_96 = saved_arg2;
        ((S_800A75E4_4 *)body)->unk_50 = D_800D0E3C[saved_arg2];
    }
    ASM_KEEP(saved_arg1);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_arg2);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(part);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
}

/* MECHANISM: Pinned argument/call registers reproduce the retail 0x28 frame and saved-register roles.
   An 8-byte entry record preserves the table's base-plus-field addressing; split pinned base/index
   liveness orders the two later global addresses, and the clean merge supplies the branch-delay lui. */
