#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"



typedef struct {
    u8 pad[0xA];
    s16 color;
    s16 index;
} Input;

typedef struct {
    s32 unk0;
    s32 color;
    s32 unk8;
    s32 width;
    s32 start;
    s32 end;
} Work;


extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_800666E0(void *);
extern void func_80066640(void *, s32);
extern void func_8006658C(void *, void *);

/* Queue a full-screen grayscale quad with its draw mode at the input ordering index. */
s32 func_800A624C(Input *input) {
    GpuContext *arena;
    u8 *draw_mode;
    Work *quad;
    s16 color;

    arena = (GpuContext *)gameWork.unk_000;
    draw_mode = arena->packetCursor;
    arena->packetCursor = draw_mode + 0xC;
    arena = (GpuContext *)gameWork.unk_000;
    quad = (Work *)arena->packetCursor;
    arena->packetCursor = (u8 *)quad + 0x18;

    func_80067F20(draw_mode, 0, 0, 0x40, 0);

    color = input->color;
    quad->color = color | (color << 8) | (color << 16);
    func_800666E0(quad);
    func_80066640(quad, 1);

    quad->width = 0x140;
    quad->unk8 = 0;
    quad->start = 0xE00000;
    quad->end = 0xE00140;

    func_8006658C((u8 *)gameWork.unk_000 + ((input->index * 4) + 0xB0), quad);
    func_8006658C((u8 *)gameWork.unk_000 + ((input->index * 4) + 0xB0), draw_mode);
    return 0;
}
