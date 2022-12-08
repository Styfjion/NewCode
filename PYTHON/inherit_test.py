class A(object):
    a_cls: int = 1

    def __init__(self):
        self.a_i: int = 2

    def test_a_ins(self):
        print(f"{self.__class__.__name__}:ins:{self.a_cls}")

    @classmethod
    def test_a_cls(cls):
        print(f"{cls.__name__}:cls:{cls.a_cls}")

    @staticmethod
    def test_static():
        print("static method")


class B(A):
    def __init__(self):
        super().__init__()


if __name__ == '__main__':
    A.test_a_cls()
    A().test_a_ins()
    B.test_a_cls()
    B().test_a_ins()

# A:cls:1
# A:ins:1
# B:cls:1
# B:ins:1
