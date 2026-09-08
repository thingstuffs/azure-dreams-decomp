#include "common.h"

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8();
extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_800A3820(s32);
extern s32 func_800A05A4(void *, u8, u8, s16, s32);
extern s16 func_800BCB04(s32, s32, s16);
extern void func_800A56E0(s32);
extern void func_80044A50(void *);
extern void func_800419EC(s32, s32);
extern void func_8002506C(s32, s16);
extern s32 func_8009D218(s32, s32, void *);
extern void func_800C8900(s32, s32, s32);

extern void func_800240D0(void) __attribute__((noreturn));
extern void func_80024388(void) __attribute__((noreturn));
extern void func_80024724(void) __attribute__((noreturn));
extern void func_80024728(void) __attribute__((noreturn));
extern void func_80024764(void) __attribute__((noreturn));

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_80024C7C[];
extern u8 D_80024B60[];
extern u8 D_80024798[];
extern u8 D_800249DC[];
extern u8 D_800249DC_store[] __asm__("D_800249DC");
extern u8 D_800DECF8[];
extern u8 D_800DECF8_load[] __asm__("D_800DECF8");
extern u8 D_800E3D68[];
extern s32 D_8008346C[3];
extern s32 D_800814A0[3];

#define S8(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

#ifdef __mips__
static const u32 split_prefix[] __asm__("func_818E6800")
    __attribute__((section(".text.func_818E6800"), aligned(4))) = {
    0x8002401C, 0x10001000, 0x14000E10, 0x18000D48,
    0x0FA01000, 0x0DAC1800, 0x0BB82000,
};
__asm__(".globl func_818E6800\n"
        ".size func_818E6800, 1944");
#define BODY_NAME func_818E681C
#else
#define BODY_NAME func_818E6800
#endif

void BODY_NAME(void *effect_arg, void *motion_arg, void * volatile context_arg)
    __attribute__((section(".text.func_818E6800")));

