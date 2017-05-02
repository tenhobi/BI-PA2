#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Shape {
public:
    Shape (int x1, int y1, int x2, int y2) {
        m_minX = min(x1, x2);
        m_maxX = min(x1, x2);
        m_minY = min(y1, y2);
        m_maxY = min(y1, y2);
    }

    virtual Shape * Clone () const = 0;
//    {
//        return new Shape (*this);
//    }

    virtual ~Shape () {}

    virtual ostream& Print (ostream& os) const {
        return os << "[" << m_minX << "," << m_minY << "] [" << m_maxX << "," << m_maxY << "]";
    }

    friend ostream& operator << (ostream& os, const Shape& t) {
        return t.Print(os);
    }

protected:
    int m_minX, m_maxX, m_minY, m_maxY;
};

class Rectangle : public Shape {
public:
    Rectangle (int x1, int y1, int x2, int y2) : Shape(x1, y1, x2, y2) {}

    virtual Rectangle * Clone () const {
        return new Rectangle (*this);
    }

    virtual ostream& Print (ostream& os) const override {
        os << "Rectangle: ";
        return Shape::Print(os);
    }
};

class Square : public Shape {
public:
    Square (int x, int y, string name) : Shape(x, y, x, y), m_Name(name) {}

    virtual Square * Clone () const {
        return new Square (*this);
    }

    virtual ostream& Print (ostream& os) const override {
        os << ("Square(" + m_Name + "): ");
        return Shape::Print(os);
    }

    string m_Name;
};

class Rhombus : public Shape {
public:
    Rhombus (int x, int y) : Shape(x, y, x, y) {}

    virtual Rhombus * Clone () const {
        return new Rhombus (*this);
    }

    virtual ostream& Print (ostream& os) const override {
        os << "Rhombus: ";
        return Shape::Print(os);
    }
};

int main () {
    vector<Shape*> shapes;
    shapes.push_back(new Square(0, 1, "Squarishing"));
    shapes.push_back(new Rectangle(0, 0, 1, 2));
    shapes.push_back(new Rhombus(0, 2));

    for (int i = 0; i < 2; ++i) {
        shapes.push_back(shapes[i]->Clone());
    }

    for (int i = 0; i < shapes.size(); ++i) {
        cout << *shapes[i] << endl;
    }

    for (int i = 0; i < shapes.size(); ++i) {
        delete shapes[i];
    }

    return 0;
}
