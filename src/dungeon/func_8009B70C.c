#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_status.h"

typedef struct { u8 b0; u8 b1; u8 b2; u8 b3; } Elem;

extern s16 D_8006CD00[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];

extern Elem *func_8009FCAC(s16);
extern s32 func_800A6D30(void);
extern s32 func_800A0818(s16, s16, s16, s16, u16 *);
extern s32 func_800BCB04(s32, s32, s16);

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
s32 func_800A0E6C(u8 *actor_held, s32 kind, u8 *work_p, u16 *out) {
    Elem *s1;
    Elem *scan_entry;
    Elem *entry;
    s16 s0;
    s16 i;
    s16 count;
    s16 c3;
    s16 mod;
    u8 type;
    s32 b72, b73;
    s32 match;
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
                count = D_800E2970[(s8)actor_held[0x26]].unk_0E;
                for (i = 0; i < count; i++) {
                    scan_entry = (Elem *)((unsigned long)(i * sizeof(Elem)) + (unsigned long)s1);
                    if (scan_entry->b0 != 0 && abs(actor_held[0x24] - scan_entry->b0) < 2 && abs(actor_held[0x25] - scan_entry->b1) < 2) {
                        actor_held[0x27] = i;
                        work_p[0x67] = scan_entry->b2;
                        break;
                    }
                }
                i = 0;
                s0 = func_800A6D30();
                if (c3 = D_800E2970[*(s8 *)(actor_held + 0x26)].unk_0E, type = actor_held[0x26], c3 > 0) {
                    do {
                        Elem *cand_entry;
                        mod = s0 % D_800E2970[(s8)type].unk_0E;
                        cand_entry = (Elem *)((unsigned long)(mod * sizeof(Elem)) + (unsigned long)s1);
                        s0 = mod;
                        if (cand_entry->b0 != 0) {
                            if (actor_held[0x27] != (s16)mod) {
                                match = direction_matches(cand_entry, work_p[0x67]);
                                if (match) {
                                    goto L_BCB8;
                                }
                            }
                        }
                        i++;
                        s0++;
                    } while (c3 = D_800E2970[*(s8 *)(actor_held + 0x26)].unk_0E, type = actor_held[0x26], i < c3);
                    return 0;
                }
            }
            return 0;
        }

        if ((actor_held[0x24] == b72) && (actor_held[0x25] == b73)) {
            s1 = func_8009FCAC(*(s8 *)(actor_held + 0x26));
            if (s1 != 0) {
                s0 = dungeonStatus.unk_1E;
                if (c3 = D_800E2970[*(s8 *)(actor_held + 0x26)].unk_0E, type = actor_held[0x26], c3 > 0) {
                    i = 0;
                    do {
                        mod = s0 % D_800E2970[(s8)type].unk_0E;
                        entry = (Elem *)((unsigned long)(mod * sizeof(Elem)) + (unsigned long)s1);
                        s0 = mod;
                        if (entry->b0 != 0) {
                            if (actor_held[0x27] != (s16)mod) {
                                match = direction_matches(entry, work_p[0x67]);
                                if (match) {
                                    goto L_BCB8;
                                }
                            }
                        }
                        i++;
                        s0++;
                    } while (c3 = D_800E2970[*(s8 *)(actor_held + 0x26)].unk_0E, type = actor_held[0x26], i < c3);
                }
            }
            return 0;
        }

        {
            s16 angle;
            s16 d;
            s8 n;

            d = (((s16)*(u16 *)(work_p + 0x2A) >> 9) - 4) & 7;
            *(s32 *)&bitmap[0] = 0;
            *(s32 *)&bitmap[4] = 0;
            bitmap[d] = 1;
            bitmap[(d + 1) & 7] = 1;
            bitmap[(d - 1) & 7] = 1;
            angle = func_800A0818(actor_held[0x24], actor_held[0x25], *(s8 *)(work_p + 0x72), *(s8 *)(work_p + 0x73),
                out) & 0xFFF;
            d = ((angle >> 9) - 4) & 7;
            bitmap[d] = 1;
            bitmap[(d + 1) & 7] = 1;
            bitmap[(d - 1) & 7] = 1;
            for (i = 0; i < 8; i++) {
                if (*out & 2) {
                    d = ((angle - D_8006CD00[i]) >> 9) & 7;
                    n = d;
                } else {
                    d = ((angle + D_8006CD00[i]) >> 9) & 7;
                    n = d;
                }
                if (bitmap[n] == 0) {
                    if ((s16)func_800BCB04((u16)(D_800DCEAC[n] + (actor_held[0x24] << 6)), (u16)(D_800DCEBC[n] + (actor_held[0x25] << 6)), *(u16 *)(work_p + 0x88) - 0x20) < 0x200) {
                        *(u16 *)(work_p + 0x2A) = d << 9;
                        return 0;
                    }
                }
            }
            return 0;
        }

L_BCB8:
        work_p[0x72] = s1[s0].b0;
        work_p[0x73] = s1[s0].b1;
        work_p[0x67] = s1[s0].b2;
        *(u16 *)(work_p + 0x2A) = func_800A0818(actor_held[0x24], actor_held[0x25], *(s8 *)(work_p + 0x72), *(s8 *)(work_p + 0x73), out);
        actor_held[0x27] = s0;
    } else {
        s32 dir;

        actor_held[0x27] = 0xFF;
        dir = ((*(s16 *)(work_p + 0x2A) - D_8006CD00[1]) >> 9) & 7;
        if ((s16)func_800BCB04((u16)(D_800DCEAC[dir] + (actor_held[0x24] << 6)), (u16)(D_800DCEBC[dir] + (actor_held[0x25] << 6)),
                *(u16 *)(work_p + 0x88) - 0x20) < 0x200) {
            *(u16 *)(work_p + 0x2A) = dir << 9;
        }
    }
    return 0;
}
