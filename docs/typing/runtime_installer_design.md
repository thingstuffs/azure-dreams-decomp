# Discovering callback installers in native recordings

Inspected port revision: `2f22998`, in a private clone. This is a design; no port source or executable changed.

The recorder already retains the storing site's native PC for instrumented four-byte writes. The first step is
to expose and audit that evidence, then instrument the missing write paths. Adding another generic slot trace
would duplicate H8.

## Existing evidence

In `port/rtti/rtti.c`, `ACCESS_HOOK` passes `__builtin_return_address(0)` to `observe_access`. Before a four-byte
store, `observe_access` saves that PC, the destination class/kind and its real offset in `pv_*`. `settle_store`
reads the value after the store and calls `val_add` with the saved PC, rather than the next observer's PC.
`ValCell` and the raw `V` record include PC, destination identity/offset, store/load direction, value identity and
count. Code pointers resolve through the function registry and load-map notes into entry-pad identities.

`port/tools/rtti_merge.py:value_facts` symbolizes that PC to file/function/line and writes it to
`pointees.tsv.gz`; `access=store,value_class=func` already describes a named installer where the original write
was instrumented and symbolized. The exported table drops the raw native PC. The raw PC is the instrumentation
call's return address, not an assertion about the exact machine-store instruction.

The current aggregate cannot distinguish allocation generations, when an install happened, its previous target,
or its scenario/checkpoint. It only observes writes through game access hooks. A callback copied in uninstrumented
port/library code, loaded with an image or restored with a snapshot can later appear in slot loads without an H8
store. Unresolved or stripped debug information can also hide an installer that was recorded.

## First deliverable: audit existing stores

Extend the merger to export `callback_installs.tsv.gz` from existing H8 store rows. Keep:

- executable fingerprint and recording source revision;
- raw instrumentation return PC and a clearly identified symbolization PC;
- installer defining file, function and native function-relative offset;
- destination class, merged kind/global/container identity and exact byte offset;
- installed callback defining file/function, raw value and count;
- symbolization status and origin (`instrumented_store`).

Keep per-file function identities, including same-name overlay functions. Resolve PCs with the exact executable
and its debug data; use a documented return-address adjustment for line lookup and retain the unadjusted value.
Do not substitute the installed callback's PC, the slot's address or the next hook's PC for the installer PC.
Group missing callback targets into: recorded store, unsymbolized store, load-only, unresolved code value and
never-observed target. Reuse frozen raw recordings for this audit before collecting another campaign. This
establishes which of the data-installed handlers actually need recorder work.

## Recorder extension for remaining gaps

Add an opt-in `AZ_RTTI_INSTALLERS=1` record family, independently versioned. On a completed code-pointer store,
record the original hook PC, destination address, allocation id/generation as well as kind and offset, old and new
callback identities, a monotonic install sequence, frame or control-boundary index, and a small bounded caller
context. Include scenario/run id, snapshot id and natural/forced origin in the run metadata. Do not encode these
as guessed source types. Retain a few representative events per aggregate key plus explicit dropped/overflow
counters, so a high-frequency callback assignment does not create an unbounded log.

Capture the old word before the store and the new word at settlement. Flush pending writes before freeing or
retagging a destination allocation, before snapshot/load-map transitions and at shutdown. Preserve the original
allocation generation and PC in pending state, even if settlement is triggered by another observer. Guard
reentrancy and thread ownership as the current hooks do. Unknown PCs and failed symbolization remain explicit.

For load-only targets, cover the real writer:

1. Wrap game-facing block-copy helpers, including the `func_80069ED8` port override, and relevant memcpy/memmove
   and image-loader boundaries. After the copy, inspect aligned destination words whose values resolve to code
   entries. Record the calling game's PC as `bulk_copy`, source address/container offset, length and destination
   allocation generation. Bound scanning and report truncation. A helper's PC alone does not identify a scenario.
2. Treat snapshot restore and image/data loading as `snapshot_restore` or `image_load`, with their source image
   and offset. Do not attribute those writes to an arbitrary last game caller. A snapshot's present callback is
   evidence of state, not evidence of the original installer.
3. If those paths still miss a live write, add a narrowly scoped post-store hook in generated game code or a
   watched-slot hook for the unresolved callback family. The hook should receive site, address and value
   explicitly. Reserve page trapping for diagnosis: it has different overhead and ordering semantics.

At the merge boundary, preserve raw provenance and event samples in a separate installers table while retaining
old H8 compatibility. Same-executable recordings can add installer metadata without changing the existing type
vote model. A new recorder executable cannot be silently merged into the frozen campaign; use a separate merge
and compare target/installer identities across campaigns.

## Turning an installer into a capture route

For each target handler, join target identity to store events, installer entry/call edges and the checkpoint/frame
of a sample. Distinguish an object-local action assignment from a table load and from a bulk record copy. The
result names the source person/map or action transition to reproduce with ordinary controls. Store count alone
cannot establish reachability or a valid game situation. Execute a route only after its preconditions are known;
keep any forced diagnostic run separate from natural evidence.

## Acceptance checks

Use a tiny instrumented fixture before a game capture. Two stores from different functions into the same slot
must retain two installer PCs; two same-name functions in different files must remain distinct. Check consecutive
stores, overwrite with null, a final store immediately before shutdown, an indirect callback that never executes,
allocation reuse at the same address, heap and static table destinations, bulk copies, snapshot restores, and an
unsymbolized site. Verify that a deferred store retains its own PC and generation when the next hook belongs to
a different function. Existing H8/H9 outputs must remain unchanged with installer mode disabled.

Then replay one known naturally installed callback and one current load-only family. Success is a reproducible
installer/situation for the latter, with exact provenance, explicit losses, no forced evidence mixed into natural
votes, and measured capture overhead. More broad capture is held until this audit identifies a concrete route.
