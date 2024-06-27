/**Solutions to Chapter 2, Section 2, Exercise 3 of Horowitz's Data Structures.*/ 

#include <stdio.h>

struct Rectangle {
    float width;
    float height;
};

struct Triangle {
    float base;
    float height;
};

struct Circle {
    float radius;
};

typedef struct GeometricObject {
    enum {RECTANGLE, TRIANGLE, CIRCLE} type;
    union {
        struct Rectangle rectangle;
        struct Triangle triangle;
        struct Circle circle;
    };
} GeometricObject;

int main() {
    // Create a geometric object representing a rectangle
    struct GeometricObject rectangleObject;
    rectangleObject.type = RECTANGLE;
    rectangleObject.rectangle.width = 5.0;
    rectangleObject.rectangle.height = 3.0;

    // Create a geometric object representing a triangle
    struct GeometricObject triangleObject;
    triangleObject.type = TRIANGLE;
    triangleObject.triangle.base = 4.0;
    triangleObject.triangle.height = 6.0;

    // Create a geometric object representing a circle
    struct GeometricObject circleObject;
    circleObject.type = CIRCLE;
    circleObject.circle.radius = 2.5;

    // Print the details of the geometric objects
    printf("Rectangle: Width = %.2f, Height = %.2f\n",
           rectangleObject.rectangle.width, rectangleObject.rectangle.height);
    printf("Triangle: Base = %.2f, Height = %.2f\n",
           triangleObject.triangle.base, triangleObject.triangle.height);
    printf("Circle: Radius = %.2f\n",
           circleObject.circle.radius);

    return 0;
}
