# Combat and status

[Mechanics index](README.md) · [Levels and MP](leveling.md) · [Monster decisions](monsters.md)

## Acquiring a target and deciding a hit

Verified by reading
[`prepare_directional_attack`](../../../src/dungeon/effect/screen/change.c)
and `resolve_attack_damage_and_effects` in the same file. A directional attack
first checks the diagonal sides, then searches the requested tile and height
unless the caller supplies a target. A confused actor can randomize its facing
once under the tested per-action flag. A blocked corner or absent target can
stop an attack before any damage roll. The distance-zero Salamander path still
performs the corner check: see [B025](../../BUGS.md#salamander-attacks-that-miss).

With a target, the first threshold is:

```text
v = attacker byte[0x84]
if attacker luck byte[3] != 0:
    v += 4 * ((random() & 0xffff) % luck)
if target is the player with shield subtype 2:
    v -= signed16(v) >> 2
```

The routine leaves its miss flag set and returns early when the target has
none of `flags1C & 0x238` and `signed16(v) < 128`. That mask includes MP empty,
blindness, paralysis and sleep. Passing this check proceeds to attack power
and critical selection. The second, target-luck dodge check runs **only** when
that mask is nonzero: it tests whether the signed sum of target byte[0x70]
and `random16 % target_luck` reaches 128 (zero luck contributes zero).
Otherwise it clears the miss flag. The reviewed bug record identifies the
normally zero evasion byte and the misplaced condition:
[B011, luck dodge and evasion](../../BUGS.md#luck-dodge-and-evasion).
There is no universal accuracy percentage in this function.

## Physical damage

Verified by reading
[`get_clamped_adjusted_value`](../../../src/dungeon/player/get_clamped_adjusted_value.c),
[`clamp_adjusted_value_0_to_99`](../../../src/dungeon/actor/clamp_adjusted_value_to.c),
`prepare_directional_attack` and `resolve_attack_damage_and_effects`.
For a hit, before elements and height:

```text
attack_bonus  = clamp(attacker[0x85] + signed equipped-weapon parameter, 0, 99)
defense_bonus = clamp(target[0x86] + signed equipped-shield parameter, 0, 99)
r = random()
A = 2 * (attacker.current_attack + attack_bonus)
    + (r & 1) + ((r & 2) != 0)
D = target.current_defense + defense_bonus
```

The two random terms use the **same** random result and sum to 0, 1 or 2.
An attack whose linked weapon word is `0x0f0d` omits the shield bonus.
Frog status halves `D` with a signed shift; zero defense is then changed to one.

Element masks are 1 = fire, 2 = water, 4 = wind. The attack mask includes
actor properties and the equipped weapon contribution; the defense mask
includes actor properties and the equipped shield contribution, as implemented
by `get_masked_record_flags` in the same source file.

| Attacking element | Target giving +1 modifier | Target giving -2 modifier | Status that quarters attack instead |
| --- | --- | --- | --- |
| Fire (1) | Wind (4) | Water (2) | `STATUS_WATER_PROTECT` |
| Water (2) | Fire (1) | Wind (4) | `STATUS_WIND_PROTECT` |
| Wind (4) | Water (2) | Fire (1) | `STATUS_FIRE_PROTECT` |

For each attacking bit, its protection branch quarters `A` and skips that
bit's affinity contribution. Contributions from other bits still apply.
The signed height difference is attacker +0x88 minus target +0x88. A difference
at least 32 subtracts one from the modifier; a difference at most -32 adds one.
Thus the source's sign should be preserved when interpreting height.

```text
A += (A * modifier) >> 3
A += (A >> 3) * count_occupied_entity_slots(attacker)
h = trunc((D - A) / 2)
pending_HP_delta = h                         # normal
pending_HP_delta = h + trunc(h / 2)          # critical
if pending_HP_delta >= 0: pending_HP_delta = -1
```

These expressions describe ordinary in-range values; the implementation stores
intermediate attack, defense and HP delta in 16-bit fields. Critical therefore
scales the post-defense delta, with rounding, rather than multiplying the
initial attack by 1.5. Damage guard makes the damage display zero and suppresses
negative HP application in
[`apply_clamped_actor_value_delta`](../../../src/dungeon/actor/apply_clamped_actor_value_delta.c).

The extra eighths are limited by
[`count_occupied_entity_slots`](../../../src/dungeon/actor/object/count_occupied_entity_slots.c):
it only counts for the player and tests the player's talent word for each
occupied familiar slot. It does not successfully implement the familiar's
advertised Strength increased bonus; see
[B010](../../BUGS.md#the-strength-increased-talent).

## Critical rolls and luck

Verified by reading `prepare_directional_attack`. The critical flag is set when:

```text
(random() & 127) <= (luck >> 6)     # ordinary
(random() & 127) <= (luck >> 1)     # anger flag
```

Equality counts, so even a threshold of zero accepts roll zero. A probability
such as `(threshold + 1) / 128` is **inferred**, conditional on uniform low
seven RNG bits; the comparison above is the actual rule. The player turn updater
also rewrites the player's luck byte from the old phase, then increments that
phase. Its expressions are `(rsin(signed16(phase)) >> 7) + 64` normally and
`(rsin(signed16(phase)) >> 8) + 48` while cursed, stored as a byte. Thus an
item's direct luck-byte increase need not persist for the player. Verified by reading
[`update_player_and_actor_turns`](../../../src/dungeon/player/update_player_and_actor_turns.c).

## Spell power and elemental affinity

Verified by reading `apply_attack_power_and_element_effects` in
[`change.c`](../../../src/dungeon/effect/screen/change.c).
The caller supplies base power, bonus and an element mask. A bonus of `0xff`
is replaced by `min(4 * player_level, 99)`. Initial power is
`P = 2 * (base_power + bonus)`; defense is computed as above, including frog
halving and the zero-to-one repair.

The elemental cycle is the same as the physical table, but each unfavorable
pair contributes **-1**, not -2. The corresponding protection quarters `P`
and skips that bit's affinity contribution. Then the C computes:

```text
q = signed16(P * affinity)
adjust = q
if q < 0: adjust = signed16(unsigned32(q + 3) >> 2)
P += adjust
pending_HP_delta = trunc((signed16(D) - P) / 2)
if signed16(pending_HP_delta) >= 0: pending_HP_delta = -1
```

For ordinary values a single favorable pair doubles power; a single unfavorable
pair subtracts about a quarter. The asymmetry is preserved and its possible
intended correction is separately labeled in
[B008](../../BUGS.md#b008--positive-spell-affinity-skips-division-by-four).
Before this calculation, `try_trigger_target_record_effect` can intercept
certain attacks according to element/status/item tests. These formulas do not
cover every special effect's independently supplied damage or HP delta.

## Status slots and IDs

Verified by reading
[`set_or_clear_actor_status_slot` and `advance_status_timers`](../../../src/dungeon/actor/ability_eligibility.c),
[`get_entity_effect_value`](../../../src/engine/entity/get_entity_effect_value.c),
[`apply_entity_action_flags`](../../../src/dungeon/actor/object/apply_entity_action_flags.c)
and [`apply_entity_effects`](../../../src/engine/entity/apply_entity_effects.c).
Actors have four signed-byte ID/value pairs beginning at +0x2c.

- Matching IDs update their value, except a sign change or a new value of zero
  removes the existing slot. Empty-slot insertion scans slots 3 down to 0.
- When full, insertion evicts the smallest existing ID only if that ID is
  greater than the requested ID; otherwise it fails with -1. Success returns
  the slot index, including zero. Sleep and paralysis clear each other when
  inserted into an empty slot.
- Nonzero timer values move one step toward zero on a status tick. At zero
  the slot expires; an initially zero-valued slot has no timer countdown.
  Poison also invokes its damage helper on each tick.
- A matching zero-valued slot reads as `0x100`, preserving a nonzero presence
  result. No matching ordinary slot reads as zero.

The named IDs below come from
[`actor_status_ids.h`](../../../include/shared/actor_status_ids.h);
the header does not assign a public name to every numeric ID used by effects.

| IDs | Named statuses and checked behavior |
| --- | --- |
| 1, 2, 3, 4, 5, 6 | Sleep, confusion, blind, paralysis, poison, magic bind; set corresponding live actor flags |
| 7 | Speed: positive values double the speed scale; negative values halve it |
| 8, 9 | Curse and anger; set live flags, with luck/critical consumers above |
| 10 | Frog; changes actor handling and halves defense in these damage paths |
| 11, 12 | Player side and brainwash; change side and tile-occupancy masks |
| 15 | MP drain; doubles the modified MP reduction |
| 18, 19, 20 | Fire, water, wind protection; use the exact pairing in the affinity table |
| 25, 27 | Anorexia (feeding refusal), no tile occupancy |
| 29, 32 | Damage guard, no MP drain |

Feedback can disagree with slot success: several item and spell handlers test
the returned index as a Boolean. See
[DB003-DB007](../../BUGS.md#dungeon-audit-db001-db007) and
[DB008-DB013](../../BUGS.md#dungeon-spell-feedback-db008-db013).
No single fixed duration or common resistance percentage is established for
all applications; callers supply those values.
