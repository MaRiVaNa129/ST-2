// Copyright 2025 UNN-CS Team
#include <gtest/gtest.h>
#include <cmath>
#include "circle.h"
#include "tasks.h"

const double PI = 3.141592653589793;
const double EPSILON = 1e-10;

TEST(CircleTest, Constructor) {
  Circle c1(5.0);
  EXPECT_NEAR(c1.getRadius(), 5.0, EPSILON);
  EXPECT_NEAR(c1.getFerence(), 2.0 * PI * 5.0, EPSILON);
  EXPECT_NEAR(c1.getArea(), PI * 25.0, EPSILON);

  Circle c2;
  EXPECT_NEAR(c2.getRadius(), 0.0, EPSILON);
  EXPECT_NEAR(c2.getFerence(), 0.0, EPSILON);
  EXPECT_NEAR(c2.getArea(), 0.0, EPSILON);

  Circle c3(-3.0);
  EXPECT_NEAR(c3.getRadius(), 0.0, EPSILON);
}

TEST(CircleTest, SetRadius) {
  Circle c;
  c.setRadius(10.0);
  EXPECT_NEAR(c.getRadius(), 10.0, EPSILON);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * 10.0, EPSILON);
  EXPECT_NEAR(c.getArea(), PI * 100.0, EPSILON);

  c.setRadius(-5.0);
  EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
  EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
  EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
}

TEST(CircleTest, SetFerence) {
  Circle c;
  double ference = 31.4159265359;
  c.setFerence(ference);

  double expectedRadius = ference / (2.0 * PI);
  EXPECT_NEAR(c.getRadius(), expectedRadius, EPSILON);
  EXPECT_NEAR(c.getFerence(), ference, EPSILON);
  EXPECT_NEAR(c.getArea(), PI * expectedRadius * expectedRadius, EPSILON);

  c.setFerence(-10.0);
  EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
  EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
  EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
}

TEST(CircleTest, SetArea) {
  Circle c;
  double area = 78.53981634;
  c.setArea(area);

  double expectedRadius = std::sqrt(area / PI);
  EXPECT_NEAR(c.getRadius(), expectedRadius, EPSILON);
  EXPECT_NEAR(c.getArea(), area, EPSILON);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * expectedRadius, EPSILON);

  c.setArea(-20.0);
  EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
  EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
  EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
}

TEST(CircleTest, Consistency) {
  Circle c(7.0);

  c.setFerence(50.0);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * c.getRadius(), EPSILON);
  EXPECT_NEAR(c.getArea(), PI * c.getRadius() * c.getRadius(), EPSILON);

  c.setArea(200.0);
  EXPECT_NEAR(c.getArea(), PI * c.getRadius() * c.getRadius(), EPSILON);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * c.getRadius(), EPSILON);
}

TEST(CircleTest, EdgeCases) {
  Circle c;

  c.setRadius(0.0);
  EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
  EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
  EXPECT_NEAR(c.getArea(), 0.0, EPSILON);

  c.setRadius(1e-10);
  EXPECT_GT(c.getRadius(), 0.0);
  EXPECT_GT(c.getFerence(), 0.0);
  EXPECT_GT(c.getArea(), 0.0);
}

TEST(CircleTest, MultipleOperations) {
  Circle c;

  c.setRadius(5.0);
  double r1 = c.getRadius();
  double f1 = c.getFerence();

  c.setFerence(f1 + 10.0);
  double r2 = c.getRadius();
  EXPECT_GT(r2, r1);

  c.setArea(c.getArea() / 2.0);
  double r3 = c.getRadius();
  EXPECT_LT(r3, r2);
}

TEST(CircleTest, Precision) {
  Circle c;

  c.setRadius(123.456789);
  double originalRadius = c.getRadius();

  c.setFerence(c.getFerence());
  EXPECT_NEAR(c.getRadius(), originalRadius, EPSILON);

  c.setArea(c.getArea());
  EXPECT_NEAR(c.getRadius(), originalRadius, EPSILON);
}

TEST(CircleTest, LargeValues) {
  Circle c;

  c.setRadius(1e6);
  EXPECT_GT(c.getFerence(), 0.0);
  EXPECT_GT(c.getArea(), 0.0);

  c.setArea(1e12);
  EXPECT_GT(c.getRadius(), 0.0);
  EXPECT_GT(c.getFerence(), 0.0);
}

