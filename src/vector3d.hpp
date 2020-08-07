#pragma once

#include <iostream>
#include <cmath>
#include <stdexcept>

template <typename T>
class vector3d {
    public:
        vector3d() { x=0, y=0, z=0; }
        vector3d(T x1, T y1, T z1) : x(x1), y(y1), z(z1) {}
        vector3d(const vector3d& v) { x=v.x, y=v.y, z=v.z; }

        vector3d operator+(const vector3d& v) {
            return vector3d(x+v.x, y+v.y, z+v.z);
        }
        vector3d& operator+=(const vector3d& v) {
            x+=v.x;
            y+=v.y;
            z+=v.z;
            return *this;
        }
        vector3d operator-(const vector3d& v) const {
            return vector3d(x-v.x, y-v.y, z-v.z);
        }
        vector3d& operator-=(const vector3d& v) {
            x-=v.x;
            y-=v.y;
            z-=v.z;
            return *this;
        }
        vector3d operator*(const T val) {
            return vector3d(x*val, y*val, z*val);
        }
        vector3d& operator*=(const T val) {
            x*=val;
            y*=val;
            z*=val;
            return *this;
        }
        vector3d operator/(const T val) const {
            if (val == 0) throw std::runtime_error("Attempted division by 0.");
            return vector3d(x/val, y/val, z/val);
        }
        vector3d& operator/=(const T val) {
            if (val == 0) throw std::runtime_error("Attempted division by 0.");
            x/=val;
            y/=val;
            z/=val;
            return *this;
        }
        vector3d& operator=(const vector3d& v) {
            x=v.x;
            y=v.y;
            z=v.z;
            return *this;
        }
        bool operator==(const vector3d& v) const {
            if (x==v.x && y==v.y && z==v.z) return true;
            return false;
        }
        T dot_product(const vector3d& v) const {
            return x*v.x+y*v.y+z*v.z;
        }
        T magnitude() const {
            return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        }
        T distance(const vector3d& v) const {
            vector3d diff = *this - v;
            return diff.magnitude();
        }
        vector3d& normalize() {
            T len = this->magnitude();
            if (len == 0) std::runtime_error("Div by 0 in vector3d.normalize()");
            return this->operator/=(len);
        }
        friend std::ostream& operator<<(std::ostream& os, const vector3d& v)  {
            os << "vector3d(" << v.x << ", " << v.y << ", " << v.z << ")"  << std::endl;
            return os;
        }
        T& X() {
            return x;
        }
        T& Y() {
            return y;
        }
        T& Z() {
            return z;
        }
        bool isZero() {
            if (x==0 && y==0 && z==0 ) return true;
            return false;
        }
        //Return new vector3d where angles are in radians.
        vector3d angle() const {
            T mag = magnitude();
            T x_ang = acos(x / mag);
            T y_ang = acos(y / mag);
            T z_ang = acos(z / mag);
            return vector3d(x_ang, y_ang, z_ang);
        }
        T angleBetween(const vector3d& v) const {
            return std::acos(dot_product(v) / (magnitude()*v.magnitude() )) * 180 / M_PI;
        }

    private:
        T x, y, z;
};