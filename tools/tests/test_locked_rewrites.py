"""atomic_io.update_bytes / append_rows / remove_rows: read-modify-write under the append lock (names journal restore paths)."""
import json, os, sys, tempfile, threading, time, unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import atomic_io, common


class Rewrites(unittest.TestCase):
    def setUp(self):
        self.d = tempfile.mkdtemp(); self.addCleanup(__import__('shutil').rmtree, self.d, True)
        self.p = Path(self.d) / 'names.jsonl'

    def test_append_between_read_and_replace_is_not_lost(self):
        """the rewriter reads, an appender fires while it still computes, the rewriter replaces: the appended row survives"""
        self.p.write_text('{"a":1}\n')
        started = threading.Event(); t = []
        def fn(cur):
            t.append(threading.Thread(target=common.append_jsonl, args=(self.p, {"late": 1}))); t[0].start()
            time.sleep(0.4)   # the appender is now blocked on the lock
            return cur + b'{"mine":1}\n'
        atomic_io.update_bytes(self.p, fn); t[0].join(10)
        rows = [json.loads(l) for l in self.p.read_text().splitlines()]
        self.assertEqual([list(r)[0] for r in rows], ['a', 'mine', 'late'])

    def test_old_snapshot_restore_would_lose_it(self):
        """documents the bug being fixed: restoring a pre-run snapshot drops rows other tools appended since"""
        self.p.write_text('{"a":1}\n'); before = self.p.read_bytes()
        common.append_jsonl(self.p, {"mine": 1}); common.append_jsonl(self.p, {"other": 1})
        atomic_io.write_bytes(self.p, before)
        self.assertNotIn('other', self.p.read_text())

    def test_remove_rows_keeps_foreign_rows(self):
        self.p.write_text('{"a":1}\n')
        mine = [b'{"mine":1}\n', b'{"mine":2}\n']
        atomic_io.append_rows(self.p, mine); common.append_jsonl(self.p, {"other": 1})
        n = atomic_io.remove_rows(self.p, mine)
        self.assertEqual(n, 2); self.assertEqual(self.p.read_text(), '{"a":1}\n{"other":1}\n')

    def test_remove_rows_takes_last_occurrence_only(self):
        self.p.write_bytes(b'{"x":1}\n{"x":1}\n'); atomic_io.remove_rows(self.p, [b'{"x":1}\n'])
        self.assertEqual(self.p.read_bytes(), b'{"x":1}\n')

    def test_append_rows_repairs_missing_newline_and_creates(self):
        self.p.write_bytes(b'{"a":1}'); atomic_io.append_rows(self.p, [b'{"b":2}\n'])
        self.assertEqual(self.p.read_bytes(), b'{"a":1}\n{"b":2}\n')
        q = Path(self.d) / 'new.jsonl'; atomic_io.append_rows(q, [b'x\n']); self.assertEqual(q.read_bytes(), b'x\n')

    def test_concurrent_rewriters_and_appenders_lose_nothing(self):
        self.p.write_text('')
        def appender(k):
            for i in range(60): common.append_jsonl(self.p, {"k": k, "i": i})
        def rewriter(k):
            for i in range(20):
                row = (json.dumps({"r": k, "i": i}) + "\n").encode()
                atomic_io.append_rows(self.p, [row]); time.sleep(0.001)
                atomic_io.remove_rows(self.p, [row])
        ts = [threading.Thread(target=appender, args=(k,)) for k in range(3)] + [threading.Thread(target=rewriter, args=(k,)) for k in range(2)]
        [x.start() for x in ts]; [x.join() for x in ts]
        rows = [json.loads(l) for l in self.p.read_text().splitlines()]
        self.assertEqual(len(rows), 180); self.assertTrue(all('k' in r for r in rows))
        self.assertEqual(list(Path(self.d).glob('.*.tmp')), [])


if __name__ == '__main__':
    unittest.main()
