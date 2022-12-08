class A(object):
    a_cls: int = 1

    def __new__(cls, *args, **kwargs):
        cls.a_cls = 2
        return super().__new__(cls, *args, **kwargs)

    def __init__(self):
        self.a_i: int = 2

    def test_ins(self):
        print(f"{self.__class__.__name__}:ins a_i:{self.a_i}")

    @classmethod
    def test_cls(cls):
        print(f"{cls.__name__}:cls a_c:{cls.a_cls}")

    @staticmethod
    def test_static():
        print("a static method")


class B(A):

    def __new__(cls, *args, **kwargs):
        ins = super().__new__(cls, *args, **kwargs)
        cls.a_cls = 4
        return ins

    def __init__(self):
        super().__init__()
        self.b_i = 6

    def test_ins(self):
        print(f"{self.__class__.__name__}:ins b_i:{self.b_i}")

    @classmethod
    def test_cls(cls):
        print(f"{cls.__name__}:cls b_c:{cls.a_cls}")

    @staticmethod
    def test_static():
        print("b static method")

    def test_super_ins(self):
        super().test_ins()

    @classmethod
    def test_super_cls(cls):
        super().test_cls()


if __name__ == '__main__':
    A.test_cls()
    a = A()
    a.test_ins()
    A.test_static()
    print("_______________________")
    B.test_super_cls()
    B.test_cls()
    b = B()
    B.test_cls()
    b.test_ins()
    A.test_cls()
    B.test_static()
    b.test_super_ins()
    B.test_super_cls()

# A:cls a_c:1
# A:ins a_i:2
# a static method
# _______________________
# B:cls a_c:2
# B:cls b_c:2
# B:cls b_c:4
# B:ins b_i:6
# A:cls a_c:2
# b static method
# B:ins a_i:2
# B:cls a_c:4
