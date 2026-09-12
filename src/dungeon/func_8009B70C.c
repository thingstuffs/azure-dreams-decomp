#include "common.h"

typedef struct { u8 b0; u8 b1; u8 b2; u8 b3; } Elem;
typedef struct { u8 pad0[0xE]; s16 fieldE; u8 pad1[4]; } E2970;

extern E2970 D_800E2970[];
extern s16 D_8006CD00[];
extern s16 D_8006CD02[];
extern u16 D_8008347E;
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];

extern Elem *func_8009FCAC(s32);
extern s16 func_800A6D30(void);
extern s32 func_800A0818(u8, u8, s8, s8, u16 *);
extern s16 func_800BCB04(u16, u16, s32);

s32 func_800A0E6C(void *arg0, s32 arg1, void *arg2, u16 *arg3) {
    register u8 *p3 ASM_REG("$19") = (u8 *)arg0;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *p4 = (u8 *)arg2;
    u16 *fp = arg3;
    Elem *s1;
    Elem *scan_entry;
    Elem *entry;
    s16 s0;
    s16 i;
    s16 count;
    s16 c2;
    s16 c3;
    register s32 mod ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 r;
    s32 dir;
    s32 zero;
    u8 type;
    s32 b72, b73;
    s32 d;
    s32 s5v;
    s16 idx;
    register s32 tail ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    E2970 *ct2;
    E2970 *ct1;
    E2970 *table;
    s16 *offsets;
    u16 *x_offsets;
    s32 scan_s0;
    s32 bitmap_idx;
    u8 *bit_next;
    u8 *bit_prev_v0;
    u8 *bit_prev_s0;
    u8 bitmap[8];

    if (*(s8 *)(p3 + 0x26) < 0) {
        goto L_BD00;
    }

    b72 = p4[0x72];
    b73 = p4[0x73];
    if (((b72 | b73) != 0) && (*(s8 *)(p3 + 0x26) == (s16)arg1)) {
        goto L_B9A8;
    }

    p4[0x73] = 0;
    p4[0x72] = 0;
    p4[0x67] = 0;
    p3[0x27] = 0xFF;
    s1 = func_8009FCAC(*(s8 *)(p3 + 0x26));
    if (s1 != 0) {
        count = D_800E2970[*(s8 *)(p3 + 0x26)].fieldE;
        if (count > 0) {
            i = 0;
            do {
                tail = (s16)i * sizeof(Elem);
                scan_entry = (Elem *)((unsigned long)tail + (unsigned long)s1);
                if (scan_entry->b0 != 0) {
                    tail = p3[0x24];
                    d = *(volatile u8 *)&scan_entry->b0;
                    tail -= d;
                    if (tail < 0) tail = -tail;
                    if (tail < 2) {
                        tail = p3[0x25];
                        d = scan_entry->b1;
                        tail -= d;
                        if (tail < 0) tail = -tail;
                        if (tail < 2) {
                            goto L_B998;
                        }
                    }
                }
                i++;
            } while ((s16)i < count);
        }
L_B84C:
        i = 0;
        s0 = func_800A6D30();
        ct1 = D_800E2970;
        if (c3 = ct1[*(s8 *)(p3 + 0x26)].fieldE, type = p3[0x26], c3 > 0) {
            table = ct1;
            do {
                zero = (s16)s0;
                mod = (s8)type;
                c2 = table[mod].fieldE;
                mod = zero % c2;
                entry = (Elem *)((unsigned long)((s16)mod * sizeof(Elem)) + (unsigned long)s1);
                s0 = mod;
                if (entry->b0 != 0) {
                    if (p3[0x27] != (s16)mod) {
                        zero = 0;
                        dir = p4[0x67];
                        switch (dir) {
                        case 0:
                            tail = *(s16 *)&entry->b2 < 2;
                            break;
                        case 1:
                            tail = *(s16 *)&entry->b2 == 2;
                            break;
                        case 2:
                            tail = *(s16 *)&entry->b2 == 0;
                            break;
                        default:
                            goto L_DIR1_DONE;
                        }
                        zero = tail;
L_DIR1_DONE:
                        tail = zero;
                        ASM_KEEP(tail);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        if (tail) {
                            goto L_BCB8;
                        }
                    }
                }
                i++;
                s0++;
            } while (c3 = table[*(s8 *)(p3 + 0x26)].fieldE, type = p3[0x26], (s16)i < c3);
            return 0;
        }
    }
    return 0;

L_B998:
    p3[0x27] = i;
    p4[0x67] = scan_entry->b2;
    goto L_B84C;

L_B9A8:
    if ((p3[0x24] == b72) && (p3[0x25] == b73)) {
        s1 = func_8009FCAC(*(s8 *)(p3 + 0x26));
        if (s1 == 0) {
            goto L_RET0;
        }
        s0 = D_8008347E;
        ct2 = D_800E2970;
        if (c3 = ct2[*(s8 *)(p3 + 0x26)].fieldE, type = p3[0x26], c3 > 0) {
            i = 0;
            table = ct2;
            do {
                zero = (s16)s0;
                mod = (s8)type;
                c2 = table[mod].fieldE;
                mod = zero % c2;
                entry = (Elem *)((unsigned long)((s16)mod * sizeof(Elem)) + (unsigned long)s1);
                s0 = mod;
                if (entry->b0 != 0) {
                    if (p3[0x27] != (s16)mod) {
                        zero = 0;
                        switch (p4[0x67]) {
                        case 0:
                            tail = *(s16 *)&entry->b2 < 2;
                            break;
                        case 1:
                            tail = *(s16 *)&entry->b2 == 2;
                            break;
                        case 2:
                            tail = *(s16 *)&entry->b2 == 0;
                            break;
                        default:
                            goto L_DIR2_DONE;
                        }
                        zero = tail;
L_DIR2_DONE:
                        tail = zero;
                        ASM_KEEP(tail);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                        if (tail) {
                            goto L_BCB8;
                        }
                    }
                }
                i++;
                s0++;
            } while (c3 = table[*(s8 *)(p3 + 0x26)].fieldE, type = p3[0x26], (s16)i < c3);
            return 0;
        }
        return 0;
    }

L_BB24: {
    s32 masked;
    u32 base_page;
    s32 call_a2;

    tail = (s16)((((s16)*(u16 *)(p4 + 0x2A) >> 9) - 4) & 7);
    *(s32 *)&bitmap[0] = 0;
    *(s32 *)&bitmap[4] = 0;
    bit_next = &bitmap[tail];
    *bit_next = 1;
    idx = (tail + 1) & 7;
    bit_next = &bitmap[idx];
    tail = (tail - 1) & 7;
    bit_prev_v0 = &bitmap[tail];
    *bit_next = 1;
    *bit_prev_v0 = 1;
    i = 0;
    masked = (func_800A0818(p3[0x24], p3[0x25], *(s8 *)(p4 + 0x72), *(s8 *)(p4 + 0x73), fp) & 0xFFF) << 16;
    s5v = masked >> 16;
    ASM_KEEP(s5v);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    base_page = 0x80070000;
    ASM_KEEP_NV(base_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    offsets = (s16 *)(base_page - 0x3300);
    base_page = 0x800E0000;
    ASM_KEEP_NV(base_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    x_offsets = (u16 *)(base_page - 0x3154);
    tail = (s16)(((masked >> 25) - 4) & 7);
    bit_next = &bitmap[tail];
    *bit_next = 1;
    idx = (tail + 1) & 7;
    bit_next = &bitmap[idx];
    tail = (tail - 1) & 7;
    bit_prev_s0 = &bitmap[tail];
    *bit_next = 1;
    *bit_prev_s0 = 1;
    do {
        if (*fp & 2) {
            tail = s5v - offsets[(s16)i];
        } else {
            tail = s5v + offsets[(s16)i];
        }
        scan_s0 = (tail >> 9) & 7;
        s0 = scan_s0;
        bitmap_idx = scan_s0;
        ASM_KEEP_NV(bitmap_idx);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if (bitmap[bitmap_idx] == 0) {
            bitmap_idx <<= 1;
            bit_next = (u8 *)(bitmap_idx + (s32)x_offsets);
            masked = p3[0x24];
            zero = *(u16 *)bit_next;
            call_a2 = *(u16 *)(p4 + 0x88);
            masked <<= 6;
            zero += masked;
            zero &= 0xFFFF;
            ASM_USE(zero);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            masked = (s32)&D_800DCEBC;
            bitmap_idx += masked;
            call_a2 = (s16)(call_a2 - 0x20);
            masked = p3[0x25];
            bitmap_idx = *(u16 *)bitmap_idx;
            masked <<= 6;
            bitmap_idx += masked;
            bitmap_idx &= 0xFFFF;
            r = func_800BCB04(zero, bitmap_idx, call_a2);
            if ((s16)r < 0x200) {
                goto L_BD8C;
            }
        }
        i++;
    } while ((s16)i < 8);
    return 0;
}

L_BCB8:
    tail = (s16)s0 * sizeof(Elem);
    tail += (s32)s1;
    mod = *(u8 *)tail;
    p4[0x72] = mod;
    mod = *(u8 *)(tail + 1);
    p4[0x73] = mod;
    tail = *(u8 *)(tail + 2);
    p4[0x67] = tail;
    tail = func_800A0818(p3[0x24], p3[0x25], *(s8 *)(p4 + 0x72), *(s8 *)(p4 + 0x73), fp);
    *(u16 *)(p4 + 0x2A) = tail;
    p3[0x27] = s0;
    goto L_RET0;

L_BD00: {
    register s32 final_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    tail = 0xFF;
    mod = 0x80070000;
    ASM_KEEP_NV(mod);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    p3[0x27] = tail;
    final_a2 = *(u16 *)(p4 + 0x88);
    tail = *(s16 *)(p4 + 0x2A);
    mod = *(s16 *)(mod - 0x32FE);
    final_a2 = (s16)(final_a2 - 0x20);
    tail -= mod;
    tail >>= 9;
    scan_s0 = tail & 7;
    r = func_800BCB04(D_800DCEAC[scan_s0] + (p3[0x24] << 6),
                      D_800DCEBC[scan_s0] + (p3[0x25] << 6), final_a2);
    if ((s16)r < 0x200) {
        goto L_BD8C;
    }
    return 0;
}

L_BD8C:
    tail = scan_s0 << 9;
    *(u16 *)(p4 + 0x2A) = tail;
L_RET0:
    return 0;
}
