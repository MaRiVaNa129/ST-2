// Copyright 2026 UNN-CS
#include <cmath>
#include <stdexcept>
#include "circle.h"

namespace {
constexpr double Pi = 3.14159265358979323846;
}

Circle::Circle(double radius) {
  setRadius(radius);
}

void Circle::setRadius(double radius) {
  if (radius <= 0.0) {
    throw std::invalid_argument("Radius must be positive");
  }

  radius_ = radius;
  ference_ = 2.0 * Pi * radius_;
  area_ = Pi * radius_ * radius_;
}

void Circle::setFerence(double ference) {
  if (ference <= 0.0) {
    throw std::invalid_argument("Circumference must be positive");
  }

  ference_ = ference;
  radius_ = ference_ / (2.0 * Pi);
  area_ = Pi * radius_ * radius_;
}

void Circle::setArea(double area) {
  if (area <= 0.0) {
    throw std::invalid_argument("Area must be positive");
  }

  area_ = area;
  radius_ = std::sqrt(area_ / Pi);
  ference_ = 2.0 * Pi * radius_;
}

double Circle::getRadius() const {
  return radius_;
}

double Circle::getFerence() const {
  return ference_;
}

double Circle::getArea() const {
  return area_;
}
