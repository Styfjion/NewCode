from typing import Tuple, Callable


def create_counter(init: int) -> Tuple[Callable[..., int], Callable[..., int], Callable[..., int]]:
    cur_value = init

    def add():
        nonlocal cur_value
        cur_value += 1
        return cur_value

    def dec():
        nonlocal cur_value
        cur_value -= 1
        return cur_value

    def reset():
        nonlocal cur_value
        cur_value = init
        return cur_value
    return add, dec, reset

if __name__ == '__main__':
    add, dec, reset = create_counter(5)
    print(add())
    print(reset())
    print(dec())

# 6
# 5
# 4
