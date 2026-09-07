#include "common.h"

typedef struct Command Command;
typedef struct Entry Entry;
typedef struct Packet Packet;

struct Entry {
    u8 pad00[6];
    s16 depth_bias;
    Command *commands;
    union {
        u32 word;
        struct {
            u8 b0;
            u8 b1;
            u8 b2;
            u8 mode;
        } bytes;
    } packet;
    u16 texture_bias;
    u16 texture_base;
    u16 flags;
    u16 angle_x;
    u16 angle_y;
    u16 angle_z;
    u16 scale_x;
    u16 scale_y;
    u16 sprite_w;
    u16 sprite_h;
};

struct Command {
    u8 flags;
    u8 mode;
    s8 x;
    s8 y;
    u16 attr;
    u16 texture_offset;
    u8 x0;
    u8 y0;
    u8 x1;
    u8 y1;
};

struct Packet {
    u32 tag;
    u32 packet_word;
    u16 x0;
    u16 y0;
    u16 u0;
    u16 v0;
    u16 x1;
    u16 y1;
    u16 u1;
    u16 attr;
    u16 x2;
    u16 y2;
    u16 u2;
    u16 v2;
    u16 x3;
    u16 y3;
    u16 u3;
    u16 v3;
};

typedef s32 (*CommandFn)(void *, void *, Entry *, Command *, Packet *);

extern void *D_80083160[3];
extern u32 D_8006CD30[8];
extern s32 D_80081510;

extern u32 RotTransPers(void *, void *, void *, void *);
extern void RotTransPers4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void RotMatrix(void *, void *);
extern void ScaleMatrix(void *, void *);
extern void CompMatrix(void *, void *, void *);
extern void SetTransMatrix(void *);
extern void SetRotMatrix(void *);

#define SP8(base, off)  (*(u8 *)((base) + (off)))
#define SPS8(base, off) (*(s8 *)((base) + (off)))
#define SP16(base, off) (*(u16 *)((base) + (off)))
#define SPS16(base, off) (*(s16 *)((base) + (off)))
#define SP32(base, off) (*(u32 *)((base) + (off)))
#define E8(base, off) (*(u8 *)((u8 *)(base) + (off)))
#define E16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define E32(base, off) (*(u32 *)((u8 *)(base) + (off)))
#define C8(base, off) (*(u8 *)((u8 *)(base) + (off)))
#define CS8(base, off) (*(s8 *)((u8 *)(base) + (off)))
#define C16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define P16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define PS16(base, off) (*(s16 *)((u8 *)(base) + (off)))
#define P32(base, off) (*(u32 *)((u8 *)(base) + (off)))

