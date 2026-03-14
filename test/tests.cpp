// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include <cmath>
#include "circle.h"
#include "tasks.h"

const double PI = 3.141592653589793;
const double EPSILON = 1e-10;

TEST(CircleTest, Constructor)
{
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

TEST(CircleTest, SetRadius)
{
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

TEST(CircleTest, SetFerence)
{
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

TEST(CircleTest, SetArea)
{
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

TEST(CircleTest, Consistency)
{
  Circle c(7.0);

  c.setFerence(50.0);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * c.getRadius(), EPSILON);
  EXPECT_NEAR(c.getArea(), PI * c.getRadius() * c.getRadius(), EPSILON);

  c.setArea(200.0);
  EXPECT_NEAR(c.getArea(), PI * c.getRadius() * c.getRadius(), EPSILON);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * c.getRadius(), EPSILON);
}

TEST(CircleTest, EdgeCases)
{
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

TEST(CircleTest, MultipleOperations)
{
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

TEST(CircleTest, Precision)
{
  Circle c;

  c.setRadius(123.456789);
  double originalRadius = c.getRadius();

  c.setFerence(c.getFerence());
  EXPECT_NEAR(c.getRadius(), originalRadius, EPSILON);

  c.setArea(c.getArea());
  EXPECT_NEAR(c.getRadius(), originalRadius, EPSILON);
}

TEST(CircleTest, LargeValues)
{
  Circle c;

  c.setRadius(1e6);
  EXPECT_GT(c.getFerence(), 0.0);
  EXPECT_GT(c.getArea(), 0.0);

  c.setArea(1e12);
  EXPECT_GT(c.getRadius(), 0.0);
  EXPECT_GT(c.getFerence(), 0.0);
}

TEST(CircleTest, ConstGetters)
{
  const Circle constCircle(5.0);
  EXPECT_NEAR(constCircle.getRadius(), 5.0, EPSILON);
  EXPECT_NEAR(constCircle.getFerence(), 2.0 * PI * 5.0, EPSILON);
}

TEST(CircleTest, TinyValues)
{
  Circle tiny(1e-15);
  EXPECT_GT(tiny.getRadius(), 0.0);
  EXPECT_GT(tiny.getFerence(), 0.0);
  EXPECT_GT(tiny.getArea(), 0.0);
}

TEST(TasksTest, EarthRopeGap)
{
  double gap = calculateEarthRopeGap();
  double expectedGap = 1.0 / (2.0 * PI);
  EXPECT_NEAR(gap, expectedGap, 1e-6);
  EXPECT_GT(gap, 0.15);
  EXPECT_LT(gap, 0.17);
}

TEST(TasksTest, PoolCosts)
{
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