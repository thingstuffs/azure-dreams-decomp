"""Bounded, staged pin search. No source publication or model calls in this module."""
import collections
import difflib
import json
import re
import resource
import sqlite3
import subprocess
import sys
import time
import zlib
from pathlib import Path

from common import sha_text
from pin_census import sites_of, unscored_text
from census import _fakedep
from xform import t27_beam as old
from xform.screen import compile_s, sdiff

DEFAULTS = dict(screens=1200, verifies=12, cpu_seconds=40, group_screens=240,
                depth=3, beam=4, fallback=2, band=30)

def cpu_time():
    return sum(r.ru_utime + r.ru_stime for r in
               (resource.getrusage(resource.RUSAGE_SELF), resource.getrusage(resource.RUSAGE_CHILDREN)))

def debt(text):
    return (*old.debt(text), _fakedep(text))

def improves(before, after):
    a, b = debt(before), debt(after)
    return b[0] < a[0] and all(y <= x for x, y in zip(a[1:], b[1:]))

def mechanism(ref, got):
    if got is None:
        return "build-error"
    if ref == got:
        return "assembler-or-dead"
    regs = lambda ls: [re.sub(r"\$\w+", "$R", s) for s in ls]
    if regs(ref) == regs(got):
        return "allocation"
    if collections.Counter(ref) == collections.Counter(got):
        return "scheduling"
    changed = list((collections.Counter(ref) - collections.Counter(got)).elements())
    changed += list((collections.Counter(got) - collections.Counter(ref)).elements())
    if any(re.search(r"\b(lui|li|la)\b|%hi|%lo", s) for s in changed):
        return "addressing"
    return "mixed"

FAMILIES = {
    "allocation": {"host", "hostwide", "unhost", "declorder", "narrow", "dropcopy", "mask2cast"},
    "scheduling": {"dup_after_if", "armstore", "ret2break", "gotoloop", "realloop", "postinc", "dropcopy"},
    "addressing": {"basesym", "litsym", "ptr2index", "dropcopy", "host", "hostwide"},
}

def ranked_menu(candidates, kind):
    """Prioritize evidence, retaining one exploration candidate in every four slots."""
    preferred, explore = [], []
    for item in candidates:
        (preferred if item[0].split(":")[0] in FAMILIES.get(kind, set()) else explore).append(item)
    if not preferred:
        return explore
    out = []
    while preferred or explore:
        out.extend(preferred[:3]); del preferred[:3]
        out.extend(explore[:1]); del explore[:1]
        if not preferred:
            out.extend(explore); break
    return out

def diverse(items, count):
    ordered = sorted(items, key=lambda x: x[0])
    chosen, families = [], set()
    for x in ordered:
        fam = x[2].rsplit("+", 1)[-1].split(":")[0]
        if fam not in families:
            chosen.append(x); families.add(fam)
            if len(chosen) == count: return chosen
    chosen.extend(x for x in ordered if x not in chosen)
    return chosen[:count]

class Limit(Exception):
    pass

