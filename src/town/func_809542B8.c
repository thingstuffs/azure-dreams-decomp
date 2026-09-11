#include "common.h"

typedef struct {
    s32 v[5];
} Word5;

typedef struct {
    s32 v[8];
} Word8;

typedef struct {
    s32 v[4];
} Word4;

typedef struct {
    s32 w0;
    s32 w4;
} __attribute__((packed)) Packed8;

typedef struct {
    s16 h0;
    s16 pad2;
    void *p4;
    s32 w8;
    s16 hC;
    s16 hE;
    s16 h10;
    s16 h12;
    s16 h14;
    s16 h16;
    s32 pad18[4];
} Init40;

typedef struct {
    s16 h0;
    s16 pad2;
    void *p4;
    void *p8;
    void *pC;
    s32 w10;
    s16 h14;
    s16 h16;
    s16 h18;
    s16 h1A;
    s16 h1C;
    s16 pad1E;
    s32 pad20[4];
} Init10;

#define AT(type, base, off) (*(type *)((u8 *)(base) + (off)))

extern Word5 D_80020100[];
extern Word8 D_80020114[];
extern Word4 D_80020134[];
extern Packed8 D_80020144[];
extern u8 D_800218E4[];
extern u8 D_80022484[];
extern u8 D_800225F0[];
extern u8 D_80023158[];
extern u8 D_80023260[];
extern u8 D_80023A00[];
extern u8 D_80023C80[];
extern Packed8 D_80024310[];
extern u8 D_80045340[];
extern u8 D_80046398[];
extern u8 D_80082E80[];
extern s32 D_80082EA8[];
extern u8 D_80083498[];
extern u8 D_800F15E4[];
extern s32 D_800135B4[];

extern void func_8002108C();
extern void func_80021120();
extern void func_80022FD8();
extern void func_80023DA0();
extern void func_80033B9C();
extern void func_8003DB94();
extern void func_8003E188();
extern u8 *func_8003FC64();
extern u8 *func_8003FD64();
extern void func_8004491C();
extern s16 func_800C2AE8();

