# Town code ownership audit (opus_town_owner, 2026-10-27)

Inputs: the proto3 run-6 binding inventory (154 sites,
`proof_run6/owners_binding_inventory.tsv`), the cover-plan X4 rows (108),
the scene1 loader groups (129 rows), and the live repo at eb24ebdfe
(read-only). Retail bytes come from the repo's pinned `work/disc` containers.
The JP release was flattened into a private scratch directory to act as a
second witness. Nothing was written to the repo or to any lane directory.

## Answer in one paragraph

**Nothing loads the 0x7FD9AC00 group at run time, on the US disc or on the JP disc.**
TOWN `0x78B800-0x795800` is a complete 20-sector stale image. It was built
with gcc 2.6.3 and linked at the devkit address `0x80526400`. It is an
earlier build of the casino/betting/collection-round minigame overlay. The
whole image is byte-identical (SHA-256 `b066efec...`) at JP TOWN `0x765800`,
where it is also unreferenced. The JP live minigame images hold relinked twins
of its functions; the US live images hold rebuilt (2.7.2-cdk) versions.

Its absolute calls target a devkit memory map that matches neither retail
build. For example, its `jal 0x8006A3A4` is `rsin` (proven through the JP
twin), but US `rsin` lives at 0x800644B8, so the call goes somewhere else on
US retail. The code therefore cannot run correctly on US retail from any
loader. So the 60 sites have no runtime owner
to find. They are **dead devkit image**, the same kind as the owner's X1 ruling.

Even so, half of the sites can still get a prototype:
- 10 call into the image itself, so a diagnostic devkit view gives them an owner.
- 20 call library or engine functions whose identity is now proven through the JP release.

Of the ~150 town holds, only 3 are genuine "owner found" ownership fixes. The
largest real lever is registering diagnostic devkit views (30 prototype sites)
plus identity prototypes (23 sites). The total is 59 sites. The coverage effect is mainly on
the denominator: 120 rows become unreachable, and 9 X4/scene rows turn out to
be loaded.

## Classes (154 binding sites; full detail in owners.tsv, item_kind=binding_site)

| Class | Sites | Owner | Unlockable now |
|---|---:|---|---:|
| owner_found | 2 | `append_town_item` placed in both validated scenes 0x581000/0x594800; `point_shared_buffer_at_data_e` in validated scene 0x652800 | 2 |
| owner_found_via_live_placement | 1 | `query_lowered_transform_position` (engine 0x800C2AE8), via live placement image_795384 binding | 1 |
| owner_known_not_ownership | 27 | resident engine / SLUS / validated scenes. These holds are contract conflicts (11), missing resident definitions (13: `func_8004DC14` x6, `func_80049004` x2, ...), a resolver typedef loop (1) and consumer files with no registered row (2) | 0 by ownership |
| duplicate_of_owned_devkit_copy | 7 | TOWN 0x26E000-0x272000 is byte-identical to the MAIN devkit card image at the same offsets and base 0x80400000 (main view `ll34_269000_80400000`, load record 117; X1 ruled unreachable) | 3 (callees inside the MAIN image) |
| nonstandard_loader_unexecutable | 12 | devkit flag-test scenes 0x7F4000-0x804000 (details below) | 4 (intra-image, same link delta) |
| dead_devkit_image:intra_image | 26 | the devkit image itself, same link delta (old_minigame_a 10, devkit_low 16) | 26 |
| dead_devkit_image:identity_via_jp | 23 | devkit address proven to be a US function through the JP twin chain | 23 |
| dead_devkit_image:candidate_identity | 6 | `0x800373DC` -> `allocate_flagged_object_node`: 10-word prefix match only, 23/67 over the body. Not proven | 0 |
| dead_devkit_image:unidentified_slus / _engine / _other_devkit_image | 19 / 16 / 15 | devkit-layout SLUS (0x8003-0x8007xxxx), devkit town engine (0x8023-0x8029xxxx), or a call into another devkit image's window (0x8070/0xA070/kernel area) with no row at the same delta; no identity yet | 0 |

Per-region view of the 125 "no loading image or resident owner" holds, plus the
other 29 holds:

| Region | Sites |
|---|---:|
| old_minigame_a | 74 (the 60, plus 14 `missing_base_and_image`) |
| devkit_low_copies 0x832800-0x846000 | 31 |
| devkit_8070_scenes | 12 |
| card copies | 7 |
| engine / scene holds that are not ownership problems | 27 |
| scene owner fixes | 2 |
| fall_to_ground_height | 1 |

