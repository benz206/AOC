# day10_p2.py
import sys
import re
import math
import re
import numpy as np
from scipy.optimize import milp, LinearConstraint

def parse_line(line):
    button_parts = re.findall(r'\(([^)]*)\)', line)
    buttons = []
    for bp in button_parts:
        bp = bp.strip()
        if not bp:
            buttons.append([])
        else:
            buttons.append([int(x) for x in bp.replace(",", " ").split()])

    # joltage targets
    curly = re.search(r'\{([^}]*)\}', line)
    target = []
    if curly:
        tpart = curly.group(1).strip()
        if tpart:
            target = [int(x) for x in tpart.replace(",", " ").split()]
    return buttons, target

def solve_machine(buttons, target):
    n = len(target)
    m = len(buttons)

    if n == 0 or m == 0:
        return 0

    # Build A (n x m) with 0/1 entries
    A = np.zeros((n, m), dtype=float)
    for j, idxs in enumerate(buttons):
        for i in idxs:
            if 0 <= i < n:
                A[i, j] = 1.0

    target_arr = np.array(target, dtype=float)

    c = np.ones(m, dtype=float)

    lc = LinearConstraint(A, lb=target_arr, ub=target_arr)

    integrality = np.ones(m, dtype=int)

    res = milp(c=c, integrality=integrality, constraints=[lc])

    return int(round(res.fun))


def main():
    total = 0
    for line in sys.stdin:
        line = line.strip()
        print(line)
        if not line:
            continue
        buttons, target = parse_line(line)
        if not target:
            continue
        total += solve_machine(buttons, target)
    print(total)

main()
