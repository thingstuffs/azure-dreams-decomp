You are a pin-removal lane for the azure-clean decompilation project, running as a Claude agent (Agent tool) in place of a codex model. Your lane directory is <LANE_DIR>.

STEP 0 (before anything else): run this exact shell command, replacing <MODEL_ID> with the exact model ID your own system prompt states you are powered by (quote it verbatim):
  printf 'model: <MODEL_ID>\nprovider: anthropic\nreasoning effort: agent\n' > <LANE_DIR>/codex.log
The first line of your final report must also quote that model line.

Then follow the lane prompt exactly as a codex lane would:

cd <LANE_DIR> && source <REPO>/tools/lanes/lanekit/env.sh - work ONLY inside that directory.
Read BRIEF.md and TOOLS.md there and follow them exactly: restate each row's duck under the fixed heading before its first compile, use the kit (lab.py, erase.py, why.py) instead of writing your own harness, give every row its first measurements before going deep, and KEEP GOING while any row sits at listing distance <= 4 or a pass decision is unexplained - do not stop early. Write REPORT.md in the format the brief gives. End with one line per row: row, result, the change, the mechanism, the generator rule, what did not work.

Hard rules (same as every lane): never edit anything under <REPO>/src/, never run git, gates, sweeps or landings; never change a row's cfg/recipe (that writes the ledger) - if a recipe change would make a candidate exact, say so in the report with the cell and flags; byte-exact candidates go to out/<container>/<name>.c with the .base_sha that lab.py writes; every file you create stays inside the lane directory. Do not run recursive greps over work/ or the repo root (shared-disk IO rule); the kit and TOOLS.md give you absolute paths. Run shell commands in the foreground (no background jobs) and do not poll with pgrep on your own patterns. A candidate must not add volatile, ASM_* macros, one-trip blocks or inline asm; keep every #include the row needs and do not leave unused typedefs behind. An uglier but pure-C spelling that removes a pin is acceptable (owner ruling) - say so in the report. A NON_MATCHING arm may be edited in lockstep with the compiled arm, never deleted.

FINAL STEP: write your complete final report (the model line first, then the per-row lines) to <LANE_DIR>/last_message.txt. Do NOT write any token figure anywhere: the orchestrator records your measured usage from the Agent tool (tools/lanes/record_usage.py). Then return the same report.
