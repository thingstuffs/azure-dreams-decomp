# Levels, EXP and MP

[Mechanics index](README.md) · [Combat](combat.md) · [Familiars](familiars.md)

## The generated EXP curve

Verified by reading
[`build_cubic_cumulative_table`](../../../src/engine/entity/build_cubic_cumulative_table.c),
[`lookup_level_experience_threshold`](../../../src/engine/entity/is_frame_packet_arena_overflowed.c)
and [`can_entity_gain_level`](../../../src/dungeon/player/object/can_entity_gain_level.c).
The threshold array `T = entity_level_thresholds` is generated at runtime:

```text
T[0] = 0
for i = 1 through 99:
    T[i] = T[i-1] + floor((i+3)^3 / 8) + 32 * max(i-20, 0)^2
```

At level `L < 99`, eligibility compares **accumulated** EXP with `T[L]`.
EXP is not subtracted on level-up. For example `T[1]=8`, `T[2]=23`,
`T[3]=50`, and `T[4]=92`. The quadratic correction first contributes at
index 21. A level-up item sets EXP to `T[L]` and clears the pending award,
rather than directly increasing a stat.
Verified by reading [`use_level_gain_item`](../../../src/dungeon/item/use_level_gain_item.c).

Eligibility also rejects negative species codes, frog status, lifted actors,
and actors flagged MP empty, paralyzed or asleep. There is an additional
player action-state check. The cap is 99; some separate spawn/egg loops keep
requesting growth after the cap and can hang:
[B016/B016S](../../BUGS.md#spawning-monsters-past-level-99).

## EXP rewards and sharing

Verified by reading `distribute_experience_awards` and
`accumulate_experience_award` in
[`can_entity_gain_level.c`](../../../src/dungeon/player/object/can_entity_gain_level.c).
The defeated source has a 16-bit EXP reward at +6 and a credited actor pointer
at +0x60. A null credit pointer or negative credited species gives no award.

For a party credit (`flags14 & 0x4000`), let `E` be the source reward. The
credited actor's talent bit `0x20` doubles `E`; source talent bit `0x40` doubles
it again. Count one player plus each of the two nonnull familiar slots whose
HP is nonzero. The share is `ceil(E / count)`, implemented as
`(E + count - 1) / count`. Each living recipient below the defeated actor's
level receives twice that share. Equal/higher-level recipients receive the
ordinary share. The apparent intermediate bonus tier is unreachable:
[B007](../../BUGS.md#b007--one-xp-bonus-tier-is-unreachable).

A non-party credited actor instead receives the source's original reward;
the earlier party multipliers/share are not used for this branch. Pending
awards occupy the high/low bytes at +0x41/+0x42 and saturate their **sum** at
65535. Party callers narrow each wide award to 16 bits before accumulation,
so a single large award can wrap first:
[B012](../../BUGS.md#exp-reward-overflow). The popup interprets some large
awards as signed values:
[B005](../../BUGS.md#large-exp-reward-crashes). An expired Salamander can
also become its own pending level-up blocker:
[B023](../../BUGS.md#off-screen-salamander-kill-softlock).

## Stat growth for player and familiars

Verified by reading `raise_entity_level`, `lower_entity_level` in
[`can_entity_gain_level.c`](../../../src/dungeon/player/object/can_entity_gain_level.c)
and [`init_monster_from_stats`](../../../src/engine/entity/init_monster_from_stats.c).
Species selects a 24-byte initial-stat record `b` and an eight-byte growth
record `g`. Offset 0/1 is attack/defense, 2 is the agility byte, 3 luck,
4 base MP and 5 base HP. Species zero takes the same growth code; player
spell growth is skipped.

Define nominal curves at `n = level - 1`, for nonnegative normal inputs:

| Stat | Nominal value `F(n)` |
| --- | --- |
| Attack, defense, agility (`j=0,1,2`) | `b[j] + floor(g[j] * b[j] * n / 64)` |
| Luck (`j=3`) | `b[3] + floor(g[3] * b[3] * n / 1024)` |
| Base MP (`j=4`) | `b[4] + floor(g[4] * b[4] * n / 1024)` |
| Base HP (`j=5`) | `b[5] + floor(g[5]*n/16) + trunc(g[5]*SquareRoot12((n*g[5]) << 11)/32768)` |

`SquareRoot12` is retained as the source call, without replacing its fixed-point
rounding with a real-number square root. Raising old level `L` adds
`F(L)-F(L-1)` to the actor's **existing** base stat and caps the result at 255.
It does not replace a modified or evolved actor with the nominal table value.
The actual base-stat gain is also added to current HP/MP/attack/defense bytes.
Lowering subtracts the adjacent curve difference and resets EXP to the new
level's threshold minus one.

Current byte additions can wrap even though base stats are capped. Examples:
[Naplass HP B009](../../BUGS.md#b009--leveling-can-empty-a-full-health-naplasss-hp),
[attack B009A](../../BUGS.md#b009a--attack-byte-wraps-on-level-up),
[defense B009D](../../BUGS.md#b009d--defense-byte-wraps-on-level-up).
Level loss after evolution can underflow inherited stats:
[B013](../../BUGS.md#stat-underflow-after-evolution).
The agility byte's growth does not establish a combat use; see
[the unresolved consumer audit](../../BUGS.md#agility-without-a-known-use).

After a raise, the actor's own EXP **reward** is recomputed separately. Let
`n` be the old level, `B` the signed base reward halfword at initial-stat +6:

```text
reward = B + n*B + trunc(n*n*(B + g[6]*n) / 512)
reward = min(unsigned32(reward), 65535)
```

This is the reward for defeating that actor, not the EXP cost to level it.

## Familiar spell levels and talents

Verified by reading `raise_entity_level` and
[`apply_entity_effects`](../../../src/engine/entity/apply_entity_effects.c).
Three ability triples begin at +8: ID, effective level and stored level.
A nonzero ID grows only if its definition's high-nibble element mask matches
the actor, or that mask has none of the three element bits. If stored level
`a < 99`, the update at old actor level `L` is:

```text
a1 = a + 1
a_new = min(99, a1 + trunc((99 - a1) / (100 - L)))
```

Talents then derive effective values: +0x54 bit 2 doubles max HP, bit 4 doubles
max MP, bit 8 doubles base attack into the effective attack limit, and bit
`0x10` doubles defense into its limit, each capped at 255. Bit `0x80` doubles
effective ability level, capped at 99. The routine derives limits and spell
levels; it does not refill current HP or MP to those limits.

## MP is an 8.8 quantity

Verified by reading
[`spend_actor_mp`](../../../src/dungeon/actor/spend_actor_mp.c),
[`update_actor_status_and_mp`](../../../src/dungeon/actor/state/update_actor_status_and_food.c)
and [`feed_actor_restore_mp`](../../../src/dungeon/actor/feed_actor_restore_mp.c).
The integer MP byte is +0x25, the fraction byte +0x24, and maximum MP +0x66:
`raw_MP = 256 * MP + fraction`. These are actor stats, not sprite coordinates.
`spend_actor_mp` applies only to positive signed species IDs; it excludes the
player. A reduction argument of 256 costs one MP; a reduction of 4 costs
1/64 MP. Pending ordinary actor updates use a base reduction of 4, while
individual action callbacks can charge additional amounts.

The drain order is: no-MP-drain status sets reduction to zero; otherwise
talent bit `0x100` replaces it with `(reduction+1)>>1`; MP-drain status then
doubles the result. Remaining MP floors at zero and is limited against max MP.
Exhaustion logic tests the **integer** MP byte, so a remaining fraction below
one MP still enters the zero-MP branch. A tested mode preserves one MP for
Kewne and species `0x39`; it is not a general exemption for all familiars.

Feeding refuses under anorexia. Otherwise mode 1 adds 3 MP, mode 2 adds
50 MP (10 MP for category-12 Meat), and mode 3 adds 100 MP; mode 0 adds none.
Mode 3 is changed to mode 2 for Pita Fruit and Meat. The result is clamped to
max MP with fraction `0xff` when over that maximum. Exactly 256 MP wraps
before this cap:
[B003](../../BUGS.md#b003--an-exact-256-mp-food-total-wraps-to-zero).
The separate low-MP creature food AI path can consume Meat without restoration:
[DB001/DB007](../../BUGS.md#dungeon-audit-db001-db007).