class Session:
    def __init__(self, row, text, recipe, cache, options, verify_fn, on_win=None):
        self.row, self.original, self.options, self.verify_fn = row, text, options, verify_fn
        self.start, self.cpu_start = time.monotonic(), cpu_time()
        self.stats = collections.Counter()
        self.best = text
        self.stop = "complete"
        self.recipe = recipe
        self.db = sqlite3.connect(cache)
        self.db.execute("PRAGMA journal_mode=WAL")
        self.db.execute("PRAGMA synchronous=NORMAL")
        self.db.execute("CREATE TABLE IF NOT EXISTS assembly (key TEXT PRIMARY KEY, value TEXT NOT NULL)")
        self.memo, self.verified, self.menus = {}, {}, {}
        self.near = []
        self.group_log = []
        self.on_win = on_win
        self.timeout = None

    def check(self):
        if cpu_time() - self.cpu_start >= self.options["cpu_seconds"]:
            raise Limit("cpu-budget")

    def compile(self, row, text):
        self.check()
        if self.stats["screened"] >= self.options["screens"]:
            raise Limit("screen-budget")
        self.stats["screened"] += 1
        h = sha_text(self.recipe + json.dumps(row, sort_keys=True) + text)
        if h in self.memo:
            self.stats["cache_hits"] += 1
            return self.memo[h]
        hit = self.db.execute("SELECT value FROM assembly WHERE key=?", (h,)).fetchone()
        if hit:
            self.stats["cache_hits"] += 1
            raw = zlib.decompress(hit[0]) if isinstance(hit[0],bytes) else hit[0]
            self.memo[h] = json.loads(raw); return self.memo[h]
        t0 = time.monotonic()
        try:
            result = compile_s(row, text)
        except subprocess.TimeoutExpired as exc:
            # A pathological generated program must not discard the row's proven wins.
            # End this bounded search and retain the exact input for diagnosis. A timeout
            # compiling the reference remains an error; neither case enters the cache.
            self.stats["compile_timeouts"] += 1
            command=exc.cmd[0] if isinstance(exc.cmd,(list,tuple)) else exc.cmd
            self.timeout=dict(text=text,source_sha=sha_text(text),seconds=exc.timeout,
                              compiler=Path(command).name,reference=text==self.original)
            if text==self.original: raise
            raise Limit("compiler-timeout") from exc
        finally:
            self.stats["compile_seconds"] += time.monotonic() - t0
            self.stats["compiled"] += 1
        if result is None:
            self.stats["build_failures"] += 1
            # Do not persist failures: missing inputs and temporary compiler errors are retryable.
            return None
        self.memo[h] = result
        self.db.execute("INSERT OR REPLACE INTO assembly VALUES (?,?)", (h, zlib.compress(json.dumps(result).encode(),1)))
        self.db.commit()
        return result

    def verify(self, text):
        self.check()
        h = sha_text(text)
        if h in self.verified: return self.verified[h]
        if unscored_text(text) != unscored_text(self.original) or not improves(self.original, text):
            return {"exact": False, "status": "debt-or-unscored-edit"}
        if self.stats["tried"] >= self.options["verifies"]:
            raise Limit("verify-budget")
        self.stats["tried"] += 1
        t0 = time.monotonic(); result = self.verify_fn(text)
        self.stats["verify_seconds"] += time.monotonic() - t0
        self.verified[h] = result
        if result.get("exact") and improves(self.best, text):
            self.best = text
            if self.on_win: self.on_win(text)
        return result

    def menu(self, text, slus, kind="mixed", depth=0):
        self.check()
        h = sha_text(text + kind + str(depth))
        if h not in self.menus:
            t0 = time.monotonic()
            shape = sys.modules[old.T15.__module__]
            generators = {g.__name__.removesuffix("_candidates"):g for g in old.N.GENERATORS}
            generators.update({name:getattr(shape,name+"_candidates") for name in
                ("narrow","dup_after_if","mask2cast","maskfold","litsym","fold_load","fold_temp","commute","inplace_update")})
            if not slus: generators["basesym"] = old.N.basesym_candidates
            # Generate the relevant families, rather than eagerly building the full menu and
            # only then sorting it. Universal proven shapes and rotating exploration remain.
            primary = ["dropcopy","narrow","dup_after_if"]
            if kind in FAMILIES: primary += sorted(FAMILIES[kind])
            else: primary += ["armstore","postinc","gotoloop","realloop","hostwide","unhost"]
            chosen = list(dict.fromkeys(k for k in primary if k in generators))
            rest = [k for k in generators if k not in chosen]
            if rest: chosen.append(rest[depth % len(rest)])
            result=[]; seen={text}
            for key in chosen:
                self.check()
                try: candidates=generators[key](text)
                except Exception:
                    self.stats["generator_errors"] += 1;continue
                for label,c in candidates:
                    if c not in seen: result.append((label,c));seen.add(c)
            self.menus[h] = result
            self.stats["generation_seconds"] += time.monotonic() - t0
        else: self.stats["menu_cache_hits"] += 1
        return self.menus[h]

    def remember(self, kind, group, d, label, text):
        if d is None or d == 0: return
        self.near.append(dict(kind=kind, group=list(group), distance=d, label=label, text=text))
        self.near.sort(key=lambda r: r["distance"])
        unique = {}
        for r in self.near: unique.setdefault(sha_text(r["text"]), r)
        self.near = list(unique.values())[:3]

    def baseline(self):
        # The historical algorithm is retained as the pilot control. Each worker runs one arm
        # at a time in its own process; restoring the module prevents cross-arm contamination.
        old_values = {k: getattr(old, k) for k in ("compile_s", "SCREEN", "BUDGET", "GROUP_SCREEN", "DEPTH", "BEAM", "BAND")}
        try:
            old.compile_s = self.compile
            for key, opt in (("SCREEN", "screens"), ("BUDGET", "verifies"), ("GROUP_SCREEN", "group_screens"),
                             ("DEPTH", "depth"), ("BEAM", "beam"), ("BAND", "band")):
                setattr(old, key, self.options[opt])
            _, info = old.T.apply_verified(self.original, self.row, {}, self.verify)
            if info.get("err"): self.stop = "reference-build-error"
            elif info.get("screened", 0) >= self.options["screens"]: self.stop = "screen-budget"
            elif info.get("tried", 0) >= self.options["verifies"]: self.stop = "verify-budget"
            self.stats["groups_visited"] = len(info.get("groups", []))
            return info
        finally:
            for k, v in old_values.items(): setattr(old, k, v)

    def targeted(self):
        ref = self.compile(self.row, self.original)
        if ref is None:
            self.stop = "reference-build-error"; return {}
        cur, steps, group_log = self.original, [], self.group_log
        while True:
            won = False
            # Fresh census linkage already takes instruction overlap into account. Singles
            # and nearby pairs remain the fallback when those measurements are stale.
            plan = old.groups(cur, self.row)
            live = sites_of(cur)
            marker = lambda i: any(k in live[i][1] for k in ("TAILSLOT", "JALDELAY", "PAGEBASE", "SCHED_BARRIER"))
            # Cheap marker residues otherwise consume the entire budget ahead of ordinary C
            # pins (confirmed by the 8187BB80 replay). Keep them eligible, but defer them.
            plan.sort(key=lambda group: all(marker(i) for i in group))
            group_limit = min(self.options["group_screens"], max(12, self.options["screens"] // max(1,len(plan))))
            for group in plan:
                self.check()
                base = old.erase_many(cur, [sites_of(cur)[i] for i in group], clean_notes=True)
                asm = self.compile(self.row, base); d0 = sdiff(ref, asm); kind = mechanism(ref, asm)
                self.stats["groups_visited"] += 1
                if d0 is None: continue
                record = dict(group=list(group), kind=kind, initial=d0, best=d0)
                group_log.append(record)
                if d0 == 0 and self.verify(base).get("exact"):
                    cur = base; steps.append("erase"); won = True; break
                if d0 > self.options["band"]:
                    self.stats["outside_band"] += 1; continue
                frontier, seen, candidates = [(d0, base, "erase")], {sha_text(base)}, [(d0, base, "erase")]
                used = 0
                for depth in range(self.options["depth"]):
                    children = []
                    for _, source, lab in frontier:
                        for label, c in ranked_menu(self.menu(source, self.row.get("kind") == "slus",kind,depth), kind):
                            if used >= group_limit: break
                            h = sha_text(c)
                            if h in seen: continue
                            seen.add(h); used += 1
                            d = sdiff(ref, self.compile(self.row, c))
                            if d is None: continue
                            label = lab + "+" + label
                            record["best"] = min(record["best"], d)
                            if 0 < d <= 4:
                                self.remember(kind, group, d, label, c)
                            if d == 0 and self.verify(c).get("exact"):
                                cur = c; steps.append(label); won = True; break
                            children.append((d, c, label)); candidates.append((d, c, label))
                        if won: break
                    if won: break
                    if not children: break
                    frontier = diverse(children, self.options["beam"])
                if not won:
                    # A small full-verifier allowance recovers post-cc1 convergence. Distance
                    # is a priority, never an assertion that different assembly cannot match.
                    fallback = [x for x in candidates if x[0] > 0 and improves(cur, x[1])]
                    # Historical exact-pair replay finds a scheduling miss. Broad nonzero
                    # probing spent 191 verifies for no extra wins in pilot v1; bound it to
                    # very near residues, with one exploratory probe for other classes.
                    allowed = [x for x in fallback if x[0] <= (4 if kind == "scheduling" else 2)]
                    cap = self.options["fallback"] if kind == "scheduling" else 1
                    allowance = max(0, cap - self.stats["fallback_tried"])
                    for d, c, label in diverse(allowed, allowance):
                        self.stats["fallback_tried"] += 1
                        if self.verify(c).get("exact"):
                            self.stats["fallback_wins"] += 1
                            cur = c; steps.append(label); won = True; break
                    for d, c, label in sorted(fallback, key=lambda x: x[0])[:1]:
                        self.remember(kind, group, d, label, c)
                if used >= group_limit: self.stats["group_budget_hits"] += 1
                if won: break
            if not won: break
        return dict(steps=steps, groups=group_log[:40])

    def run(self, mode):
        info = {}
        try:
            info = self.baseline() if mode == "baseline" else self.targeted()
        except Limit as exc:
            self.stop = str(exc)
            info = {"groups": self.group_log[:40]}
        finally:
            self.db.close()
        # A generated-program timeout is a bounded stop, not a negative compilation proof.
        # Reference failures remain retryable; no timeout is cached as rejected assembly.
        if self.stop == "complete" and self.stats["group_budget_hits"]:
            self.stop = "group-budget"
        return self.best, dict(info, **dict(self.stats), stop_reason=self.stop,
            seconds=time.monotonic()-self.start, cpu_seconds=cpu_time()-self.cpu_start,
            pins_in=debt(self.original)[0], pins_out=debt(self.best)[0],
            debt_in=debt(self.original), debt_out=debt(self.best))