## The 60-site group (delta 0x7FD9AC00): evidence

1. **No loader.** I ran a packed-descriptor census (`ana/desc_census.py`) over
   SLUS, TOWN, MAIN, DUNGEON and OVMOVIE, counting every `(sectors<<23|dest, LBA)`
   pair. Real tables are those in SLUS, in the town engine, or inside a loaded
   TOWN image. They cover the neighbours: 0x747000-0x78A800 (SLUS 0x80080E50, a
   135-sector bank to 0x80175800) and 0x796000 (D_800D4740, 15 sectors to
   0x80020000). Nothing covers 0x78A800-0x796000.
   - The lane's six raw candidates are coincidental words. The 236- and
     220-sector "0x80020000" entries at TOWN 0x863510 are ISO directory records
     (`dummy` entries).
   - A word scan for entry-exact pointers, jal/j targets or hi/lo pairs into
     0x80526400-0x80530400, or its 2 MiB alias 0x80126400, finds no reference
     from loaded code. The 4 alias hits are self-pointers of the 0x8E2800 image.
2. **Link base and toolchain.**
   - Internal j targets and its own data pointers fix the base at 0x80526400:
     `0x78B800` holds the TOTAL/SCORE header and a pointer table at 0x8052xxxx.
   - The header layout is the same as the live minigame image at 0x796000. But
     where the live image points to engine data at `0x800F2B04`, this one points
     to `0x80289030`: an older, larger engine linked high.
   - 63 of 69 rows use the `2.6.3-G0` config; the live images use `2.7.2-cdk`.
3. **Unexecutable on retail** (`ana/devkit_callees.py`, `ana/verify_full.py`).
   - Path: the devkit row, then its masked twin in a JP *loaded* minigame image
     (JP 0x770000/0x777800, loaded by JP D_800D6774/7C), then that call's
     JP-layout target, then the masked match in US SLUS or the US engine.
   - Proven so far: `0x80071494=rand`, `0x80071424=strlen`, `0x8006A3A4=rsin`,
     `0x80058F88=SD_Call`, `0x800374FC=allocate_list_node`,
     `0x8025E01C=query_lowered_transform_position`.
   - In every proven case the identified callee lives at a different US
     address (rand 0x80069EF8, strlen 0x80069E98, rsin 0x800644B8, SD_Call
     0x80053DA8, allocate_list_node 0x8003FD64, query_lowered_transform_position
     0x800C2AE8). The sparse symbol file names nothing at the devkit addresses.
     I did not prove that no US function starts there, because SLUS rows are
     per module. The rand identity also explains `config/void_callees.txt`:
     "37 retail call sites in the 0x8052xxxx TOWN devkit module, none setting
     a0-a3".
4. **The same leftover is on the JP disc.**
   - US 0x78B800-0x795800 equals JP TOWN 0x765800 sector for sector.
   - The JP descriptor scan finds no loader for that copy.
   - JP's real minigame image A (JP 0x770000, to 0x80020000) contains relinked
     masked twins of its first functions.
5. **Twins.** Apart from internal duplicates there are no relocation-masked
   twins in US loaded images. The one exception is `fall_to_ground_height`,
   whose 2.6.3 twins sit inside the live US image A at 0x798C2C and 0x799934,
   already bound 0x8025E01C->0x800C2AE8. So the earlier "byte-identical copy"
   audit (scene1 run13) was right. The relocation-masked search adds only the
   JP chain.

Breakdown of the 60 sites:

| Callee kind | Sites |
|---|---:|
| intra-image (0x8052xxxx; definitions exist in the same image) | 10 |
| identity proven via JP: rand 6, strlen 2, rsin 3, SD_Call 4, allocate_list_node 2, query_lowered_transform_position 3 | 20 |
| allocate_flagged_object_node candidate (unproven) | 2 |
| devkit-SLUS, unidentified | 13 |
| devkit-engine, unidentified | 15 |

## Other groups

- **devkit_low_copies 0x832800-0x846000** (39 X4 rows, 31 sites). Five
  sub-images linked at 0x80700000, 0xA0700000 (KSEG1), 0x80003000 and
  0x80000000 (twice).
  - Under the owner's X1 rule (OWNER_RULINGS_1027.md / unreachable.tsv: a
    devkit link base read through the 21-bit 2 MiB RAM alias):
    - the 0x80000000 and 0x80003000 bases are BIOS kernel RAM on retail;
    - 0x80700000 aliases to 0x80100000, which is inside the resident town
      engine (0x80088760-0x80113800).
  - No descriptor covers these sub-images. Their only references come from
    other devkit images: 0x833604 `j 0x80700E18` targets the 0x7F4000 scene.
  - All 32 non-empty sectors are byte-identical at JP TOWN 0x80D000, which is
    also unreferenced.
  - Verdict: dead devkit image.
