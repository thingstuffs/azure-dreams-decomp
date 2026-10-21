# Original Azure Dreams bugs and their causes

Most bugs here were found by players and documented in the [adrando randomizer guide](https://adrando.com/guide/bugs.html); this page maps each one to the code that causes it. Credit belongs to the Azure Dreams community. The guide uses bullet entries; the labels below identify them.

The retail logic is preserved. These are static code checks; no emulator replay is claimed.

## Community bugs

### Spawning monsters past level 99

[adrando entry: Spawning monsters past level 99](https://adrando.com/guide/bugs.html).

- **B016**: Egg bombing at the capped level 99 leaves a leveling loop running forever. The same uncapped-loop pattern exists in floor spawn/restore. Source: [advance_egg_bomb_sequence](../src/dungeon/effect/advance_egg_bomb_sequence.c#L164).
- **B016S**: On second-tower floor 99, the uncapped spawn groups can request level 100. The game loops forever after the monster reaches level 99. Source: [spawn_floor_monster_from_table](../src/dungeon/item/spawn_floor_monster_from_table.c#L139).

The egg-bomb formula can already reach the problematic capped index at Koh level 49. The guide describes 50+. Both ordinary second-tower floor-99 spawning and egg bombing share the uncapped leveling loop.

### Large EXP reward crashes

[adrando entry: Large EXP reward crashes](https://adrando.com/guide/bugs.html).

- **B005**: Awards of 32768..65535 take an invalid message-pointer lookup; this is the community EXP crash / MISS!! text bug (targets 2 and 21). Source: [create_actor_value_popup](../src/dungeon/effect/create_actor_value_popup.c#L129).

The signed C branch begins at 32,768; the guide’s reported crash range starts at 32,767. The exact crash/text cutoff is a player report, not an emulator observation made for this page.

### Mazarr and an exhausted U-Boat

[adrando entry: Mazarr and an exhausted U-Boat](https://adrando.com/guide/bugs.html).

- **B017**: Feeding a Mazarr seed to an exhausted U-Boat restores 3 MP and queues a level-up, but its exhausted-state handler then waits on its own pending EXP owner. Source: [advance_actor_action_animation](../src/dungeon/monster/u_boat/advance_actor_action_animation.c#L76).

### Off-screen Salamander kill softlock

[adrando entry: Off-screen Salamander kill softlock](https://adrando.com/guide/bugs.html).

- **B023**: A final-action off-screen Salamander kill worth at least 8 EXP can block its removal forever by making it the pending level-up actor. Source: [can_entity_gain_level](../src/dungeon/player/object/can_entity_gain_level.c#L26).

A sufficient code path needs the Salamander’s last action and at least 8 EXP from its kill. The expired actor becomes the pending level-up owner while its removal waits for that owner to clear. The watchdog leaves its EXP intact and the cycle repeats.

### Oleem and an item-form Manoeva

[adrando entry: Oleem and an item-form Manoeva](https://adrando.com/guide/bugs.html).

- **B024**: Oleem on an item-form Manoeva starts two completions against one pending action, leaving -1 until the watchdog resets it. Source: [transfer_linked_object_state](../src/dungeon/monster/manoeva/linked_entity_state_g00259.c#L56).

The Oleem route reserves one completion, but the pentagram and the returning Manoeva each consume one. The signed action counter reaches −1 until the watchdog clears it after 901 unchanged updates.

### Golem idle animation and Select

[adrando entry: Golem idle animation and Select](https://adrando.com/guide/bugs.html).

The community report is credited here, but its complete cause still needs verification.

### The Strength increased talent

[adrando entry: The Strength increased talent](https://adrando.com/guide/bugs.html).

- **B010**: Collared Ashra/Arachne's Strength increased talent gives Koh none of its intended one-eighth attack bonus. Source: [count_occupied_entity_slots](../src/dungeon/actor/object/count_occupied_entity_slots.c#L33).

### Salamander attacks that miss

[adrando entry: Salamander attacks that miss](https://adrando.com/guide/bugs.html).

- **B025**: A diagonally facing Salamander can waste an attack on a monster sharing its tile when either flanking side has blocking terrain. Source: [prepare_directional_attack](../src/dungeon/effect/screen/change.c#L691).

The Salamander attacks a monster sharing its tile with distance zero. When facing diagonally beside a mapped wall above height 0x200, the attack helper can reject the corner and clear the target; the attack still spends an action.

### Gaia Shoot uses water

[adrando entry: Gaia Shoot uses water](https://adrando.com/guide/bugs.html).

- **B018**: DeoRock's Gaia Shoot passes water damage flags (0xA) instead of wind (0xC), changing affinity and the impact effect. Source: [update_warp_camera_and_effects](../src/dungeon/effect/travel/warp.c#L1052).

### Barong item rarity

[adrando entry: Barong item rarity](https://adrando.com/guide/bugs.html).

- **B001**: Barong accepts the first otherwise eligible replacement regardless of the thrown item's rarity. Source: [select_random_replacement_item](../src/dungeon/monster/barong/select_random_replacement_item.c#L64).

### EXP reward overflow

[adrando entry: EXP reward overflow](https://adrando.com/guide/bugs.html).

- **B012**: An 81590 EXP award becomes 16054 before accumulation; exactly 65536 would become zero. Source: [distribute_experience_awards](../src/dungeon/player/object/can_entity_gain_level.c#L1061), [distribute_experience_awards](../src/dungeon/player/object/can_entity_gain_level.c#L1087).

### Stat underflow after evolution

[adrando entry: Stat underflow after evolution](https://adrando.com/guide/bugs.html).

- **B013**: A level-20 Nyuel evolved into Battnel, then lowered to level 7, can turn 1 attack into 255. Source: [lower_entity_level](../src/dungeon/player/object/can_entity_gain_level.c#L478).

### Manoeva/Picket item duplication

[adrando entry: Manoeva/Picket item duplication](https://adrando.com/guide/bugs.html).

The community report is credited here, but its complete cause still needs verification.

### De-curse leaves the curse effect

[adrando entry: De-curse leaves the curse effect](https://adrando.com/guide/bugs.html).

- **B014**: De-curse removes the Cursed slot and item flag but can leave Koh's reduced-luck effect active after cursed equipment. Source: [use_item_to_clear_equipment_flags](../src/dungeon/item/use_item_to_clear_equipment_flags.c#L61).

### Lifted familiar clears the player tile

[adrando entry: Lifted familiar clears the player tile](https://adrando.com/guide/bugs.html).

- **B015**: Recalling a lifted familiar clears Koh's occupied tile, allowing another actor to enter it. Source: [store_recalled_familiar](../src/dungeon/player/store_recalled_familiar.c#L108).
- **B015F**: When a lifted familiar stops being a frog, reattaching the replacement clears Koh's tile occupancy after its constructor set it. Source: [end_status_effect_message](../src/engine/message/end_status_effect_message.c#L173).
- **B015T**: Feeding Tumna to an already lifted familiar restarts lift setup on Koh's shared tile, clearing Koh's occupancy. Source: [update_actor_facing_animation](../src/dungeon/actor/movement_path_g00371.c#L238).
- **B015E**: Feeding Roche to a lifted familiar turns it into an egg and clears occupancy at Koh's tile. Source: [apply_monster_egg_reversion_item](../src/dungeon/item/apply_monster_egg_reversion_item.c#L154).

Recall, Tumna, Roche and frog-expiry routes are mapped. The separate Free command still needs its full removal path checked.

### Luck dodge and evasion

[adrando entry: Luck dodge and evasion](https://adrando.com/guide/bugs.html).

- **B011**: The luck-based dodge roll runs only for incapacitated targets; its zero evasion byte and ordinary luck cannot reach the 128 threshold. Source: [prepare_directional_attack](../src/dungeon/effect/screen/change.c#L768).

### Fusion while frogged

[adrando entry: Fusion while frogged](https://adrando.com/guide/bugs.html).

- **B026**: Fusing a frogged donor leaks its native familiar resource slot; a different third species cannot be deployed while both slots stay occupied. Source: [merge_creature_abilities_and_state](../src/dungeon/actor/state/merge_creature_abilities_and_state.c#L603).
- **B026H**: A frogged Hikewne can accept Ovum and survive a fusion that normally absorbs it. Source: [fix_monster_fusion_appearance](../src/dungeon/item/fix_monster_fusion_appearance.c#L76).

The verified parts are Hikewne survival through the frog/Ovum restriction bypass and a leaked native sprite slot that blocks another species from being deployed. Recalling the survivor restores its own species. The additional report of a different monster receiving a parent’s appearance still needs a complete sprite-resource trace.

### Items and traps on regenerated floors

[adrando entry: Items and traps on regenerated floors](https://adrando.com/guide/bugs.html).

- **B019**: A special room can leave its items/traps on terrain that was regenerated into walls, corridors or void. Source: [update_region_until_complete](../src/dungeon/level/generate.c#L2488).

### Special encounter and item records overwritten

[adrando entry: Special encounter and item records overwritten](https://adrando.com/guide/bugs.html).

- **B020**: A trap room on floor 31 can replace the reserved Beldo vision in slot 0 with a trap, preventing that vision from spawning. Source: [place_room_trap_records](../src/dungeon/level/generate.c#L2613).

The Beldo vision and trap-room collision is mapped. The blue-collar/healing-herb variants still need generation/population ordering checked.

### Invisible Salamander particles

[adrando entry: Invisible Salamander particles](https://adrando.com/guide/bugs.html).

- **B027**: The Salamander particle command is only 1x1 world units at unit scale, making the intended rising particles too small at combat camera distances. Source: [spawn_salam_particles](../src/dungeon/actor/spawn_salam_particles.c#L78).

The sprite command has width and height 1. At unit scale the perspective renderer uses these as world-space spans, so the geometry can disappear at camera distance. The exact camera/GTE packet bounds needed to prove zero area in every case have not been established here; no off-viewport position is asserted.

### Large EXP reward text glitches

[adrando entry: Large EXP reward text glitches](https://adrando.com/guide/bugs.html).

- **B005**: Awards of 32768..65535 take an invalid message-pointer lookup; this is the community EXP crash / MISS!! text bug (targets 2 and 21). Source: [create_actor_value_popup](../src/dungeon/effect/create_actor_value_popup.c#L129).

### Moonwalking after egg heating

[adrando entry: Moonwalking after egg heating](https://adrando.com/guide/bugs.html).

- **B022**: Rotating the camera while heating an egg, canceling, then walking in the same mirrored view direction leaves Koh facing backward while moving. Source: [update_player_and_actor_turns](../src/dungeon/player/update_player_and_actor_turns.c#L519).

### Agility without a known use

[adrando entry: Agility without a known use](https://adrando.com/guide/bugs.html).

The community report is credited here, but its complete cause still needs verification.

## Other bugs seen while reading the code

These entries are **not on the adrando list (may be known elsewhere)**. “Likely” marks an inferred intended behavior.

### B002 — fusion truncates the MP sum before averaging

Fusion loses 128 MP from the average when the two fixed-point MP values sum to at least 256 MP; two full 128-MP creatures can produce a zero-MP result.

Source: [merge_creature_abilities_and_state](../src/dungeon/actor/state/merge_creature_abilities_and_state.c#L566).

### B003 — an exact 256-MP food total wraps to zero

Food that brings the fixed-point MP total to exactly 256 MP empties MP instead of filling it to the creature's limit.

Source: [feed_actor_restore_mp](../src/dungeon/actor/feed_actor_restore_mp.c#L93).

### B004 — cumulative boundaries lose floor items

A random roll on a category's cumulative endpoint selects that exhausted category, then returns category/item zero instead of an item from the next category.

Source: [select_weighted_floor_item](../src/dungeon/level/spawn.c#L386).

### B006 — numeric popup prefixes are overwritten

Numeric format-0x50 popups from attack/defense reductions lose their stat glyph; format 0x30 likewise loses its plus sign.

Source: [create_actor_value_popup](../src/dungeon/effect/create_actor_value_popup.c#L148).

### B007 — one XP bonus tier is unreachable

**Likely.** Every recipient below the defeated creature's level gets double the party share, including a one-level gap; the apparent 50-percent bonus tier never occurs.

Source: [distribute_experience_awards](../src/dungeon/player/object/can_entity_gain_level.c#L1051), [distribute_experience_awards](../src/dungeon/player/object/can_entity_gain_level.c#L1078).

### B008 — positive spell affinity skips division by four

**Likely.** A single favorable elemental affinity doubles spell power before defense, while a single unfavorable affinity reduces power by about one quarter.

Source: [apply_attack_power_and_element_effects](../src/dungeon/effect/screen/change.c#L1017).

### B009 — leveling can empty a full-health Naplass's HP

A full-health Naplass can lose all HP on leveling from 53 to 54: its doubled maximum is already 255, and the one-point growth wraps current HP to zero.

Source: [raise_entity_level](../src/dungeon/player/object/can_entity_gain_level.c#L156).

### B009A — attack byte wraps on level-up

An Arachne kept unevolved with Leva can lose all attack at level 74 to 75; a naturally evolved Ashra can fall to 1 at 68 to 69.

Source: [raise_entity_level](../src/dungeon/player/object/can_entity_gain_level.c#L220).

### B009D — defense byte wraps on level-up

A naturally evolved Metal can drop from 255 defense to 1 on leveling 53 to 54.

Source: [raise_entity_level](../src/dungeon/player/object/can_entity_gain_level.c#L258).

### B021 — frog species masks erase native fusion talents

Fusing two frogged familiars masks both saved talent words with the frog's zero native-talent mask. An Arachne can permanently lose its doubled-attack talent after reverting.

Source: [merge_creature_abilities_and_state](../src/dungeon/actor/state/merge_creature_abilities_and_state.c#L554).

