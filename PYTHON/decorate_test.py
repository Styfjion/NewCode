from functools import wraps


# 无参装饰器常用形式
def decorate_one(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        print("execute one")
        return func(*args, **kwargs)

    return wrapper  # 返回外层函数定义，调用时执行，不会立即打印


# 可适用于导入后注册等功能
def decorate_two(func):
    # register operation
    print("execute two")  # 模块导入后立即执行，先打印，返回函数定义
    return func


# 可适用于导入后注册等功能
def decorate_tree(func):
    @wraps(func)
    def wrapper():
        # register operation
        print("execute three")
        return func

    return wrapper()  # 模块导入后立即执行，先打印


# 有参装饰器，可适用于导入后注册等功能
def decorate_four(level):
    def wrapper(func):
        # register operation
        print(level)  # 装饰器函数执行时机以以func作为参数的函数开始，此处wrapper会在模块导入后立即执行，先打印
        return func

    return wrapper


# 有参装饰器常用形式
def decorate_five(level):
    def out_wrapper(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            print(level)
            return func(*args, **kwargs)

        return wrapper  # 装饰器函数执行时机以以func作为参数的函数开始，out_wrapper立即执行，返回wrapper定义，在函数调用时执行打印

    return out_wrapper


class DecorateOne(object):
    def __init__(self, func):
        self.func = func

    def __call__(self, *args, **kwargs):
        print("execute class decorate no param")  # 函数调用时打印
        return self.func(*args, **kwargs)


class DecorateTwo(object):
    def __init__(self, level):
        self.level = level

    def __call__(self, func):
        # register operation
        print("call time test")  # __call__以func作为参数会在模块导入后立即执行，此行会先打印
        
        @wraps(func)
        def wrapper(*args, **kwargs):
            print(self.level)
            return func(*args, **kwargs)

        return wrapper


@decorate_one
def test_one():
    print("test_one")


@decorate_two
def test_two():
    print("test_two")


@decorate_tree
def test_three():
    print("test_three")


@decorate_four("execute four")
def test_four():
    print("test_four")


@decorate_five("execute five")
def test_five():
    print("test_five")


@decorate_one
def test_param_one(param: int):
    print(f"test_param_one:{param}")


@decorate_five("execute five param")
def test_param_two(param: int):
    print(f"test_param_five:{param}")


@DecorateOne
def test_class_one(param: int):
    print(f"test_class_one:{param}")


@DecorateTwo("execute class decorate has param")
def test_class_tow(param: int):
    print(f"test_class_tow:{param}")


if __name__ == '__main__':
    print("-----------------------------")
    test_one()
    test_two()
    test_three()
    test_four()
    test_five()
    test_param_one(1)
    test_param_two(2)
    test_class_one(3)
    test_class_tow(4)

'''
execute two
execute three
execute four
call time test
-----------------------------
execute one
test_one
test_two
test_three
test_four
execute five
test_five
execute one
test_param_one:1
execute five param
test_param_five:2
execute class decorate no param
test_class_one:3
execute class decorate has param
test_class_tow:4
'''