/* Advance the effect through target selection, movement, impact, and cleanup. */
void BODY_NAME(void *effect_arg, void *motion_arg, void * volatile context_arg) {
    u8 *effect = (u8 *)effect_arg;
    register u8 *motion ASM_REG("$22") = (u8 *)motion_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *actor ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *actor_data;
    u8 *actor_header;
    u8 *particle;
    u8 *render_data;
    register u8 *particle_data ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 count ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 state;
    s32 tile_x;
    s32 tile_y;
    s32 distance;
    s16 offset[3];

    ASM_CLOBBER("$6");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    {
        register s32 original_count ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        actor = (u8 *)S32(effect, 0);
        ASM_KEEP_NV(actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        original_count = U16(effect, 80);
        state = S16(effect, 10);
        count = original_count - 1;
        ASM_KEEP(count);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    }
    actor_data = (u8 *)S32(actor, -20);
    actor_header = actor - 32;

    U16(effect, 80) = (u16)count;
    if (state > 0) {
        if (state == 2) goto state_2;
        if (state < 3) {
            if (state == 1) goto state_1;
            count = -1;
            ASM_TAILSLOT_PIN(count);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800240D0();
            return;
        }
        if (state >= 242) goto state_other;
        if (state < 240) goto state_other;
        count = 8;
        ASM_TAILSLOT_PIN(count);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800240D0();
        return;
state_1: {
            register s32 frames_left ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            frames_left = (s16)count;
            state = 20;
            count = state - frames_left;
            ASM_TAILSLOT_PIN(count);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800240D0();
            return;
        }
state_2:
        count = 8;
        ASM_TAILSLOT_PIN(count);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800240D0();
        return;
state_other:
        count = -1;

        ASM_KEEP(count);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        distance = count;
        while (distance >= 0) {
            particle = (u8 *)func_8003FD64(786, D_80083498);
            if (particle != 0) {
                func_8004491C(particle, D_80045340);
                render_data = (u8 *)S32(particle, 12);
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                {
                    register u8 *callback ASM_REG("$8") = D_800249DC_store;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    S32(particle, 16) = (s32)callback;
                }
                U16(S32(particle, 8), 2) = (u16)(U16(motion, 2) +
                                             (func_80069EF8() & 0x1ff) - 256);
                U16(S32(particle, 8), 6) = (u16)(U16(motion, 6) +
                                             (func_80069EF8() & 0x1ff) - 256);
                U16(S32(particle, 8), 10) = (u16)(U16(motion, 10) +
                                              (func_80069EF8() & 0xf) - 8);
                particle_data = particle + 32;
                S32(particle_data, 28) = S32(motion, 0);
                S32(particle_data, 32) = S32(motion, 4);
                S32(particle_data, 36) = S32(motion, 8);
                S32(particle_data, 52) = S32(motion, 12);
                S32(particle_data, 56) = S32(motion, 16);
                S32(particle_data, 60) = S32(motion, 20);
                U16(particle_data, 72) = U16(effect, 80);

                {
                    s32 init_word = 0x101010;
                    s32 flags;
                    register u8 *template ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    s32 template_word;
                    S16(render_data, 30) = 4096;
                    S16(render_data, 28) = 4096;
                    S16(render_data, 16) = 32;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    flags = U16(render_data, 20);
                    ASM_KEEP(flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    template = D_800DECF8;
                    S32(render_data, 12) = init_word;
                    init_word = (s32)template;
                    ASM_KEEP(init_word);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    S32(render_data, 0) = (s32)template;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    flags |= 0xc;
                    S16(render_data, 20) = (u16)flags;
                    template_word = S32((u8 *)init_word, 4);
                    U8(render_data, 4) = 0;
                    U8(render_data, 5) = 0;
                    S32(render_data, 8) = template_word;
                }
                S32(particle, 32) = (s32)effect;
                S16(particle_data, 76) = 0;
            }
            distance--;
        }
    }

    {
        s32 mode = S16(effect, 10);
        if (mode == 240) goto mode_240;
        if (mode < 241) {
            if (mode == 1) goto mode_1;
            if (mode >= 2) goto mode_ge_2;
            if (mode == 0) goto mode_0;
            func_80024764();
            return;
mode_ge_2:
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            if (mode == 2) goto mode_2;
            func_80024764();
            return;
        }
        if (mode == 255) goto mode_255;
        if (mode < 256) {
            if (mode == 241) goto mode_241;
            func_80024764();
            return;
        }
        if (mode == 256) goto mode_256;
        func_80024764();
        return;

mode_0: {
            s32 target;
            s32 delta_x;
            register s32 delta_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 abs_y;
            if ((U16(S32(effect, 4), 0) & 0x80) != 0) {
                if (func_8003DE58(S32(S32(actor_header, 12), 8), S32(actor_header, 12), offset, 0) == 0) {
                    offset[1] = 0;
                    offset[0] = 0;
                    offset[2] = (U16(actor_data, 20) & 0x8000) ? -48 : 0;
                }
                target = func_800A05A4(actor, U8(actor_data, 36), U8(actor_data, 37), S16(actor, 42),
                                     (s16)func_800A3820(36));
                S32(actor, 96) = target;
                if (target == 0) {
                    U8(actor, 114) = U8(actor_data, 36);
                    U8(actor, 115) = U8(actor_data, 37);
                    func_80024388();
                    return;
                }
                render_data = (u8 *)S32(target, -20);
                if ((U16(render_data, 20) & 0x8000) != 0) {
                    register u8 *context_data ASM_REG("$8") = (u8 *)context_arg;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    if ((U16(context_data, 20) & 0x8000) != 0) {
                        goto set_state_240;
                    }
                }
                U8(actor, 114) = U8(render_data, 36);
                U8(actor, 115) = U8(render_data, 37);
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                {
                    u8 *effect_header = effect - 32;
                    u8 *callback = D_80024798;
                    S32(motion, 0) = S32(S32(actor_header, 8), 0) + ((s32)offset[0] << 16);
                    S32(motion, 4) = S32(S32(actor_header, 8), 4) + ((s32)offset[1] << 16);
                    S32(motion, 8) = S32(S32(actor_header, 8), 8) + ((s32)offset[2] << 16);
                    func_8004491C(effect_header, callback);
                }
                delta_x = S8(actor, 114);
                delta_y = U8(actor_data, 36);
                abs_y = U8(actor_data, 37);
                delta_x -= delta_y;
                delta_y = S8(actor, 115);
                if (delta_x < 0) {
                    distance = delta_x;
                    ASM_KEEP_NV(distance);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    distance = -distance;
                } else {
                    distance = delta_x;
                }
                delta_y -= abs_y;
                if (delta_y < 0) {
                    abs_y = delta_y;
                    ASM_KEEP_NV(abs_y);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    abs_y = -abs_y;
                } else {
                    abs_y = delta_y;
                }
                if (distance < abs_y) distance = abs_y;
                if (distance < 4) distance = 4;
                delta_y = distance << 2;
                U16(effect, 80) = (u16)delta_y;
                ASM_KEEP_NV(delta_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                delta_y = (s16)delta_y;
                abs_y = S8(actor, 114);
                delta_x = S16(motion, 2);
                abs_y <<= 6;
                distance = abs_y + 32;
                delta_x = distance - delta_x;
                delta_x /= delta_y;
                delta_y = S8(actor, 115);
                delta_y <<= 6;
                abs_y = delta_y + 32;
                delta_y = S16(motion, 6);
                S32(motion, 12) = delta_x << 16;
                delta_x = S16(effect, 80);
                delta_y = abs_y - delta_y;
                delta_y /= delta_x;
                S32(motion, 16) = delta_y << 16;
                tile_x = (S8(actor, 114) << 6) & 0xffc0;
                tile_y = (S8(actor, 115) << 6) & 0xffc0;
                distance = (s16)func_800BCB04(tile_x, tile_y, U16(S32(actor_header, 8), 10) - 48) - 192;
                {
                    s32 velocity_z;
                    s32 travel_frames;
                    velocity_z = S16(motion, 10);
                    travel_frames = S16(effect, 80);
                    velocity_z = (distance - velocity_z) / travel_frames;
                    S32(motion, 20) = velocity_z << 16;
                }
                U16(effect, 82) = 0;
                func_800A56E0(768);
                {
                    s32 next_state;
                    next_state = (s32)(u16)U16(effect, 10) + 1;
                    ASM_TAILSLOT_PIN(next_state);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    func_80024728();
                }
                return;
            }
        }
            goto mode_done;

mode_1: {
            s16 frame_counter;
            if (S16(effect, 80) >= 0) {
                S32(motion, 0) += S32(motion, 12);
                S32(motion, 4) += S32(motion, 16);
                S32(motion, 8) += S32(motion, 20);
            }
            frame_counter = (u16)U16(effect, 82) + 1;
            U16(effect, 82) = (u16)frame_counter;
            if (frame_counter >= 8) {
                U16(effect, 82) = 4;
            }
            if (S16(effect, 80) <= 0 && S16(effect, 82) == 7) {
                register s32 hold_frames ASM_REG("$3") = 8;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                s32 current_state = U16(effect, 10);
                ASM_KEEP_DEP_NV(hold_frames, current_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                U16(effect, 80) = (u16)hold_frames;
                func_80024724();
                return;
            }
            goto mode_done;
        }

mode_2: {
            u16 frame_counter = (u16)U16(effect, 82) + 1;
            U16(effect, 82) = frame_counter;
            if (S16(effect, 80) == mode) {
                if (S32(actor, 96) != 0) {
                    particle = (u8 *)func_8003FD64(770, D_80083498);
                    if (particle != 0) {
                        func_8004491C(particle, D_80024C7C);
                        S32(particle, 16) = (s32)D_80024B60;
                        {
                            s32 coordinate = S8(actor, 114);
                            particle_data = particle + 32;
                            S16(particle_data, 12) = coordinate << 6;
                            coordinate = S8(actor, 115);
                            S16(particle_data, 14) = coordinate << 6;
                            S16(particle_data, 16) = U16(motion, 10);
                        }
                        S32(particle, 32) = (s32)effect;
                        S16(particle_data, 76) = 0;
                    }
                }
            }
            if (S16(effect, 80) <= 0) {
                if (S32(actor, 96) != 0) {
set_state_240:
                    U16(effect, 10) = 240;
                    func_80024764();
                    return;
                }
                goto cleanup_state;
            }
            goto mode_done;
        }

mode_240:
            func_80044A50(effect - 32);
            U16(effect, 80) = 10;
            func_800419EC(8, 16);
            {
                s32 next_state;
                next_state = (s32)(u16)U16(effect, 10) + 1;
                ASM_TAILSLOT_PIN(next_state);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                func_80024728();
            }
            return;

mode_241:
            func_8002506C(S32(actor, 96), S16(effect, 80));
            if (S16(effect, 80) == 6 && func_8009D218(S32(actor, 96), 4, actor) == 0 &&
                S32(actor, 96) != 0) {
                func_800C8900(S32(actor, 96), U8(D_800E3D68, 0) == 255 ? 255 : 16, 4);
            }
            if (S16(effect, 80) > 0) goto mode_done;
cleanup_state:
            func_80044A50(effect - 32);
            U16(effect, 10) = 255;
            func_80024764();
            return;

mode_255: {
            s32 effect_flags;
            effect_flags = S32(effect, 16);
            if ((effect_flags & 0x8000) != 0) {
                S32(effect, 16) = effect_flags & ~0x8000;
                func_80024764();
                return;
            } else {
                U16(effect, 80) = 10;
                U16(effect, 10) = (u16)(U16(effect, 10) + 1);
                func_80024764();
                return;
            }
        }

mode_256:
            if (S16(effect, 80) < 0) {
                D_8008346C[0] = 0;
                U16(effect, -2) = (u16)(U16(effect, -2) | 0x8000);
                D_800814A0[0] |= 0x8000;
            }
mode_done:
            ;
    }
}