TEST(CircleTest, ConstGetters) {
  const Circle constCircle(5.0);
  EXPECT_NEAR(constCircle.getRadius(), 5.0, EPSILON);
  EXPECT_NEAR(constCircle.getFerence(), 2.0 * PI * 5.0, EPSILON);
}

TEST(CircleTest, TinyValues) {
  Circle tiny(1e-15);
  EXPECT_GT(tiny.getRadius(), 0.0);
  EXPECT_GT(tiny.getFerence(), 0.0);
  EXPECT_GT(tiny.getArea(), 0.0);
}

TEST(TasksTest, EarthRopeGap) {
  double gap = calculateEarthRopeGap();
  double expectedGap = 1.0 / (2.0 * PI);
  EXPECT_NEAR(gap, expectedGap, 1e-6);
  EXPECT_GT(gap, 0.15);
  EXPECT_LT(gap, 0.17);
}

TEST(TasksTest, PoolCosts) {
  PoolCosts costs = calculatePoolCosts();

  double expectedPathArea = PI * (16.0 - 9.0);
  double expectedConcreteCost = expectedPathArea * 1000.0;
  double expectedFenceLength = 2.0 * PI * 4.0;
  double expectedFenceCost = expectedFenceLength * 2000.0;

  EXPECT_NEAR(costs.concreteCost, expectedConcreteCost, 1e-6);
  EXPECT_NEAR(costs.fenceCost, expectedFenceCost, 1e-6);
  EXPECT_NEAR(costs.totalCost, expectedConcreteCost + expectedFenceCost, 1e-6);

  EXPECT_GT(costs.concreteCost, 20000.0);
  EXPECT_LT(costs.concreteCost, 23000.0);
  EXPECT_GT(costs.fenceCost, 50000.0);
  EXPECT_LT(costs.fenceCost, 51000.0);
  EXPECT_GT(costs.totalCost, 70000.0);
  EXPECT_LT(costs.totalCost, 74000.0);
}

TEST(CircleTest, NegativeValuesSetRadius) {
    Circle c(10.0);
    c.setRadius(-15.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
    EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
    EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
}

TEST(CircleTest, NegativeValuesSetFerence) {
    Circle c(5.0);
    c.setFerence(-25.0);
    EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
    EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
    EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
}

TEST(CircleTest, NegativeValuesSetArea) {
    Circle c(3.0);
    c.setArea(-50.0);
    EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
    EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
    EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
}

TEST(CircleTest, ZeroRadiusOperations) {
    Circle c(0.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
    EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
    EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
    
    c.setFerence(10.0);
    EXPECT_NEAR(c.getRadius(), 10.0 / (2.0 * PI), EPSILON);
}

TEST(CircleTest, ChainedOperations) {
    Circle c;
    c.setRadius(2.0);
    double r = c.getRadius();
    c.setFerence(2.0 * PI * r);
    c.setArea(PI * r * r);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 2.0, EPSILON);
    EXPECT_NEAR(c.getArea(), PI * 4.0, EPSILON);
}

TEST(CircleTest, RoundTripRadiusToFerence) {
    Circle c;
    double originalRadius = 8.5;
    c.setRadius(originalRadius);
    double ference = c.getFerence();
    c.setFerence(ference);
    EXPECT_NEAR(c.getRadius(), originalRadius, EPSILON);
}

TEST(CircleTest, RoundTripRadiusToArea) {
    Circle c;
    double originalRadius = 4.2;
    c.setRadius(originalRadius);
    double area = c.getArea();
    c.setArea(area);
    EXPECT_NEAR(c.getRadius(), originalRadius, EPSILON);
}

TEST(CircleTest, RoundTripFerenceToArea) {
    Circle c;
    c.setFerence(30.0);
    double area = c.getArea();
    Circle c2;
    c2.setArea(area);
    EXPECT_NEAR(c2.getFerence(), c.getFerence(), EPSILON);
}

TEST(TasksTest, EarthRopeGapPositive) {
    double gap = calculateEarthRopeGap();
    EXPECT_GT(gap, 0.0);
    EXPECT_NEAR(gap, 0.1591549, 1e-6);
}

TEST(TasksTest, EarthRopeGapFormula) {
    double expected = 1.0 / (2.0 * PI);  
    EXPECT_NEAR(calculateEarthRopeGap(), expected, 1e-9);
}

TEST(TasksTest, PoolCostsNonNegative) {
    PoolCosts costs = calculatePoolCosts();
    EXPECT_GE(costs.concreteCost, 0.0);
    EXPECT_GE(costs.fenceCost, 0.0);
    EXPECT_GE(costs.totalCost, 0.0);
}

TEST(TasksTest, PoolCostsConcreteVsFence) {
    PoolCosts costs = calculatePoolCosts();
    EXPECT_GT(costs.fenceCost, costs.concreteCost);
}

TEST(TasksTest, PoolCostsReasonableValues) {
    PoolCosts costs = calculatePoolCosts();
    EXPECT_GT(costs.totalCost, 70000.0);
    EXPECT_LT(costs.totalCost, 75000.0);
}

TEST(CircleTest, SetRadiusAfterNegativeValue) {
    Circle c(5.0);
    c.setRadius(-10.0);
    EXPECT_NEAR(c.getRadius(), 0.0, EPSILON);
    c.setRadius(7.0);
    EXPECT_NEAR(c.getRadius(), 7.0, EPSILON);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 7.0, EPSILON);
    EXPECT_NEAR(c.getArea(), PI * 49.0, EPSILON);
}

