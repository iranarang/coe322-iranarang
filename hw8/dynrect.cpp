// Names: Christine Goh, Ira Narang, Rhea Samuel
// UTEIDs: cxg96, in2933, rss3488
// TACC Usernames: christinegoh, iranarang, rheasamuel12

#include <memory>
#include <iostream>
#include <cmath>

using std::make_shared;
using std::shared_ptr;

class Point
{
private:
    float x, y;

public:
    Point(float xCoord, float yCoord) : x(xCoord), y(yCoord) {}

    void scale(float factor)
    {
        x *= factor;
        y *= factor;
    }

    float getX() const
    {
        return x;
    }

    float getY() const
    {
        return y;
    }
};

class Rectangle
{
private:
    Point bl;
    Point tr;

public:
    Rectangle(Point ibl, Point itr) : bl(ibl), tr(itr) {}

    float calculateArea() const // method to calculate area using points
    {
        return std::abs(tr.getX() - bl.getX()) * std::abs(tr.getY() - bl.getY());
    }
};

class DynRectangle
{
private:
    shared_ptr<Point> bl, tr;

public:
    DynRectangle(shared_ptr<Point> ibl, shared_ptr<Point> itr) : bl(ibl), tr(itr) {}
    float calculateArea() const // method to calculate area using points
    {
        return std::abs(tr->getX() - bl->getX()) * std::abs(tr->getY() - bl->getY());
    }
};

int main()
{
    // point origin: (0,0)
    // point fivetwo: (5,2)
    auto origin = make_shared<Point>(0, 0);
    auto fivetwo = make_shared<Point>(5, 2);

    // Make a dynamic rectangle
    DynRectangle lielow(origin, fivetwo);

    // Calculate and print the initial area
    std::cout << "Area: " << lielow.calculateArea() << '\n';

    // Scale the top-right point
    fivetwo->scale(2.0);

    // Recalculate and print the area after scaling
    std::cout << "Area: " << lielow.calculateArea() << '\n';

    return 0;
}
