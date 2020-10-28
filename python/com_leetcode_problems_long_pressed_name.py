class Solution:
    def isLongPressedName(self, name: str, typed: str) -> bool:
        long_pressed = True
        name_idx = 0
        typed_idx = 0
        name_len = len(name)
        typed_len = len(typed)
        if typed_len < name_len:
            return False
        while True:
            if typed_idx >= typed_len or name_idx >= name_len:
                break
            n = name[name_idx]
            t = typed[typed_idx]
            if n == t:
                name_idx += 1
                typed_idx += 1
                continue
            else:
                if name_idx > 0 and t == name[name_idx - 1]:
                    long_pressed = True
                    typed_idx += 1
                    continue
                else:
                    return False
        if name_idx != name_len:
            return False
        while typed_idx < typed_len:
            if typed[typed_idx] != name[-1]:
                return False
            typed_idx += 1
        return long_pressed


if __name__ == '__main__':
    test_vec = [
        ('alex', 'aalex', True),
        ('saeed', 'ssaaedd', False),
        ('leelee', 'lleeelee', True),
        ('laiden', 'laiden', True),
        ('alex', 'alexxr', False),
        ('vtkgn', 'vttkgnn', True),
        ('pyplrz', 'ppyypllr', False),
    ]
    for v in test_vec:
        res = Solution().isLongPressedName(v[0], v[1])
        assert res == v[2], f"({v[0]}, {v[1]}) expected {v[2]}, got {res}"
