#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    u16 z;
} DungeonCoord;

typedef struct {
    u8 pad0[8];
    void *image;
    s32 color;
    s16 width;
    s16 pad12;
    s16 blend;
    u16 blend2;
    s16 shade;
    s16 pad1A;
    s16 size;
    s16 limit;
    u16 flags;
    u16 depth;
} DungeonRender;

typedef struct {
    void *parent;
    u8 pad4[9];
    s8 angle;
    u8 pad14[2];
    s16 mode;
    s16 value;
    u8 pad20[4];
    s16 height;
    s16 frame;
    s16 speed;
    s16 limit;
} DungeonState;

typedef struct {
    s32 arg1;
    u16 arg3_low;
    s32 arg3;
    s32 arg4;
} DungeonHomes;

typedef struct {
    u8 pad0[8];
    DungeonCoord *coord;
    DungeonRender *render;
    void *callback;
    u8 pad20[12];
    DungeonState state;
} DungeonObject;

extern void func_8003DB6C(void *, void *, s32);
extern DungeonObject *func_8003FD64(s32, void *);
extern void func_8004491C(DungeonObject *, void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern u8 D_80045C34[];
extern u8 D_800777E8[];
extern u8 D_80083498[];
extern u8 D_800BB0A8[];
extern u8 D_800BB14C[];
extern u8 D_800D0774[];
extern u8 D_800DF3B4[];

/* Creates a dungeon effect with a central object and up to eleven surrounding children. */
DungeonObject *func_800C7380(s16 tile_x, s32 tile_y, u16 z, s32 height, s32 speed) {
    DungeonHomes homes;
    s32 color;
    DungeonObject *parent;
    DungeonObject *child;
    DungeonState *state;
    register DungeonCoord *center ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    DungeonCoord *child_coord;
    DungeonRender *render;
    void *image_data;
    s16 shade;
    s32 remaining;
    s32 angle;
    register u16 saved_z ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register u32 setup_word ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    saved_z = z;
    ASM_KEEP_NV(saved_z);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    homes.arg1 = tile_y;
    setup_word = speed;
    homes.arg4 = (s32) setup_word;
    homes.arg3 = height;
    parent = func_8003FD64(0x12, D_80083498);
    setup_word = (u16) homes.arg3;
    homes.arg3_low = (u16) setup_word;
    if (parent != NULL) {
        s16 frame;
        u16 state_limit;
        parent->callback = D_800BB0A8;
        func_8004491C(parent, D_80045C34);
        color = 0x404040;
        state = &parent->state;
        remaining = 0xB;
        shade = -0xAA7;
        center = parent->coord;
        center->x = (s16) (((s32) (tile_x << 0x10) >> 0xA) + 0x20);
        angle = 0xEA7;
        setup_word = homes.arg1;
        center->z = saved_z;
        center->y = (s16) (((s32) (setup_word << 0x10) >> 0xA) + 0x20);
        ASM_USE(setup_word);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        render = parent->render;
        render->image = D_800777E8;
        render->limit = 0x1800;
        render->size = 0x1800;
        render->width = 0x20;
        render->depth = 0xFFFB;
        render->color = color;
        render->flags = 0xFFFF;
        render->blend = (s16) (render->blend | 0xC);
        frame = 0x37;
        state->mode = tile_x;
        setup_word = (u16) homes.arg1;
        ASM_USE(setup_word);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        state_limit = 0x14;
        ASM_USE(state_limit);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        state->value = (u16) setup_word;
        setup_word = (u16) homes.arg3;
        state->limit = state_limit;
        state->height = (u16) setup_word;
        setup_word = (u16) homes.arg4;
        state->speed = (u16) setup_word;
        do {
            child = func_8003FD64(0x12, parent);
            if (child != NULL) {
                register DungeonObject *init_child ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                register void *child_resource ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                init_child = child;
                child_resource = D_800D0774;
                setup_word = (u32) D_800BB14C;
                ASM_KEEP(setup_word);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                child->callback = (void *) setup_word;
                func_8004491C(init_child, child_resource);
                child_coord = child->coord;
                child_coord->x = (s16) (center->x + (func_80064584(angle) >> 7));
                child_coord->y = (s16) (center->y + (func_800644B8(angle) >> 7));
                child_coord->z = center->z;
                render = child->render;
                render->blend2 = 0xFC00;
                render->shade = shade;
                render->size = 0x410;
                if (state->height < 0) {
                    render->width = 0x40;
                }
                state = &child->state;
                image_data = (void *) ((u8 *) child + 0x24);
                setup_word = homes.arg3_low;
                state->height = (u16) setup_word;
                render->image = image_data;
                func_8003DB6C(image_data, D_800DF3B4, 3);
                state->angle = (s8) (frame & 0xBF);
                state->frame = frame;
                state->parent = parent;
            }
            shade += 0x155;
            angle -= 0x155;
            remaining -= 1;
            frame -= 5;
        } while (remaining > 0);
    }
    return parent;
}
