#include <Vc/simdize>
#include <Vc/IO>

template <typename T> struct PointTemplate {
    T x, y, z;

    using InstantiatedType = PointTemplate<T>;
    Vc_SIMDIZE_MEMBER(T, 0, x);
    Vc_SIMDIZE_MEMBER(T, 1, y);
    Vc_SIMDIZE_MEMBER(T, 2, z);
    Vc_SIMDIZE_STRUCT(InstantiatedType, 3);
};

using Point = PointTemplate<float>;

template <typename T> class Vectorizer
{
public:
    using value_type = Vc::simdize<T>;

    void append(const T &x) { decorate(data)[count++] = x; }
    bool isFull() const { return count == data.size(); }
    const value_type &contents() const { return data; }

private:
    value_type data;
    int count = 0;
};

int main()
{
    Vectorizer<Point> v;
    float x = 0.f;
    while (!v.isFull()) {
        v.append(Point{x, x + 1, x + 2});
        x += 10;
    }
    const auto &vec = v.contents();
    std::cout << vec.x << '\n' << vec.y << '\n' << vec.z << '\n';
    return 0;
}
