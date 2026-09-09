#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_func_81339A5C_0 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
} S_func_81339A5C_0;

typedef struct S_func_81339A5C_1 {
    u8 pad_00[2];
    union { u16 u; s16 s; } unk_02;
    u8 pad_04[2];
    union { u16 u; s16 s; } unk_06;
    u8 pad_08[2];
    u16 unk_0A;
    u8 pad_0C[10];
    u16 unk_16;
} S_func_81339A5C_1;

typedef struct S_func_81339A5C_2 {
    u8 pad_00[0x24];
    void *unk_24;
    u8 pad_28[0x30];
    s8 unk_58;
    s8 unk_59;
} S_func_81339A5C_2;

typedef struct S_func_81339A5C_3 {
    u8 pad_00[6];
    s16 unk_06;
    void *unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[5];
    u16 unk_14;
    u8 pad_16[6];
    s16 unk_1C;
    s16 unk_1E;
} S_func_81339A5C_3;

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 D_80045340;
extern s32 D_8006E240;
extern s32 D_8017085C;
extern void *D_80175D50;
extern void *D_80175D68;

/* Creates a linked object and initializes its position and rendering state. */
void func_80170A5C(void)
{
    u16 object_z;
    u16 source_z;
    u16 object_y;
    S_func_81339A5C_1 *source_pos;
    register S_func_81339A5C_2 *object_data ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *source_data;
    S_func_81339A5C_0 *object;
    S_func_81339A5C_3 *render_flags;
    S_func_81339A5C_1 *object_pos;
    S_func_81339A5C_3 *render_state;

    source_pos = ((S_func_81339A5C_0 *)D_80175D50)->unk_08;
    source_data = D_80175D50 + 0x20;
    object = func_8003FD64(0x12, D_80175D50);
    if (object != NULL) {
        object->unk_10 = &D_8017085C;
        func_8004491C(object, &D_80045340);
        render_flags = object->unk_0C;
        object_data = (S_func_81339A5C_2 *)((u8 *)object + 0x20);
        render_flags->unk_14 =
            (u16)(render_flags->unk_14 & 0xFFF3);
        object_data->unk_24 = source_data;
        object_pos = object->unk_08;
        object_pos->unk_02.u = source_pos->unk_02.u;
        object_pos->unk_06.u = source_pos->unk_06.u;
        ((volatile S_func_81339A5C_1 *)object_pos)->unk_0A =
            ((volatile S_func_81339A5C_1 *)source_pos)->unk_0A;
        source_z = ((volatile S_func_81339A5C_1 *)source_pos)->unk_0A;
        object_y = ((volatile S_func_81339A5C_1 *)object_pos)->unk_06.u;
        object_z = ((volatile S_func_81339A5C_1 *)object_pos)->unk_0A;
        object_pos->unk_06.u = (u16)(object_y - 0x140);
        object_pos->unk_16 = source_z;
        object_pos->unk_0A = (u16)(object_z - 0x20);
        render_state = object->unk_0C;
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        render_state->unk_06 = 6;
        object_data->unk_58 =
            (source_pos->unk_02.s - 0x20) / 0x40;
        object_data->unk_59 =
            (source_pos->unk_06.s - 0x20) / 0x40;
        render_state->unk_0E = 0x80;
        render_state->unk_0D = 0x80;
        render_state->unk_0C = 0x80;
        render_state->unk_08 = &D_8006E240;
        D_80175D68 = object;
    }
}

/* MECHANISM: A guarded s2 object-base pin preserves the 40-byte ra/s3/s2/s1/s0 frame contract.
   Volatile halfword copy/read locals retain the retail reload and load-delay nop sequence.
   Direct signed /0x40 coordinate expressions coalesce each result into retail's v0 web. */