TEST(CircleTest, SetFerenceAfterNegativeValue) {
    Circle c(5.0);
    c.setFerence(-20.0);
    EXPECT_NEAR(c.getFerence(), 0.0, EPSILON);
    c.setFerence(40.0);
    double expectedRadius = 40.0 / (2.0 * PI);
    EXPECT_NEAR(c.getRadius(), expectedRadius, EPSILON);
    EXPECT_NEAR(c.getArea(), PI * expectedRadius * expectedRadius, EPSILON);
}

TEST(CircleTest, SetAreaAfterNegativeValue) {
    Circle c(5.0);
    c.setArea(-100.0);
    EXPECT_NEAR(c.getArea(), 0.0, EPSILON);
    c.setArea(100.0);
    double expectedRadius = std::sqrt(100.0 / PI);
    EXPECT_NEAR(c.getRadius(), expectedRadius, EPSILON);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * expectedRadius, EPSILON);
}

TEST(CircleTest, MultipleSetRadiusCalls) {
    Circle c;
    double radii[] = {1.0, 2.5, 0.0, 7.3, 100.0};
    for (double r : radii) {
        c.setRadius(r);
        EXPECT_NEAR(c.getRadius(), r, EPSILON);
        EXPECT_NEAR(c.getFerence(), 2.0 * PI * r, EPSILON);
        EXPECT_NEAR(c.getArea(), PI * r * r, EPSILON);
    }
}

TEST(CircleTest, MultipleSetFerenceCalls) {
    Circle c;
    double ferences[] = {10.0, 25.5, 0.0, 50.0, 200.0};
    for (double f : ferences) {
        c.setFerence(f);
        double expectedRadius = f / (2.0 * PI);
        EXPECT_NEAR(c.getRadius(), expectedRadius, EPSILON);
        EXPECT_NEAR(c.getFerence(), f, EPSILON);
        EXPECT_NEAR(c.getArea(), PI * expectedRadius * expectedRadius, EPSILON);
    }
}

TEST(CircleTest, MultipleSetAreaCalls) {
    Circle c;
    double areas[] = {10.0, 50.5, 0.0, 100.0, 500.0};
    for (double a : areas) {
        c.setArea(a);
        double expectedRadius = std::sqrt(a / PI);
        EXPECT_NEAR(c.getRadius(), expectedRadius, EPSILON);
        EXPECT_NEAR(c.getArea(), a, EPSILON);
        EXPECT_NEAR(c.getFerence(), 2.0 * PI * expectedRadius, EPSILON);
    }
}

TEST(CircleTest, VeryLargeRadius) {
    Circle c(1e10);
    EXPECT_NEAR(c.getRadius(), 1e10, EPSILON);
    EXPECT_NEAR(c.getFerence(), 2.0 * PI * 1e10, EPSILON);
    EXPECT_NEAR(c.getArea(), PI * 1e20, EPSILON);
}

TEST(CircleTest, VerySmallFerence) {
    Circle c;
    c.setFerence(1e-10);
    EXPECT_NEAR(c.getFerence(), 1e-10, EPSILON);
    EXPECT_NEAR(c.getRadius(), 1e-10 / (2.0 * PI), EPSILON);
    EXPECT_NEAR(c.getArea(), PI * std::pow(1e-10 / (2.0 * PI), 2), EPSILON);
}
