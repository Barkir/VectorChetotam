#ifndef _MY_VEC2F_HPP_
#define _MY_VEC2F_HPP_

class Vec2f {
private:
    float x_ = 0.0F;
    float y_ = 0.0F;

public:
    Vec2f() = default;
    Vec2f(float x_value, float y_value) : x_(x_value), y_(y_value) {}

    explicit Vec2f(float value) : x_(value), y_(value) {}

    float x() const { return x_; }
    float y() const { return y_; }

    void set_x(float value) { x_ = value; }
    void set_y(float value) { y_ = value; }

    float length() const;
    float dot(const Vec2f& vec) const {
        return x_ * vec.x_ + y_ * vec.y_;
    }
    Vec2f get_ortogonal() const { return orthogonal(); }
    Vec2f orthogonal() const {
        return {y_, -x_};
    }

    Vec2f operator+(const Vec2f& vec) const {
        return {x_ + vec.x_, y_ + vec.y_};
    }
    Vec2f operator-(const Vec2f& vec) const {
        return {x_ - vec.x_, y_ - vec.y_};
    }
    Vec2f operator-() const {
        return {-x_, -y_};
    }
    Vec2f operator*(float scalar) const {
        return {x_ * scalar, y_ * scalar};
    }
    Vec2f operator*(const Vec2f& vec) const {
        return cwiseProduct(vec);
    }
    Vec2f operator/(float scalar) const {
        return {x_ / scalar, y_ / scalar};
    }
    Vec2f cwiseProduct(const Vec2f& vec) const {
        return {x_ * vec.x_, y_ * vec.y_};
    }

    Vec2f& operator+=(const Vec2f& vec) {
        x_ += vec.x_;
        y_ += vec.y_;
        return *this;
    }
    Vec2f& operator-=(const Vec2f& vec) {
        x_ -= vec.x_;
        y_ -= vec.y_;
        return *this;
    }
    Vec2f& operator*=(float scalar) {
        x_ *= scalar;
        y_ *= scalar;
        return *this;
    }
    Vec2f& operator/=(float scalar) {
        x_ /= scalar;
        y_ /= scalar;
        return *this;
    }

    bool operator==(const Vec2f& vec) const {
        return x_ == vec.x_ && y_ == vec.y_;
    }
    double operator^(const Vec2f& vec) const { return dot(vec); }
    Vec2f new_vec_from_basic(const class CoordSystem& cs) const;
    Vec2f get_vec_in_basic_cs(const class CoordSystem& cs) const;
    void print() const;
    bool operator!=(const Vec2f& vec) const {
        return !(*this == vec);
    }

};

Vec2f operator*(float scalar, const Vec2f& vector);

#endif

