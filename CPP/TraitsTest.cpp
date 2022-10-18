#include <iostream>

using namespace std;

struct A_tag {
};

struct B_tag {
};

struct int_tag {
};

struct A1 {
    int val;
    using category = A_tag;
};

struct A2 {
    int val;
    using category = A_tag;
};

struct B1 {
    int val;
    using category = B_tag;
};

struct B2 {
    int val;
    using category = B_tag;
};

template<typename T>
void doExecute(const T& type, A_tag)
{
    cout << "A type " << type.val << endl;
}

template<typename T>
void doExecute(const T& type, B_tag)
{
    cout << "B type " << type.val << endl;
}

template<typename T>
void doExecute(const T& type, int_tag)
{
    cout << "int type " << type << endl;
}

template<typename T>
struct ClassTraits {
    using category = typename T::category;
};

template<>
struct ClassTraits<int> {
    using category = int_tag;
};

template<typename T>
void execute(const T& type) {
    doExecute(type, typename ClassTraits<T>::category());
}

int main()
{
    A1 a1{1};
    A2 a2{2};
    B1 b1{3};
    B2 b2{4};
    execute(a1);
    execute(a2);
    execute(b1);
    execute(b2);
    execute(1);
    execute(2);
}