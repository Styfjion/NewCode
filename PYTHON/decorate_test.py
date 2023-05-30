from functools import wraps
from typing import Callable


# 无参装饰器常用形式
def decorate_one(func):
    # register operation
    print("register one")

    @wraps(func)
    def wrapper(*args, **kwargs):
        # execute operation
        print("execute one")
        return func(*args, **kwargs)

    return wrapper  # 返回外层函数定义，调用时执行，不会立即打印


# 可适用于导入后注册等功能
def decorate_two(func):
    # register operation
    print("register two")  # 模块导入后立即执行，先打印，返回函数定义
    return func


# 可适用于导入后注册等功能
def decorate_tree(func):
    @wraps(func)
    def wrapper():
        # register operation
        print("register three")
        return func

    return wrapper()  # 模块导入后立即执行，先打印


# 有参装饰器，可适用于导入后注册等功能
def decorate_four(register: str):
    def wrapper(func):
        # register operation
        print(register)  # 装饰器函数执行时机以以func作为参数的函数开始，此处wrapper会在模块导入后立即执行，先打印
        return func

    return wrapper


# 有参装饰器常用形式
def decorate_five(register: str, execute: str):
    def out_wrapper(func):
        # register operation
        print(register)

        @wraps(func)
        def wrapper(*args, **kwargs):
            # execute operation
            print(execute)
            return func(*args, **kwargs)

        return wrapper  # 装饰器函数执行时机以以func作为参数的函数开始，out_wrapper立即执行，返回wrapper定义，在函数调用时执行打印

    return out_wrapper


class DecorateOne(object):
    def __init__(self, func):
        self.func = func

    def __call__(self, *args, **kwargs):
        # execute operation
        print("execute class decorate no param")  # 函数调用时打印
        return self.func(*args, **kwargs)


class DecorateTwo(object):
    def __init__(self, register: str, execute: str):
        self.register = register
        self.execute = execute

    def __call__(self, func):
        # register operation
        print(self.register)  # __call__以func作为参数会在模块导入后立即执行，此行会先打印

        @wraps(func)
        def wrapper(*args, **kwargs):
            # execute operation
            print(self.execute)
            return func(*args, **kwargs)

        return wrapper


def method_decorator(key: str, value: str) -> Callable:
    def out_wrapper(func: Callable) -> Callable:
        @wraps(func)
        def wrapper(*args, **kwargs):
            self = args[0]
            func(*args, **kwargs)
            self.data[key] = value
            self.post_process()
        return wrapper
    return out_wrapper


class Target(object):
    def __init__(self, data: dict):
        self.data = data

    @method_decorator("practise", "practise_val")
    def insert_func(self):
        print(f"inner data is {self.data}")

    def post_process(self):
        print(f"post process {self.data}")


@decorate_one
def practise_one():
    print("practise_one")


@decorate_two
def practise_two():
    print("practise_two")


@decorate_tree
def practise_three():
    print("practise_three")


@decorate_four("register four")
def practise_four():
    print("practise_four")


@decorate_five("register five", "execute five")
def practise_five():
    print("practise_five")


@decorate_one
def practise_param_one(param: int):
    print(f"practise_param_one:{param}")


@decorate_five("register five param", "execute five param")
def practise_param_two(param: int):
    print(f"practise_param_five:{param}")


@DecorateOne
def practise_class_one(param: int):
    print(f"practise_class_one:{param}")


@DecorateTwo("register five param", "execute five param")
def practise_class_tow(param: int):
    print(f"practise_class_tow:{param}")


if __name__ == '__main__':
    print("-----------------------------")
    practise_one()
    practise_two()
    practise_three()
    practise_four()
    practise_five()
    practise_param_one(1)
    practise_param_two(2)
    practise_class_one(3)
    practise_class_tow(4)
    target = Target({"prime": "prime_val"})
    target.insert_func()
'''
register one
register two
register three
register four
register five
register one
register five param
register five param
-----------------------------
execute one
practise_one
practise_two
practise_three
practise_four
execute five
practise_five
execute one
practise_param_one:1
execute five param
practise_param_five:2
execute class decorate no param
practise_class_one:3
execute five param
practise_class_tow:4
inner data is {'prime': 'prime_val'}
post process {'prime': 'prime_val', 'practise': 'practise_val'}
'''