/* Initializes the interface owner, widgets, and sprite objects. */
s32 func_800212B8(void) {
    u8 *owner = 0;
    Init10 widget_init;
    Init40 panel_init;
    Word5 widget_data = D_80020100[0];
    Word8 sprite_frames = D_80020114[0];
    Word4 sprite_images = D_80020134[0];
    u8 *obj;
    u8 *sprite;
    u8 *child_data;
    s32 *timer;
    s32 index;

    func_80033B9C(0x58D);
    func_80033B9C(0x58E);
    func_8003E188(0xE, 0);

    obj = func_8003FD64(1, D_80083498);
    if (obj != 0) {
        owner = obj + 0x20;
        AT(s16, owner, 0x2E) = 0x2D;
        AT(void *, obj, 0x10) = D_800218E4;
    }
    AT(void *, D_80083498, 0x74) = owner;
    func_80023DA0(owner);

    panel_init.hC = 0x10;
    panel_init.hE = 0x10;
    panel_init.h10 = 0x68;
    panel_init.h12 = 0x40;
    panel_init.h14 = 2;
    panel_init.h16 = 1;
    panel_init.w8 = 0x404040;
    panel_init.h0 = 0;
    panel_init.p4 = owner;
    func_80021120(D_80022484, &panel_init);

    {
        index = 3;
        panel_init.hC = -2;
        panel_init.hE = -2;
        panel_init.h14 = 0;
        panel_init.h16 = 0;
        do {
            panel_init.w8 = (0x80 << (index * 8)) & 0xFFFFFF;
            panel_init.p4 = owner + index * 4;
            func_80021120(D_80023C80, &panel_init);
            index--;
        } while (index >= 0);
    }

    {
        s32 widget_index;
        Init10 *widget_params;
        widget_init.h14 = 0x14;
        widget_init.h18 = 3;
        widget_init.h1C = 0;
        widget_init.h1A = 0x7C80;
        widget_init.w10 = 0x808080;
        widget_init.h0 = 0;
        widget_init.pC = owner;
        widget_index = 4;
        widget_params = &widget_init;
        do {
            register u8 *widget_handler ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            Init10 *widget_args;
            widget_handler = D_800225F0;
            do {
                widget_args = widget_params;
            } while (0);
            ASM_KEEP_DEP_NV(widget_args, widget_handler);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            widget_init.h16 = widget_index * 0xC + 0x14;
            widget_init.p4 = (void *)((s32 *)&widget_init)[0x16 + widget_index];
            widget_index--;
            func_8002108C(widget_handler, widget_args);
        } while (widget_index >= 0);
    }

    widget_init.h14 = 0x3C;
    timer = (s32 *)0x800135B4;
    if (*timer == 0) {
        *timer = 0x258;
    }
    AT(u16, owner, 0x38) = *(u16 *)timer;
    {
        s32 value_index = 4;
        register s32 template_page ASM_REG("$20") = (s32)0x80020000;   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        register s32 value_offset ASM_REG("$19") = 0x38;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s16 value_y = 0x44;
        Packed8 *text_buffers = D_80024310;
        Packed8 *text_buffer = text_buffers + 4;
        s32 handler_page;
        do {
            register Packed8 *copy_src ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            copy_src = (Packed8 *)(template_page + 0x144);
            ASM_KEEP_NV(copy_src);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            *text_buffer = *copy_src;
            AT(s8, text_buffer, 7) = 0;
            widget_init.h16 = value_y;
            widget_init.p4 = text_buffer;
            widget_init.p8 = owner + value_offset;
            handler_page = (s32)0x80020000;
            ASM_KEEP_DEP_NV(handler_page, template_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            func_8002108C((u8 *)(handler_page + 0x2FD8), &widget_init);
            value_offset -= 2;
            value_y -= 0xC;
            value_index--;
            text_buffer--;
        } while (value_index >= 0);
    }

    {
        s32 sprite_index = 7;
        s32 handler_page = (s32)0x80020000;
        u8 *sprite_handler;
        register s16 sprite_scale ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u8 *grid_sprite;
        ASM_KEEP(handler_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        sprite_handler = (u8 *)(handler_page + 0x3158);
        sprite_scale = 0x1000;
        do {
            obj = func_8003FC64(0x136);
            if (obj != 0) {
                func_8004491C(obj, D_80046398);
                grid_sprite = AT(u8 *, obj, 0xC);
                AT(void *, obj, 0x10) = sprite_handler;
                AT(s32, grid_sprite, 0xC) = 0x808080;
                AT(s16, grid_sprite, 0x1C) = sprite_scale;
                AT(s16, grid_sprite, 0x1E) = sprite_scale;
                AT(s16, grid_sprite, 0x20) = sprite_scale;
                AT(s32, grid_sprite, 8) = sprite_frames.v[sprite_index];
                AT(s32, AT(u8 *, obj, 8), 0) = ((sprite_index >> 2) << 22) + 0x0FE00000;
                AT(s32, AT(u8 *, obj, 8), 4) = ((sprite_index % 4) << 22) + 0x03E00000;
                AT(s32, AT(u8 *, obj, 8), 8) = 0;
                AT(void *, obj, 0x20) = owner;
            }
            sprite_index--;
        } while (sprite_index >= 0);
    }

    index = 3;
    do {
        obj = func_8003FC64(0x136);
        if (obj != 0) {
            func_8004491C(obj, D_80045340);
            sprite = AT(u8 *, obj, 0xC);
            AT(void *, obj, 0x10) = D_80023158;
            AT(s16, sprite, 0x1E) = 0x1000;
            AT(s16, sprite, 0x1C) = 0x1000;
            AT(s32, sprite, 0xC) = 0x808080;
            func_8003DB94(sprite, (void *)sprite_images.v[index], 0);
            AT(u16, sprite, 0x12) = 0xFFC0;
            AT(s32, AT(u8 *, obj, 8), 0) = ((index >> 2) << 22) + 0x0FD00000;
            AT(s32, AT(u8 *, obj, 8), 4) = ((index % 4) << 22) + 0x04100000;
            AT(s32, AT(u8 *, obj, 8), 8) = 0xFF600000;
            AT(void *, obj, 0x20) = owner;
        }
        index--;
    } while (index >= 0);

    {
        u8 *new_obj;
        register u8 *child_obj ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        register s32 child_index ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u8 *sprite_state;
        s16 frame_offset;
        register u8 *child_slot ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        sprite_state = D_80082E80;
        child_index = 2;
        ASM_KEEP_DEP_NV(child_index, sprite_state);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        frame_offset = 0xC;
        child_slot = owner + 8;
        do {
            new_obj = func_8003FD64(0x136, D_80083498);
            child_obj = new_obj;
            ASM_KEEP(child_obj);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            AT(void *, child_slot, 0x20) = new_obj;
            if (child_obj != 0) {
                obj = child_obj;
                AT(void *, obj, 0x10) = D_80023260;
                func_8004491C(obj, D_80045340);
                sprite = AT(u8 *, obj, 0xC);
                AT(s32, AT(u8 *, obj, 8), 0) = 0x10000000;
                AT(s32, AT(u8 *, obj, 8), 4) = (child_index << 22) + 0x04200000;
                child_data = obj + 0x20;
                AT(s16, AT(u8 *, obj, 8), 0xA) = func_800C2AE8(AT(void *, obj, 8));
                AT(s16, sprite, 0x1E) = 0x1000;
                AT(s16, sprite, 0x1C) = 0x1000;
                AT(s32, sprite, 0x28) = AT(s32, sprite_state, 0x28);
                AT(s16, child_data, 0x2A) = 0x800;
                func_8003DB94(sprite, D_800F15E4, 0);
                AT(s32, sprite, 0xC) = 0x808080;
                AT(s16, sprite, 0x12) = frame_offset;
                AT(void *, obj, 0x20) = owner;
                AT(s16, child_data, 0x24) = child_index + 1;
            }
            frame_offset -= 4;
            child_index--;
            child_slot -= 4;
        } while (child_index >= 0);
    }

    obj = func_8003FD64(0x136, D_80083498);
    if (obj != 0) {
        AT(void *, obj, 0x10) = D_80023A00;
        func_8004491C(obj, D_80045340);
        sprite = AT(u8 *, obj, 0xC);
        AT(s32, AT(u8 *, obj, 8), 0) = 0x10000000;
        AT(s32, AT(u8 *, obj, 8), 4) = 0x03E00000;
        child_data = obj + 0x20;
        AT(s16, AT(u8 *, obj, 8), 0xA) = func_800C2AE8(AT(void *, obj, 8));
        AT(s16, sprite, 0x1E) = 0x1000;
        AT(s16, sprite, 0x1C) = 0x1000;
        AT(s32, sprite, 0x28) = D_80082EA8[0];
        AT(s16, child_data, 0x2A) = 0x800;
        func_8003DB94(sprite, D_800F15E4, 0);
        AT(s32, sprite, 0xC) = 0x808080;
        AT(void *, obj, 0x20) = owner;
    }
    return 0;
}
