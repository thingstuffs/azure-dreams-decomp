#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad_00[0x19];
    s8 red;
    s8 green;
    s8 blue;
} ColorState;

extern void func_80064624(s32, s32);
extern void func_80064D20(void *);
extern void func_80064D50(void *);
extern void func_80064EC0(s32, s32, s32);
extern void func_80064EE0(s32, s32, s32);
extern void func_80064F00(s32, s32);
extern void func_80064F20(s32);

extern u8 D_800DDC7C;
extern ColorState D_801C9E40;
extern ColorState D_801DA714;

#ifdef __mips__
void func_80016000(void);
static const u32 split_prefix[] __asm__("func_80016000")
__attribute__((section(".text.func_80016000"), aligned(4))) = {
    0x8001D4FC, 0x8001D508, 0x8001D540, 0x8001D5C0, 0x8001D578,
    0x8001D5B0, 0x8001D5B0, 0x8001D5B0, 0x8001D5B0,
    0x8001D5B0, 0x8001D5B0, 0x8001D5B0, 0x8001D5B0,
    0x8001E944, 0x8001E944, 0x8001E944, 0x8001E87C,
    0x8001E944, 0x8001E944, 0x8001E944, 0x8001E944,
    0x8001E944, 0x8001E944, 0x8001E944, 0x8001E944,
    0x8001E944, 0x8001E944, 0x8001E8A4, 0x8001E8E8,
    0x8001E8B8, 0x8001E910,
};
__asm__(".globl func_80016000\n"
        ".size func_80016000, 472");
#define BODY_NAME func_8001607C
#else
#define BODY_NAME func_80016000
#endif

static __inline__ void set_light_vectors(u8 *view_state, s16 x, s16 y)
{
    *(s16 *)(view_state + 0x38) = x;
    *(s16 *)(view_state + 0x3A) = y;
    *(s16 *)(view_state + 0x3C) = x;
    *(s16 *)(view_state + 0x3E) = -x;
    *(s16 *)(view_state + 0x40) = -y;
    *(s16 *)(view_state + 0x42) = -x;
    *(s16 *)(view_state + 0x44) = 0;
    *(s16 *)(view_state + 0x46) = 0;
    *(s16 *)(view_state + 0x48) = 0;
}

/* Initialize projection, lighting, colors, and view bounds. */
void BODY_NAME(void) {
    u8 *render_data;
    u8 *view_state;
    s32 default_scale;
    void *light_matrix;

    render_data = ((u8 *)(&gameWork));
    view_state = render_data + 0x18;
    default_scale = 0x200;
    *(s32 *)(view_state + 0x88) = default_scale;
    func_80064F20(default_scale);
    *(s32 *)(view_state + 0x78) = 0;
    *(s32 *)(view_state + 0x7C) = 0;
    *(s32 *)(view_state + 0x80) = 0;
    func_80064EE0(0, 0, 0);
    *(s16 *)(view_state + 0x58) = default_scale;
    *(s16 *)(view_state + 0x5E) = default_scale;
    *(s16 *)(view_state + 0x64) = default_scale;
    *(s16 *)(view_state + 0x5A) = -0x100;
    *(s16 *)(view_state + 0x60) = -0x100;
    *(s16 *)(view_state + 0x66) = -0x100;
    *(s16 *)(view_state + 0x5C) = 0;
    *(s16 *)(view_state + 0x62) = 0;
    *(s16 *)(view_state + 0x68) = 0;
    func_80064D50(render_data + 0x70);

    light_matrix = render_data + 0x50;
    set_light_vectors(view_state, -0x800, 0x800);
    func_80064D20(light_matrix);

    *(s32 *)(view_state + 0x84) = 0x1000;
    func_80064624(0x1000, *(s32 *)(view_state + 0x88));
    func_80064EC0(0xA0, 0xA0, 0xA0);
    D_801C9E40.red = 0;
    D_801C9E40.green = 0;
    D_801C9E40.blue = 0;
    D_801DA714.red = 0;
    D_801DA714.green = 0;
    D_801DA714.blue = 0;
    func_80064F00(0xA0, 0x78);
    *(s16 *)(render_data + 0x18) = -0xBC;
    *(s16 *)(render_data + 0x1A) = -0x88;
    *(s16 *)(render_data + 0x1C) = 0x172;
    *(s16 *)(render_data + 0x1E) = 0x19A;
    dungeonStatus.unk_18 = &D_800DDC7C;
}