- **devkit_8070_scenes 0x7F4000-0x804000** (16 scene1 rows, 12 sites). This is
  a "non-standard loader that cannot work".
  - Real descriptors exist in the town-engine format-A table: `D_800D3C00`
    entries 0x800D3C00-0x800D3C48, e.g. D_800D3C18 loads 4 sectors from
    0x7F4000 to 0x80016000. A SLUS table (0x800812C8-0x800812F0) carries the
    same entries.
  - The code, however, links at 0x80700000+ (rowbase deltas
    0x7FF0C000..0x7FEFD800). Under the X1 alias rule that is inside the
    resident engine.
  - scene1 found no ordinary service-22 caller.
  - opus_devkit1 `retail_flgtst_crash.txt` shows a forced load dying at
    0x801131B8.
  - JP has the same pattern: JP engine 0x573BC loads JP 0x7CE800 to 0x80016000.
- **card copies 0x26E000-0x272000** (3 X4 rows, 7 sites). These are exact
  copies of MAIN rows at the same offsets and the same 0x80400000 base, so they
  belong with X1.
  - 3 sites call functions defined in the MAIN devkit image:
    `init_card_background_object` 0x80404C84, `init_card_slot_object`
    0x804076C8 and `get_table_entry_by_flag` 0x80402268.
  - 4 sites call devkit-SLUS addresses, which stay held.
- **X4 rows that are actually loaded (4).**
  - `noop_hook_b`, `noop_hook_c` and `run_service_callback_0x218_with_record`
    sit in the event subfiles 0x2D2000 (0x2000 bytes) and 0x2D9800
    (0x1000 bytes). Scene 0x2AB800's event tables 0x8001C18C/0x8001C1AC load
    these subfiles into arena 0x8001DCD0, per scene1's `subfile_map.tsv`.
  - So do 5 more scene1-only rows of the same subfiles.
  - `remove_scene_runtime_callback` (0x8EAD44) lies in the 49-sector image
    0x8E2800-0x8FB000. SLUS descriptor 0x80080B9C (LBA 0x1DCA) loads it to
    0x8011AC98, and rowbase `sweep_8EAB10` captured that load at run time. It
    has no ledger load record yet.
- **One-sector images 0x8CD000-0x8D3000** (144 rows; not X4, outside the hold
  set apart from one placement). No packed descriptor references them in US or
  JP (every LBA hit lies in sound data), and they are byte-identical in JP at
  0x8A7800. Treat them as an **X6 candidate for the coverage plan**; this needs
  its own check before any ruling.

## Whole-TOWN loader census, 0x71A000-0x8FB000 (ana/out/census_gaps.tsv)

Only three uncovered blocks contain code:

| Uncovered block | Rows | Contents |
|---|---:|---|
| 0x78A800-0x796000 | 64 | old_minigame_a |
| 0x82D800-0x868000 | 98 | devkit_low_copies |
| 0x87C000-0x8D3000 | 150 | one-sector images |

Everything else either has a loader (SLUS tables 0x80080B9C.., 0x80080E50..,
0x800812C8..; engine tables D_800D3C00.., D_800D4740/48/50; descriptors inside
validated scenes) or is data/padding.

## Recommended actions, ranked by unlock (all with the proper tools; never hand-edit link_graph shards)

1. **Devkit view for old_minigame_a.**
   - Append an `instance_load_regions` record, following MAIN record 117:
     - container town, foff 0x78B800, size 0xA000, base 0x80526400, delta 0x7FD9AC00;
     - method `internal link-evidence; documented devkit-linked image`;
     - placement_kind `linked base only; retail load/execution not established`;
     - evidence: a receipt built from this report.
   - Then create one link-list view `town/ll34_78b800_80526400` with the
     link-list producer. Limit it to 0x78B800-0x795384: 0x795384 onward
     already belongs to `town/image_795384` (delta 0x7F88A000). The load record
     can still describe 20 sectors.
   - Precondition: eight rows in the band have no proven rowbase delta
     (0x794CC4-0x7951F8 and 0x795294). `load_rowbase.py` condition L3 refuses
     until they are bracketed or proven, as r121_nodonor did for 0x78E594.
   - The view absorbs the two single-row diagnostic views
     `r124w7_home_func_8080e534` and `r124w7_home_func_808105ec` (use
     `tools/tu/view_merge.py plan/apply`).
   - Regenerate with `tools/link/graph.py`.
   - Unlocks 10 of the 60 (intra-image) and gives the remaining 50 an image,
     so their hold reason becomes "devkit-layout callee" rather than "no owner".