void func_800453E0(void *arg0, void *arg1, Entry *entry, s16 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    void **global = D_80083160;
    Packet *packet;
    Command *command;
    void *rotation_matrix;
    u32 projected;
    u32 adjusted;
    s32 callback_result;
    s16 coord;
    s16 coord_a;
    s16 coord_b;
    u32 extent;
    u16 rotation_y;
    s32 rotation_x;
    u32 scale_x;
    u32 scale_y;
    u32 visible0;
    u32 visible1;
    u32 visible2;
    u32 visible3;
    u32 combined;
    u32 value;
    u32 flags;
    u32 low_mask;
    u8 first;
    u8 second;

    SP32(scratch, 0xEC) = 0;
    SP16(scratch, 0x8C) = 0;
    SP16(scratch, 0x84) = 0;
    SP16(scratch, 0x7C) = 0;
    SP16(scratch, 0x74) = 0;
    SP32(scratch, 0x20) = (u32)global[0] + 0xB0;

    SP16(scratch, 0x00) = *(u16 *)((u8 *)arg1 + 2);
    SP16(scratch, 0x02) = *(u16 *)((u8 *)arg1 + 6);
    SP16(scratch, 0x04) = *(u16 *)((u8 *)arg1 + 0xA);
    packet = *(Packet **)((u8 *)global[0] + 0x8D0);

    SP32(scratch, 0xC0) = RotTransPers(scratch, scratch + 0xB8, scratch + 0x90, scratch + 0x94);
    E16(entry, 0x14) |= 0x8000;
    projected = *(volatile u32 *)(scratch + 0xC0);
    {
        u32 bias_temp;
        adjusted = (bias_temp = projected - 10, bias_temp - depth_bias);
    }
    D_8006CD30[7] = projected * 4;
    SP32(scratch, 0xC0) = adjusted;

    if (adjusted < 0x1D6U) {
        PushMatrix();
        low_mask = 0xFFFFFF;

        {
        register u8 *rotation_input ASM_REG("$4");
        u16 b8_value;
        register u32 a1blk ASM_REG("$5");
        s32 v104;
        rotation_input = scratch;
        ASM_KEEP_NV(rotation_input);
        b8_value = *(volatile u16 *)(scratch + 0xB8);
        ASM_USE_NV(b8_value);
        rotation_input = (u8 *)((u32)rotation_input | 0x100);
        ASM_KEEP_NV(rotation_input);
        SP16(scratch, 0xB8) = b8_value - 0xA0;
        SP16(scratch, 0xBA) -= 0x78;
        SP32(scratch, 0x30) = *(s16 *)((u8 *)global + 0xC4);
        SP32(scratch, 0x34) = *(s16 *)((u8 *)global + 0xC6);
        SP32(scratch, 0x38) = *(s16 *)((u8 *)global + 0xC8);

        SP16(scratch, 0x100) = E16(entry, 0x16);
        ASM_KEEP_NV(a1blk);
        v104 = *(u16 *)((u8 *)global + 0xB8) +
            (E16(entry, 0x1A) - SP16(scratch, 0x34));
        SP16(scratch, 0x104) = v104;
        ASM_USE2_NV(a1blk, v104);
        rotation_x = E16(entry, 0x18) - 0x100;
        rotation_x += (SP16(scratch, 0x38) + 0x100) & 0x1FF;
        SP16(scratch, 0x102) = rotation_x;
        extent = E16(entry, 0x20);
        SP32(scratch, 0xE4) = extent;
        SP16(scratch, 0x108) = extent;
        extent = E16(entry, 0x22);
        SP32(scratch, 0xE8) = extent;
        SP16(scratch, 0x10A) = extent;

        RotMatrix(rotation_input, scratch + 0xD0);
        }
        scale_x = E16(entry, 0x1C);
        SP32(scratch, 0x30) = scale_x;
        scale_y = E16(entry, 0x1E);
        SP32(scratch, 0x38) = 0x1000;
        SP32(scratch, 0x34) = scale_y;
        ScaleMatrix(scratch + 0xD0, scratch + 0x30);
        CompMatrix(D_8006CD30, scratch + 0xD0, scratch + 0x50);
        SetTransMatrix(scratch + 0x50);
        SetRotMatrix(scratch + 0x50);

        command = *(Command **)((u8 *)entry + 8);
        SP16(scratch, 0x24) = E16(entry, 0x14);

        do {
            if (!(C8(command, 0) & 0x20)) {
                first = C8(command, 8);
                SP32(scratch, 0x08) = first;
                second = C8(command, 0xA);
                SP32(scratch, 0x10) = second;
                if ((first + second >= 0x100) || E16(entry, 0x1A) != 0) {
                    SP32(scratch, 0x10) = second - 1;
                }

                first = C8(command, 9);
                SP32(scratch, 0x0C) = first;
                second = C8(command, 0xB);
                SP32(scratch, 0x14) = second;
                if ((first + second >= 0x100) || E16(entry, 0x1A) != 0) {
                    SP32(scratch, 0x14) = second - 1;
                }

                if ((C8(command, 0) ^ SP16(scratch, 0x24)) & 1) {
                    coord = -CS8(command, 2) - SP16(scratch, 0x108);
                    SP16(scratch, 0x80) = coord;
                    SP16(scratch, 0x70) = coord;
                    coord -= SP16(scratch, 0x10);
                    SP16(scratch, 0x88) = coord;
                    SP16(scratch, 0x78) = coord;
                } else {
                    coord = CS8(command, 2) - SP16(scratch, 0x108);
                    SP16(scratch, 0x80) = coord;
                    SP16(scratch, 0x70) = coord;
                    coord += SP16(scratch, 0x10);
                    SP16(scratch, 0x88) = coord;
                    SP16(scratch, 0x78) = coord;
                }

                if ((C8(command, 0) ^ SP16(scratch, 0x24)) & 2) {
                    coord = SP16(scratch, 0x13C) + (-CS8(command, 3) - SP16(scratch, 0x10A));
                    SP16(scratch, 0x7A) = coord;
                    SP16(scratch, 0x72) = coord;
                    coord -= SP16(scratch, 0x14);
                    SP16(scratch, 0x8A) = coord;
                    SP16(scratch, 0x82) = coord;
                } else {
                    coord = SP16(scratch, 0x13C) + (CS8(command, 3) - SP16(scratch, 0x10A));
                    SP16(scratch, 0x7A) = coord;
                    SP16(scratch, 0x72) = coord;
                    coord += SP16(scratch, 0x14);
                    SP16(scratch, 0x8A) = coord;
                    SP16(scratch, 0x82) = coord;
                }

                RotTransPers4(scratch + 0x70, scratch + 0x78,
                    scratch + 0x80, scratch + 0x88,
                    scratch + 0xF0, scratch + 0xF4,
                    scratch + 0xF8, scratch + 0xFC,
                    scratch + 0x90, scratch + 0x94);

                *(volatile u16 *)((u8 *)packet + 0x08) = SP16(scratch, 0xF0) + SP16(scratch, 0xB8);
                *(volatile u16 *)((u8 *)packet + 0x0A) = SP16(scratch, 0xF2) + SP16(scratch, 0xBA);
                *(volatile u16 *)((u8 *)packet + 0x10) = SP16(scratch, 0xF4) + SP16(scratch, 0xB8);
                *(volatile u16 *)((u8 *)packet + 0x12) = SP16(scratch, 0xF6) + SP16(scratch, 0xBA);
                *(volatile u16 *)((u8 *)packet + 0x18) = SP16(scratch, 0xF8) + SP16(scratch, 0xB8);
                *(volatile u16 *)((u8 *)packet + 0x1A) = SP16(scratch, 0xFA) + SP16(scratch, 0xBA);
                visible0 = 0;
                *(volatile u16 *)((u8 *)packet + 0x20) = SP16(scratch, 0xFC) + SP16(scratch, 0xB8);
                coord = SP16(scratch, 0xFE) + SP16(scratch, 0xBA);
                P16(packet, 0x22) = coord;

                if ((u16)(P16(packet, 8) + 0x20) < 0x181U) {
                    visible0 = (u16)(P16(packet, 0xA) + 0x20) < 0x121U;
                }
                visible1 = 0;
                if ((u16)(P16(packet, 0x10) + 0x20) < 0x181U) {
                    visible1 = (u16)(P16(packet, 0x12) + 0x20) < 0x121U;
                }
                visible2 = 0;
                if ((visible0 = visible1 | visible0,
                     (u16)(P16(packet, 0x18) + 0x20) < 0x181U)) {
                    visible2 = (u16)(P16(packet, 0x1A) + 0x20) < 0x121U;
                }
                visible3 = 0;
                if ((combined = visible0 | visible2,
                     (u16)(P16(packet, 0x20) + 0x20) < 0x181U)) {
                    visible3 = (u16)(coord + 0x20) < 0x121U;
                }
                if (combined | visible3) {
                    *(u8 *)((u8 *)packet + 3) = 9;
                    E16(entry, 0x14) &= 0x7FFF;

                    SP32(scratch, 0x10) += SP32(scratch, 0x08);
                    SP32(scratch, 0x14) =
                        (SP32(scratch, 0x14) + SP32(scratch, 0x0C)) << 8;
                    SP32(scratch, 0x0C) <<= 8;

                    if (SP16(scratch, 0x24) & 0x100) {
                        P16(packet, 0xE) = E16(entry, 0x12);
                    } else {
                        P16(packet, 0xE) = E16(entry, 0x12) + C16(command, 6);
                    }
                    P16(packet, 0xC) = SP16(scratch, 0x0C) + SP16(scratch, 0x08);
                    P16(packet, 0x14) = SP16(scratch, 0x0C) + SP16(scratch, 0x10);
                    if (E16(entry, 0x10) != 0) {
                        P16(packet, 0x16) = E16(entry, 0x10) + (C16(command, 4) & 0xFF9F);
                    } else {
                        P16(packet, 0x16) = C16(command, 4);
                    }
                    P16(packet, 0x1C) = SP16(scratch, 0x14) | SP16(scratch, 0x08);
                    P16(packet, 0x24) = SP16(scratch, 0x14) | SP16(scratch, 0x10);

                    if (SPS16(scratch, 0x50) >= 0x1800) {
                        value = *(u8 *)((u8 *)packet + 0x24);
                        *(u8 *)((u8 *)packet + 0x24) = value + 0xFF;
                        *(u8 *)((u8 *)packet + 0x14) = value;
                    }
                    if (SPS16(scratch, 0x58) >= 0x1800) {
                        value = *(u8 *)((u8 *)packet + 0x25);
                        *(u8 *)((u8 *)packet + 0x25) = value + 0xFF;
                        *(u8 *)((u8 *)packet + 0x1D) = value;
                    }
                    if (PS16(packet, 8) > PS16(packet, 0x20)) {
                        value = *(u8 *)((u8 *)packet + 0x24);
                        *(u8 *)((u8 *)packet + 0x24) = value + 0xFF;
                        *(u8 *)((u8 *)packet + 0x14) = value;
                    }
                    if (PS16(packet, 0xA) > PS16(packet, 0x22)) {
                        value = *(u8 *)((u8 *)packet + 0x25);
                        *(u8 *)((u8 *)packet + 0x25) = value + 0xFF;
                        *(u8 *)((u8 *)packet + 0x1D) = value;
                    }

                    {
                        u32 flag_first;
                        u32 flag_bits;
                        u32 flag_value;
                        flag_first = C8(command, 1);
                        E8(entry, 0x0F) = flag_first;
                        flag_bits = SP16(scratch, 0x24);
                        if (flag_bits & 8) {
                            if (flag_bits & 4) {
                                flag_value = flag_first | 2;
                            } else {
                                flag_value = flag_first & 0xFD;
                            }
                            E8(entry, 0x0F) = flag_value;
                        }
                    }

                    P32(packet, 4) = E32(entry, 0x0C);
                    {
                        s32 depth_delta;
                        depth_delta = -((u32)(D_80081510 * CS8(command, 3)) >> 14);
                        SP32(scratch, 0xCC) = depth_delta;
                        if (depth_delta > 0) {
                            SP32(scratch, 0xCC) = 0;
                        }
                    }

                    {
                        u32 c0_or_high = SP32(scratch, 0xC0);
                        u32 cc_value = SP32(scratch, 0xCC);
                    if (c0_or_high + cc_value < 0x1D6U) {
                        u32 c0_scaled;
                        u32 cc_scaled;
                        u32 table_base;
                        do {
                            cc_scaled = cc_value * 4;
                            c0_scaled = c0_or_high * 4;
                        } while (0);
                        table_base = SP32(scratch, 0x20);
                        c0_or_high = 0xFF000000;
                        c0_scaled += table_base;
                        cc_scaled += c0_scaled;
                        P32(packet, 0) = (P32(packet, 0) & c0_or_high) |
                            (*(u32 *)cc_scaled & low_mask);
                        *(u32 *)(SP32(scratch, 0x20) +
                            (SP32(scratch, 0xC0) * 4) +
                            (SP32(scratch, 0xCC) * 4)) =
                            (*(u32 *)(SP32(scratch, 0x20) +
                            (SP32(scratch, 0xC0) * 4) +
                            (SP32(scratch, 0xCC) * 4)) & c0_or_high) |
                            ((u32)packet & low_mask);
                    }
                    }
                    packet++;
                }
            } else {
                CommandFn callback = *(CommandFn *)((u8 *)command + 8);
                if (callback != 0) {
                    SP32(scratch, 0xCC) = SP32(scratch, 0xC0);
                    callback_result = callback(arg0, arg1, entry, command, packet);
                    if (callback_result > 0) {
                        command = (Command *)(callback_result | 0x80000000U);
                    } else {
                        packet = (Packet *)callback_result;
                    }
                    SP32(scratch, 0xC0) = SP32(scratch, 0xCC);
                }
            }
        } while (CS8(command++, 0) >= 0);

        PopMatrix();
    }

    *(Packet **)((u8 *)global[0] + 0x8D0) = packet;
}
