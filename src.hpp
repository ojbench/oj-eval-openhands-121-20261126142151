#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <iostream> // 输入输出
#include <iomanip>  // 控制输出格式
#include <cmath>    // 数学函数
#include <stdexcept> // 异常处理
// 你不可以使用任何其他的头文件!


namespace sjtu {

// 异常类，你需要要添加一个函数 what() 来返回异常信息。
class divided_by_zero final : public std::exception {
  public:
    divided_by_zero()   = default;
    ~divided_by_zero()  = default;
    const char* what() const noexcept override {
        return "complex divided by zero!";
    }
};

// 用于判断浮点数的符号.
inline int sign(double x) {
    const double eps = 1e-6;
    return (x > eps) - (x < -eps);
}

// 请保留所有的接口声明，即使你没有实现它们。
// 否则可能出现编译错误，无法通过部分测试点。
// TODO 补全类的实现
class complex {
  private:
    double a, b; // a + bi
  public:
    
    complex() : a(0), b(0) {}
    complex(double a) : a(a), b(0) {}
    complex(double a, double b) : a(a), b(b) {}

    double &real() { return a; }
    double &imag() { return b; }

    complex operator - () const { return complex(-a, -b); }
    complex operator ~ () const { return complex(a, -b); }

    complex operator + (const complex &rhs) const { return complex(a + rhs.a, b + rhs.b); }
    complex operator - (const complex &rhs) const { return complex(a - rhs.a, b - rhs.b); }
    complex operator * (const complex &rhs) const { return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a); }
    complex operator / (const complex &rhs) const {
        double denom = rhs.a * rhs.a + rhs.b * rhs.b;
        if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
            throw divided_by_zero();
        }
        return complex((a * rhs.a + b * rhs.b) / denom, (b * rhs.a - a * rhs.b) / denom);
    }

    complex &operator += (const complex &rhs) { a += rhs.a; b += rhs.b; return *this; }
    complex &operator -= (const complex &rhs) { a -= rhs.a; b -= rhs.b; return *this; }
    complex &operator *= (const complex &rhs) {
        double na = a * rhs.a - b * rhs.b;
        double nb = a * rhs.b + b * rhs.a;
        a = na; b = nb;
        return *this;
    }
    complex &operator /= (const complex &rhs) {
        double denom = rhs.a * rhs.a + rhs.b * rhs.b;
        if (sign(rhs.a) == 0 && sign(rhs.b) == 0) {
            throw divided_by_zero();
        }
        double na = (a * rhs.a + b * rhs.b) / denom;
        double nb = (b * rhs.a - a * rhs.b) / denom;
        a = na; b = nb;
        return *this;
    }

    bool operator == (const complex &rhs) const {
        return sign(fabs(a - rhs.a)) == 0 && sign(fabs(b - rhs.b)) == 0;
    }
    
    explicit operator bool() const {
        return sign(a) != 0 || sign(b) != 0;
    }

    friend std::ostream &operator << (std::ostream &os, const complex &x) {
        os << std::fixed << std::setprecision(6);
        // Real part: '-' prefix only if real < -1e-6
        if (sign(x.a) < 0) {
            os << "-";
        }
        os << std::fabs(x.a);
        // Imaginary part
        if (sign(x.b) < 0) {
            os << "-";
        } else {
            os << "+";
        }
        os << std::fabs(x.b) << "i";
        return os;
    }
};

}

#endif