2. **Identity prototypes** (23 sites; 20 in the 60).
   - Keep the numeric symbol, because the call must still link to the devkit
     address.
   - Do not add a link-list `bindings` entry: that would relocate the call.
   - Give the declaration the US function's prototype (rand/strlen/rsin/SD_Call,
     allocate_list_node, query_lowered_transform_position) under a new
     documented-identity evidence record that cites `ana/out/devkit_callee_map.tsv`
     and the verify_full result.
   - The prototype resolver needs this as an accepted evidence class, like
     documented_varying_arguments.
3. **Devkit views for devkit_low_copies** (16 intra sites). There are five
   sub-images:

   | foff | base | delta |
   |---|---|---|
   | 0x832800 | 0x80700000 | 0x7FECD800 |
   | 0x837800 | 0x80003000 | 0x7F7CB800 |
   | 0x839000 | 0xA0700000 | 0x9FEC7000 |
   | 0x83A800 | 0x80000000 | 0x7F7C5800 |
   | 0x844000 | 0x80000000 | 0x7F7BC000 |

   Many single-row ll34 views already exist there, so merge them with
   view_merge. These views must not be visible to the 0x7F4000 scene views
   that share the 0x8070 window. Use per-view resolution only.
4. **Devkit views for devkit_8070_scenes** (4 intra sites). The scene views
   exist piecemeal (`ll34_7f4d54_80700d54`, ...). Merge them into per-scene
   views at the link base. The descriptor dest 0x80016000 must not be used as
   the base.
5. **Card copies** (3 sites). Run `tools/tu/copy_place.py derive` on
   town/func_802EE3A0, func_802F13A0 and func_802F161C against their
   main/func_8001E3A0... homes (they are exact). The TOWN rows become
   placements of the MAIN homes, and the declarations take the MAIN
   prototypes.
6. **Owner-found fixes** (3 sites).
   - Add a placement of town/func_806D2898 (0x652898, vma 0x80016098) to
     `town/ll34_652800_80016000`.
   - Declare `append_town_item` for `cache_scaled_service_result_g00738.c`. It
     is the same lshop_g00008 TU in both images; the resolver needs a tool fix
     to accept same-home equivalence.
   - Declare `query_lowered_transform_position` in `fall_to_ground_height.c`.
7. **Load records for real loads that are missing from the ledger** (coverage
   attribution):

   | Load | Destination | Descriptor |
   |---|---|---|
   | 0x796000 | 0x80020000 | D_800D4740 |
   | 0x79D800 | 0x80020000 | D_800D4750 |
   | 0x8D3000 | 0x80020000 | D_800D4748 |
   | 0x8E2800, 49 sectors | 0x8011AC98 | SLUS 0x80080B9C |
   | 0x8DE000, 9 sectors | 0x80020000 | SLUS 0x80080BAC |
   | event subfiles 0x2D2000 and 0x2D9800 | 0x8001DCD0 | scene event tables |

   Then add `remove_scene_runtime_callback` to `town/ll3a_8eab10_8ee4c4`.

**Estimated unlock:** 59 prototype sites (owner fixes 2 + live placement 1 +
card 3 + flag-test scenes 4 + intra-image 26 + identity 23).

**Coverage, as denominator rulings to put to the owner:**
- UNREACHABLE: X4 old_minigame_a 62 + devkit_low 39 = 101.
- X1 extension: card 3.
- devkit flag-test scenes: 16 (scene1).
- Possible X6: one-sector images 144.

**Newly attributable reachable rows:** 9 (8 script-subfile rows + 1 streamer row).
X4 then reduces to 0 rows awaiting a census.

## Caveats

- The "unexecutable" argument is static. I did not run a retail trace beyond
  citing opus_devkit1's crash for the flag-test scene.
- The JP identities use a 10-word masked prefix plus a full-body check. SD_Call
  is only 9 words long, so it is medium confidence.
- The 50 unidentified devkit callees could be mapped further by aligning each
  devkit row with its JP live sibling call by call. I did not do that.
- The `candidate_identity` rows must stay held.
- The JP containers were extracted to a private scratch directory and are not
  kept here. Run `ana/jp_user.py` against `a user-owned JP disc` to
  reproduce them.
