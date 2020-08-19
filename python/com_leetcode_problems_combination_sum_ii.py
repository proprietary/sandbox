#!/usr/bin/env python3

from typing import List

class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        memo = {}
        def comb(idxs: List[int], target: int) -> List[List[int]]:
            nonlocal candidates
            if target in memo:
                return memo[target]
            if len(candidates) == 0 or target <= 0:
                return [[]]
            results = []
            for i, idx in enumerate(idxs):
                candidate = candidates[idx]
                if candidate > target:
                   continue
                completions = comb(idxs[:i] + idxs[i+1:], target - candidate)
                for s in completions:
                    if idx not in s:
                       a = [idx] + s
                       if a not in results:
                          results.append(a)
            # remove duplicates
            s = set(frozenset(l) for l in results)
            results = [list(t) for t in s]
            # print(f"target={target}, candidates={candidates}, results={results}")
            # add to memoized results
            memo[target] = results
            return results
        results = [[candidates[idx] for idx in lst] for lst in comb(list(range(len(candidates))), target)]
        # remove duplicates
        s = set(tuple(sorted(l)) for l in results)
        results = [list(t) for t in s]
        return results


if __name__ == '__main__':
   from pprint import pprint
   s = Solution()
   res = s.combinationSum2([10,1,2,7,6,1,5], 8)
   pprint(res)
   expected = [[1, 7], [1, 2, 5], [2, 6], [1, 1, 6]]
   

