// Copyright 2022 UNN-CS
#include <cmath>
#include "circle.h"

static const double PI = 3.141592653589793;

Circle::Circle(double r) {
  radius = r < 0.0 ? 0.0 : r;
  ference = 2.0 * PI * radius;
  area = PI * radius * radius;
}

void Circle::setRadius(double r) {
  radius = r < 0.0 ? 0.0 : r;
  ference = 2.0 * PI * radius;
  area = PI * radius * radius;
}

void Circle::setFerence(double f) {
  ference = f < 0.0 ? 0.0 : f;
  radius = ference / (2.0 * PI);
  area = PI * radius * radius;
}

void Circle::setArea(double a) {
  area = a < 0.0 ? 0.0 : a;
  radius = std::sqrt(area / PI);
  ference = 2.0 * PI * radius;
}

double Circle::getRadius() const {
  return radius;
}

double Circle::getFerence() const {
  return ference;
}

double Circle::getArea() const {
  return area;
}
