#pragma once
class Point {
private:
    double _x, _y;
public:
    Point(double x, double y);
    double getX();
    double getY();
    void setX(const double);
    void setY(const double);
};