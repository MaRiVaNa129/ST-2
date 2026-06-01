// Copyright 2026 UNN-CS Team
#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>

#include "circle.h"
#include "tasks.h"

namespace {
constexpr double Pi = 3.14159265358979323846;
constexpr double Eps = 1e-9;
}

// CIRCLE TESTS

TEST(Circle, Constructor_SetsRadiusFerenceAndArea) {
  Circle c(3.0);

  EXPECT_NEAR(c.getRadius(), 3.0, Eps);
  EXPECT_NEAR(c.getFerence(), 2.0 * Pi * 3.0, Eps);
  EXPECT_NEAR(c.getArea(), Pi * 9.0, Eps);
}

TEST(Circle, Constructor_ThrowsForZeroRadius) {
  EXPECT_THROW(Circle(0.0), std::invalid_argument);
}

TEST(Circle, Constructor_ThrowsForNegativeRadius) {
  EXPECT_THROW(Circle(-5.0), std::invalid_argument);
}

TEST(Circle, SetRadius_RecalculatesFerenceAndArea) {
  Circle c(1.0);
  c.setRadius(10.0);

  EXPECT_NEAR(c.getRadius(), 10.0, Eps);
  EXPECT_NEAR(c.getFerence(), 2.0 * Pi * 10.0, Eps);
  EXPECT_NEAR(c.getArea(), Pi * 100.0, Eps);
}

TEST(Circle, SetRadius_ThrowsForZero) {
  Circle c(1.0);
  EXPECT_THROW(c.setRadius(0.0), std::invalid_argument);
}

TEST(Circle, SetRadius_ThrowsForNegative) {
  Circle c(1.0);
  EXPECT_THROW(c.setRadius(-0.1), std::invalid_argument);
}

TEST(Circle, SetFerence_RecalculatesRadiusAndArea) {
  Circle c(1.0);
  c.setFerence(2.0 * Pi * 4.0);

  EXPECT_NEAR(c.getRadius(), 4.0, Eps);
  EXPECT_NEAR(c.getFerence(), 2.0 * Pi * 4.0, Eps);
  EXPECT_NEAR(c.getArea(), 16.0 * Pi, Eps);
}

TEST(Circle, SetFerence_ThrowsForZero) {
  Circle c(1.0);
  EXPECT_THROW(c.setFerence(0.0), std::invalid_argument);
}

TEST(Circle, SetFerence_ThrowsForNegative) {
  Circle c(1.0);
  EXPECT_THROW(c.setFerence(-100.0), std::invalid_argument);
}

TEST(Circle, SetArea_RecalculatesRadiusAndFerence) {
  Circle c(1.0);
  c.setArea(25.0 * Pi);

  EXPECT_NEAR(c.getRadius(), 5.0, Eps);
  EXPECT_NEAR(c.getFerence(), 2.0 * Pi * 5.0, Eps);
  EXPECT_NEAR(c.getArea(), 25.0 * Pi, Eps);
}

TEST(Circle, SetArea_ThrowsForZero) {
  Circle c(1.0);
  EXPECT_THROW(c.setArea(0.0), std::invalid_argument);
}

TEST(Circle, SetArea_ThrowsForNegative) {
  Circle c(1.0);
  EXPECT_THROW(c.setArea(-50.0), std::invalid_argument);
}

TEST(Circle, ChainedUpdates_StayConsistent) {
  Circle c(2.0);
  c.setArea(4.0 * Pi);
  c.setFerence(2.0 * Pi * 3.0);
  c.setRadius(7.0);

  EXPECT_NEAR(c.getRadius(), 7.0, Eps);
  EXPECT_NEAR(c.getFerence(), 14.0 * Pi, Eps);
  EXPECT_NEAR(c.getArea(), 49.0 * Pi, Eps);
}

// EARTH TESTS

TEST(TasksEarth, GapForOneMeterRopeIsIndependentOfEarthRadius) {
  const double gap1 = getEarthRopeGap(6378.1, 1.0);
  const double gap2 = getEarthRopeGap(1000.0, 1.0);

  EXPECT_NEAR(gap1, gap2, Eps);
}

TEST(TasksEarth, GapForOneMeterRope_MatchesFormula) {
  const double expected = 1.0 / (2.0 * Pi);
  const double actual = getEarthRopeGap();

  EXPECT_NEAR(actual, expected, Eps);
}

TEST(TasksEarth, GapForTwoMetersRope_MatchesFormula) {
  const double expected = 2.0 / (2.0 * Pi);
  const double actual = getEarthRopeGap(6378.1, 2.0);

  EXPECT_NEAR(actual, expected, Eps);
}

TEST(TasksEarth, ThrowsForZeroEarthRadius) {
  EXPECT_THROW(getEarthRopeGap(0.0, 1.0), std::invalid_argument);
}

TEST(TasksEarth, ThrowsForNegativeAddedRope) {
  EXPECT_THROW(getEarthRopeGap(6378.1, -1.0), std::invalid_argument);
}

// POOL TESTS

TEST(TasksPool, DefaultValues_MatchManualCalculation) {
  const PoolCosts costs = calculatePoolCosts();

  const double outerArea = Pi * 16.0;
  const double innerArea = Pi * 9.0;
  const double expectedConcrete = (outerArea - innerArea) * 1000.0;
  const double expectedFence = (2.0 * Pi * 4.0) * 2000.0;
  const double expectedTotal = expectedConcrete + expectedFence;

  EXPECT_NEAR(costs.concreteCost, expectedConcrete, Eps);
  EXPECT_NEAR(costs.fenceCost, expectedFence, Eps);
  EXPECT_NEAR(costs.totalCost, expectedTotal, Eps);
}

TEST(TasksPool, CustomValues_AreCalculatedCorrectly) {
  const PoolCosts costs = calculatePoolCosts(2.0, 2.0, 500.0, 1000.0);

  const double expectedConcrete = (Pi * 16.0 - Pi * 4.0) * 500.0;
  const double expectedFence = (2.0 * Pi * 4.0) * 1000.0;
  const double expectedTotal = expectedConcrete + expectedFence;

  EXPECT_NEAR(costs.concreteCost, expectedConcrete, Eps);
  EXPECT_NEAR(costs.fenceCost, expectedFence, Eps);
  EXPECT_NEAR(costs.totalCost, expectedTotal, Eps);
}

TEST(TasksPool, ThrowsForZeroPoolRadius) {
  EXPECT_THROW(
      calculatePoolCosts(0.0, 1.0, 1000.0, 2000.0),
      std::invalid_argument);
}

TEST(TasksPool, ThrowsForNegativeTrackWidth) {
  EXPECT_THROW(
      calculatePoolCosts(3.0, -1.0, 1000.0, 2000.0),
      std::invalid_argument);
}

TEST(TasksPool, ThrowsForNegativeConcreteCost) {
  EXPECT_THROW(
      calculatePoolCosts(3.0, 1.0, -1000.0, 2000.0),
      std::invalid_argument);
}

TEST(TasksPool, ThrowsForNegativeFenceCost) {
  EXPECT_THROW(
      calculatePoolCosts(3.0, 1.0, 1000.0, -2000.0),
      std::invalid_argument);
}

TEST(TasksPool, TotalCostEqualsSumOfParts) {
  const PoolCosts costs = calculatePoolCosts(3.5, 0.5, 1200.0, 2500.0);
  EXPECT_NEAR(costs.totalCost, costs.concreteCost + costs.fenceCost, Eps);
}
