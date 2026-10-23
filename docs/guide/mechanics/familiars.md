# Familiars: eggs, fusion and evolution

[Mechanics index](README.md) · [Levels and MP](leveling.md) · [Items](items.md)

## Finding eggs and heating them

Verified by reading
[`init_random_floor_item_parameters`, `populate_floor_item_records`](../../../src/dungeon/level/spawn.c)
and [`advance_item_interaction_and_save_creature`](../../../src/dungeon/effect/advance_item_interaction_and_save_creature.c).
Eggs are kind `0x12`; carried familiar entries are kind `0x13`.
Ordinary newly parameterized floor eggs start with byte[2] in 60..99,
computed as `(random16 % 40) + 60`. A pending egg override samples one of
32 entries in `floor_species_pool`; repeated species entries therefore matter.
The ordinary item selector is described in [Items](items.md#floor-rarity).

Each accepted heating input subtracts `(random() & 3) + 1` from the egg's
signed byte[2]. At zero or below it is set to zero and the sequence proceeds
to hatching; cancel returns control after clearing its temporary held record.
The remaining count belongs to the egg entry, so this is a count of heat
inputs, not an elapsed real-time timer. The popup uses `100 - signed byte[2]`.
Camera rotation and cancel can expose
[B022, moonwalking after heating](../../BUGS.md#moonwalking-after-egg-heating).

The hatching callback loads the egg's species resource, initializes the actor,
sets its EXP to `level_experience_table[player_level]`, and repeatedly calls
`raise_entity_level` while EXP reaches the following threshold. It then fills
HP and current attack/defense from their effective limits. It changes the
inventory entry to kind `0x13`, assigns a free familiar slot, copies a
0x8c-byte actor snapshot into familiar storage and retires the temporary
hatched actor. **Inferred:** using the same level-indexed initial-EXP table
as floor spawning is how this path targets the player's current level.
The exact assignments and loop, rather than a separate hard-coded hatch
level, are what this callback establishes.

Egg feeding is a separate action:
[`feed_egg_to_monster`](../../../src/dungeon/item/feed_egg_to_monster.c)
selects the species preference from bits 2..3 of `entity_action_selectors`
and calls the MP feeding helper. It does not hatch an egg inside the target.

## Deployment and storage

Verified by reading
[`begin_familiar_summoning`](../../../src/dungeon/player/begin_familiar_summoning.c),
[`update_familiar_summoning`](../../../src/dungeon/player/update_familiar_summoning.c)
and [`store_recalled_familiar`](../../../src/dungeon/player/store_recalled_familiar.c).
Summoning searches nearby valid placement tiles, loads the selected species,
spawns the actor and restores its saved record. If carrying another creature,
the initializer probes a second placement using a temporary reservation.
Recall restores the saved species when transformed, copies the 0x8c-byte
state into its familiar slot and clears deployment links/occupancy.
The player has two active familiar pointers; their presence and HP also
control [EXP sharing](leveling.md#exp-rewards-and-sharing).

Lifted familiars share the player's tile, which makes occupancy bookkeeping
significant. Known recall, frog reversion, lifting, egg reversion and release
exceptions are collected under
[B015 and related entries](../../BUGS.md#lifted-familiar-clears-the-player-tile).

## Choosing the fusion body and element

Verified by reading
[`select_object_by_flags_and_keys`](../../../src/dungeon/actor/object/select_object_by_flags_and_keys.c)
and [`merge_creature_abilities_and_state`](../../../src/dungeon/actor/state/merge_creature_abilities_and_state.c).
Fusion chooses one existing participant as the result body, optionally copying
it into a supplied destination for a preview. It does not generally average
the participants' levels or all their stats.

The selection rules, in source order, use the talent/state word at +0x54:

1. If both participants have bit `0x800000`, selection fails.
2. The first participant wins if it has bit `0x800000`, or if the second has
   bit `0x400000`.
3. Otherwise the second wins if it has bit `0x800000`, or the first has bit
   `0x400000`.
4. Otherwise higher level wins; at equal level, higher accumulated EXP wins.
   Exact ties select the first on odd `turn_counter`, the second on even.

The body choice and element choice are separate. For ordinary single-element
masks, equal elements stay equal; fire + water becomes water, water + wind
becomes wind, and wind + fire becomes fire. The exact multi-bit case follows
the ordered bit tests in `select_object_by_flags_and_keys`; the simple cycle
should not be extended to arbitrary combined masks.

[`fix_monster_fusion_appearance`](../../../src/dungeon/item/fix_monster_fusion_appearance.c)
stores an item in the actor's +0x48 group and sets bit `0x800000`, subject to
species, existing-item and feeding checks. Frog species can bypass the usual
species restriction: [B026H](../../BUGS.md#fusion-while-frogged).
The selection rules above specify the bits directly rather than assigning an
unverified native flag to every species.

## Inheriting spells and talents

Verified by reading `merge_creature_abilities_and_state`,
[`find_matching_initial_stat_slot`](../../../src/dungeon/actor/find_matching_initial_stat_slot.c)
and [`apply_entity_effects`](../../../src/engine/entity/apply_entity_effects.c).
Spell IDs are grouped by `(id - 1) / 3`. Fusion first considers the survivor's
initial-stat spell group, then the donor's, matching by group and keeping the
higher stored level when both have that group. It then alternates survivor
and donor slots in slot order, skipping groups already visited, until the
limit is reached. The ordinary limit is two abilities; an occupied third
ability slot on either participant raises it to three.

In the later fill pass, ID `0x2e` is cleared. If no ability was selected, a
species-indexed default is installed at level 1. Chosen spell IDs are converted
within their groups to the result's element where their definition does not
match it. Effective spell levels are then recomputed by `apply_entity_effects`.
This is a prioritized merge, not random selection from all parental spells.

Talents use a different rule. Let `M[s] = D_8006D6D8[s]`, the species' native
talent mask, and `F` the actor's +0x54 word:

```text
result.F = (survivor.F & M[survivor.species])
         | (donor.F    & M[donor.species])
```

Thus only the current species' masked talents from each parent survive this
operation; it is not an unrestricted union of all historical inherited bits.
Frogged participants use frog masks despite retaining saved talents:
[B021](../../BUGS.md#b021--frog-species-masks-erase-native-fusion-talents).
Native masks are external data; a complete species-to-talent catalog is not
derived here.

After deriving limits, MP is combined as implemented:

```text
raw = ((survivor.raw_MP + donor.raw_MP) & 0xffff) >> 1
integer_MP = min(raw >> 8, result.max_mp)
fraction_MP = 0xff
```

The pre-average narrowing is
[B002](../../BUGS.md#b002--fusion-truncates-the-mp-sum-before-averaging).
The final fraction is forced to `0xff`, so this is not a precise arithmetic
mean even below the overflow boundary. Live fusion removes the donor and
updates familiar/resource ownership; a supplied preview destination skips
that live removal. Frogged donor cleanup can leak its native resource slot:
[B026](../../BUGS.md#fusion-while-frogged).

## Evolution after leveling

Verified by reading
[`process_selected_actor_record`](../../../src/dungeon/actor/process_selected_actor_record.c),
[`Kid's level-up caller`](../../../src/dungeon/monster/kid/update_dungeon_actor_state.c),
[`advance_actor_replacement_sequence`](../../../src/dungeon/monster/kid/advance_actor_replacement_sequence.c)
and [`advance_staged_entity_load`](../../../src/dungeon/actor/entity_spawn_load.c).
After a level gain, the processor reports evolution eligibility when all these
tests pass:

- The actor belongs to the party and lacks appearance-fix bit `0x800000`.
- Its species record has flag `0x80`, its species ID is at least 2, and its
  new level is at least 20.
- It is not MP empty, paralyzed or asleep and has no status ID `0x18`.

The Kid controller uses the result to start the replacement sequence; the
[Arachne controller](../../../src/dungeon/monster/arachne/arachne.c) does too.
The loader's evolving branch selects `species - 1`, loads/spawns the new form,
updates the familiar registry and calls `copy_entity_record` to preserve stats,
EXP, spells and other state. Its separate already-party branch handles a
different state transfer; callers and flags matter when interpreting it.
The shared [species IDs](../../../include/shared/monster_ids.h) identify, for
example, Kid (4) → Dragon (3), Arachne (12) → Ashra (11), and Nyuel (14) →
Battnel (13). **Inferred scope:** the decrement describes the generic conversion
for flagged species, not proof that every adjacent pair can evolve; each pair
also needs its native flag and controller binding verified.

Inherited stats persist across the form change, so lowering levels afterward
subtracts the new species' growth from old stats. See
[B013](../../BUGS.md#stat-underflow-after-evolution).
[`apply_monster_egg_reversion_item`](../../../src/dungeon/item/apply_monster_egg_reversion_item.c)
is a separate conversion: eligible IDs 3..45 become eggs, with listed evolved
IDs incremented to their unevolved species and a new heat count of 10..25.
