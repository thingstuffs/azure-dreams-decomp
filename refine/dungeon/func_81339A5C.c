#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

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
    void *source_pos;
    register void *object_data ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    void *source_data;
    void *object;
    void *render_flags;
    void *object_pos;
    void *render_state;

    source_pos = FIELD(D_80175D50, void **, 8);
    source_data = D_80175D50 + 0x20;
    object = func_8003FD64(0x12, D_80175D50);
    if (object != NULL) {
        FIELD(object, void **, 0x10) = &D_8017085C;
        func_8004491C(object, &D_80045340);
        render_flags = FIELD(object, void **, 0xC);
        object_data = object + 0x20;
        FIELD(render_flags, u16 *, 0x14) =
            (u16)(FIELD(render_flags, u16 *, 0x14) & 0xFFF3);
        FIELD(object_data, void **, 0x24) = source_data;
        object_pos = FIELD(object, void **, 8);
        FIELD(object_pos, u16 *, 2) = FIELD(source_pos, u16 *, 2);
        FIELD(object_pos, u16 *, 6) = FIELD(source_pos, u16 *, 6);
        FIELD(object_pos, volatile u16 *, 0xA) =
            FIELD(source_pos, volatile u16 *, 0xA);
        source_z = FIELD(source_pos, volatile u16 *, 0xA);
        object_y = FIELD(object_pos, volatile u16 *, 6);
        object_z = FIELD(object_pos, volatile u16 *, 0xA);
        FIELD(object_pos, u16 *, 6) = (u16)(object_y - 0x140);
        FIELD(object_pos, u16 *, 0x16) = source_z;
        FIELD(object_pos, u16 *, 0xA) = (u16)(object_z - 0x20);
        render_state = FIELD(object, void **, 0xC);
        FIELD(render_state, s16 *, 0x1E) = 0x1000;
        FIELD(render_state, s16 *, 0x1C) = 0x1000;
        FIELD(render_state, s16 *, 6) = 6;
        FIELD(object_data, s8 *, 0x58) =
            (FIELD(source_pos, s16 *, 2) - 0x20) / 0x40;
        FIELD(object_data, s8 *, 0x59) =
            (FIELD(source_pos, s16 *, 6) - 0x20) / 0x40;
        FIELD(render_state, u8 *, 0xE) = 0x80;
        FIELD(render_state, u8 *, 0xD) = 0x80;
        FIELD(render_state, u8 *, 0xC) = 0x80;
        FIELD(render_state, void **, 8) = &D_8006E240;
        D_80175D68 = object;
    }
}

/* MECHANISM: A guarded s2 object-base pin preserves the 40-byte ra/s3/s2/s1/s0 frame contract.
   Volatile halfword copy/read locals retain the retail reload and load-delay nop sequence.
   Direct signed /0x40 coordinate expressions coalesce each result into retail's v0 web. */
