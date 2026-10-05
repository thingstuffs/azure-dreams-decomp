#include "common.h"
#include "shared/game_work.h"

typedef struct OtTag {
    u32 addr : 24;
    u32 len : 8;
} OtTag;

typedef struct S_8002222C_0 {
    u8 pad_00[0xB0];
    OtTag ot[0x208];
    u8 * unk_8D0;
} S_8002222C_0;   /* arena in func_8002222C */

typedef struct S_8002222C_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_8002222C_1_pre;   /* the 0x8 bytes before var_s3 in func_8002222C, addressed as var_s3[-1] */

typedef struct S_8002222C_1 {
    u8 pad_00[0x18];
    s32 unk_18;
    s32 unk_1C;
} S_8002222C_1;   /* var_s3 in func_8002222C */

typedef struct S_8002222C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_8002222C_2;   /* temp_s0 in func_8002222C */

typedef struct S_8002222C_3 {
    s32 unk_00;
    s32 unk_04;
} S_8002222C_3;   /* scratch in func_8002222C */

typedef struct S_8002222C_4 {
    u16 unk_00;
    u16 unk_02;
} S_8002222C_4;   /* scratch100 in func_8002222C */


extern void func_80065770(void *, void *, void *, void *, void *, s32);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80066640(void *, s32);
extern void func_800667D0(void *);
extern void func_80067F20(void *, s32, s32, s32, s32);

/* Build line and draw-mode packets for each entry and link them into the ordering table. */
s32 func_8002222C(void *first_entry) {
    u8 *line_packet;
    u8 *mode_packet;
    s32 next;
    s32 bucket_addr;
    s32 texture_page;
    u8 *entry;
    GameWork *arena_ptr;
    u8 *depths;
    u8 *transform_work;
    u8 *screen_xy;
    s32 raw_depth;

    entry = first_entry;
    arena_ptr = &gameWork;
    screen_xy = (u8 *)0x1F800000;
    depths = (u8 *)((u32)screen_xy | 0x100);
    transform_work = (u8 *)((u32)screen_xy | 0x180);
    for (;;) {
        func_80065770(entry + 8, screen_xy, depths, transform_work,
                      transform_work, 2);
        {
            u8 *arena;
            arena = arena_ptr->unk_000;
            line_packet = ((S_8002222C_0 *)arena)->unk_8D0;
            ((S_8002222C_0 *)arena)->unk_8D0 = line_packet + 0x14;
            arena = arena_ptr->unk_000;
            mode_packet = ((S_8002222C_0 *)arena)->unk_8D0;
            ((S_8002222C_0 *)arena)->unk_8D0 = mode_packet + 0xC;
            texture_page = func_80066460(0, 0, 0, 0);
        }
        func_80067F20(mode_packet, 0, 0, texture_page & 0xFFFF, 0);
        ((S_8002222C_2 *)line_packet)->unk_04 = ((S_8002222C_1 *)entry)->unk_18;
        ((S_8002222C_2 *)line_packet)->unk_0C = ((S_8002222C_1 *)entry)->unk_1C;
        func_800667D0(line_packet);
        func_80066640(line_packet, 1);
        ((S_8002222C_2 *)line_packet)->unk_08 = ((S_8002222C_3 *)screen_xy)->unk_00;
        ((S_8002222C_2 *)line_packet)->unk_10 = ((S_8002222C_3 *)screen_xy)->unk_04;
        {
            s32 min_depth;
            raw_depth = ((S_8002222C_4 *)depths)->unk_00;
            bucket_addr = raw_depth << 0x10;
            min_depth = ((S_8002222C_4 *)depths)->unk_02 << 0x10;
            if (bucket_addr < min_depth) {
                min_depth = bucket_addr >> 0x13;
            } else {
                min_depth >>= 0x13;
            }
            bucket_addr = min_depth * 4;
        }
        ((OtTag *)line_packet)->addr = ((S_8002222C_0 *)(bucket_addr + (u32)arena_ptr->unk_000))->ot[0].addr;
        ((S_8002222C_0 *)(bucket_addr + (u32)arena_ptr->unk_000))->ot[0].addr = (u32)line_packet;
        ((OtTag *)mode_packet)->addr = ((S_8002222C_0 *)(bucket_addr + (u32)arena_ptr->unk_000))->ot[0].addr;
        bucket_addr += (u32)arena_ptr->unk_000;
        ((S_8002222C_0 *)bucket_addr)->ot[0].addr = (u32)mode_packet;
        next = ((S_8002222C_1_pre *)entry)[-1].unk_00;
        if (next == 0) {
            break;
        }
        entry = next + 0x20;
    }
    return 0;
}
