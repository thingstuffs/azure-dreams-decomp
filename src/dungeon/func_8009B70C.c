#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_status.h"

typedef struct { u8 b0; u8 b1; u8 b2; u8 b3; } Elem;
typedef struct { u8 pad0[0xE]; s16 fieldE; u8 pad1[4]; } E2970;

extern s16 D_8006CD00[];
extern s16 D_8006CD02[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];

extern Elem *func_8009FCAC(s32);
extern s16 func_800A6D30(void);
extern s32 func_800A0818(u8, u8, s8, s8, u16 *);
extern s16 func_800BCB04(u16, u16, s32);

static __inline__ u8 direction_matches(Elem *entry, u8 direction) {
    u8 match = 0;
    switch (direction) {
    case 0:
        match = *(s16 *)& entry->b2 < 2;
        break;
    case 1:
        match = *(s16 *)& entry->b2 == 2;
        break;
    case 2:
        match = *(s16 *)& entry->b2 == 0;
        break;
    }
    return match;
}

/* Rebuild the actor's reachable-tile bitmap for its current move kind and hand back the chosen step. */
s32 func_800A0E6C(void *actor, s32 kind, void *work, u16 *out) {
    register u8 *actor_held ASM_REG("$19") = (u8 *)actor;
    u8 *work_p = (u8 *)work;
    u16 *out_p = out;
    Elem *s1;
    Elem *scan_entry;
    Elem *entry;
    s16 s0;
    s16 i;
    s16 count;
    s16 c2;
    s16 c3;
    s16 mod;
    s16 r;
    s32 zero;
    u8 type;
    s32 b72, b73;
    s32 d;
    s32 s5v;
    s16 idx;
    register s32 tail ASM_REG("$2");
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

    if (*(s8 *)(actor_held + 0x26) >= 0) {
        b72 = work_p[0x72];
        b73 = work_p[0x73];
        if (!(((b72 | b73) != 0) && (*(s8 *)(actor_held + 0x26) == (s16)kind))) {
            work_p[0x73] = 0;
            work_p[0x72] = 0;
            work_p[0x67] = 0;
            actor_held[0x27] = 0xFF;
            s1 = func_8009FCAC(*(s8 *)(actor_held + 0x26));
            if (s1 != 0) {
                count = D_800E2970[*(s8 *)(actor_held + 0x26)].unk_0E;
                if (count > 0) {
                    i = 0;
                    do {
                        tail = (s16)i * sizeof(Elem);
                        scan_entry = (Elem *)((unsigned long)tail + (unsigned long)s1);
                        if (scan_entry->b0 != 0) {
                            tail = actor_held[0x24];
                            d = *(u8 *)&scan_entry->b0;
                            tail -= d;
                            if (tail < 0)
                                tail = -tail;
                            if (tail < 2) {
                                tail = actor_held[0x25];
                                d = scan_entry->b1;
                                tail -= d;
                                if (tail < 0)
                                    tail = -tail;
                                if (tail < 2) {
                                    actor_held[0x27] = i;
                                    work_p[0x67] = scan_entry->b2;
                                    break;
                                }
                            }
                        }
                        i++;
                    } while ((s16)i < count);
                }
                i = 0;
                s0 = func_800A6D30();
                ct1 = D_800E2970;
                if (c3 = ct1[*(s8 *)(actor_held + 0x26)].fieldE, type = actor_held[0x26], c3 > 0) {
                    table = ct1;
                    do {
                        Elem *cand_entry;
                        zero = (s16)s0;
                        mod = (s8)type;
                        c2 = table[mod].fieldE;
                        mod = zero % c2;
                        cand_entry = (Elem *)((unsigned long)((s16)mod * sizeof(Elem)) + (unsigned long)s1);
                        s0 = mod;
                        if (cand_entry->b0 != 0) {
                            if (actor_held[0x27] != (s16)mod) {
                                tail = direction_matches(cand_entry, work_p[0x67]);
                                if (tail) {
                                    goto L_BCB8;
                                }
                            }
                        }
                        i++;
                        s0++;
                    } while (c3 = table[*(s8 *)(actor_held + 0x26)].fieldE, type = actor_held[0x26], (s16)i < c3);
                    return 0;
                }
            }
            return 0;
        }

        if ((actor_held[0x24] == b72) && (actor_held[0x25] == b73)) {
            s1 = func_8009FCAC(*(s8 *)(actor_held + 0x26));
            if (s1 != 0) {
                s0 = dungeonStatus.unk_1E;
                ct2 = D_800E2970;
                if (c3 = ct2[*(s8 *)(actor_held + 0x26)].fieldE, type = actor_held[0x26], c3 > 0) {
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
                            if (actor_held[0x27] != (s16)mod) {
                                tail = direction_matches(entry, work_p[0x67]);
                                if (tail) {
                                    goto L_BCB8;
                                }
                            }
                        }
                        i++;
                        s0++;
                    } while (c3 = table[*(s8 *)(actor_held + 0x26)].fieldE, type = actor_held[0x26], (s16)i < c3);
                }
            }
            return 0;
        }

        {
            s32 masked;
            s32 sh6;
            u32 base_page;
            s32 call_a2;

            tail = (s16)((((s16)*(u16 *)(work_p + 0x2A) >> 9) - 4) & 7);
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
            masked = (func_800A0818(actor_held[0x24], actor_held[0x25], *(s8 *)(work_p + 0x72), *(s8 *)(work_p + 0x73),
                out_p) & 0xFFF) << 16;
            s5v = masked >> 16;
            offsets = D_8006CD00;
            base_page = 0x800E0000;
            ASM_KEEP_NV(base_page);
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
                if (*out_p & 2) {
                    tail = s5v - offsets[(s16)i];
                } else {
                    tail = s5v + offsets[(s16)i];
                }
                scan_s0 = (tail >> 9) & 7;
                s0 = scan_s0;
                bitmap_idx = (s16)scan_s0;
                if (bitmap[bitmap_idx] == 0) {
                    bitmap_idx <<= 1;
                    bit_next = (u8 *)(bitmap_idx + (s32)x_offsets);
                    sh6 = actor_held[0x24];
                    zero = *(u16 *)bit_next;
                    call_a2 = *(u16 *)(work_p + 0x88);
                    sh6 <<= 6;
                    zero += sh6;
                    zero &= 0xFFFF;
                    ASM_USE(zero);
                    sh6 = (s32)&D_800DCEBC;
                    bitmap_idx += sh6;
                    call_a2 = (s16)(call_a2 - 0x20);
                    sh6 = actor_held[0x25];
                    bitmap_idx = *(u16 *)bitmap_idx;
                    sh6 <<= 6;
                    bitmap_idx += sh6;
                    bitmap_idx &= 0xFFFF;
                    r = func_800BCB04(zero, bitmap_idx, call_a2);
                    if ((s16)r < 0x200) {
                        tail = scan_s0 << 9;
                        *(u16 *)(work_p + 0x2A) = tail;
                        return 0;
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
        work_p[0x72] = mod;
        mod = *(u8 *)(tail + 1);
        work_p[0x73] = mod;
        tail = *(u8 *)(tail + 2);
        work_p[0x67] = tail;
        tail = func_800A0818(actor_held[0x24], actor_held[0x25], *(s8 *)(work_p + 0x72), *(s8 *)(work_p + 0x73), out_p);
        *(u16 *)(work_p + 0x2A) = tail;
        actor_held[0x27] = s0;
    } else {
        {
            s32 final_a2;
            s32 dir;

            tail = 0xFF;
            actor_held[0x27] = tail;
            final_a2 = *(u16 *)(work_p + 0x88);
            tail = *(s16 *)(work_p + 0x2A);
            mod = *D_8006CD02;
            final_a2 -= 0x20;
            final_a2 <<= 16;
            final_a2 >>= 16;
            dir = ((tail - mod) >> 9) & 7;
            r = func_800BCB04(D_800DCEAC[dir] + (actor_held[0x24] << 6),
                              D_800DCEBC[dir] + (actor_held[0x25] << 6), final_a2);
            if ((s16)r < 0x200) {
                tail = dir << 9;
                *(u16 *)(work_p + 0x2A) = tail;
            }
            return 0;
        }
    }
    return 0;
}
