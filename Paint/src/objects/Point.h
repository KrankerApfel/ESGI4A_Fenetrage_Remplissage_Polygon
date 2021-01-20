#pragma once
class Point {
private:
    double _x, _y;
public:
    Point(double x, double y);
    Point();
    double getX() const;
    double getY() const;
    void setX(const double);
    void setY(const double);
    bool operator==(const Point& A) const;
    bool operator!=(const Point& A) const;
};