// Copyright 2022 UNN-CS
#include <cmath>
#include "circle.h"
#include "tasks.h"

double calculateEarthRopeGap() {
  const double EARTH_RADIUS_M = 6378100.0;
  Circle earth(EARTH_RADIUS_M);
  double originalRopeLength = earth.getFerence();
  double newRopeLength = originalRopeLength + 1.0;
  Circle newCircle;
  newCircle.setFerence(newRopeLength);
  return newCircle.getRadius() - EARTH_RADIUS_M;
}

PoolCosts calculatePoolCosts() {
  const double POOL_RADIUS = 3.0;
  const double PATH_WIDTH = 1.0;
  const double CONCRETE_PRICE = 1000.0;
  const double FENCE_PRICE = 2000.0;

  Circle pool(POOL_RADIUS);
  Circle poolWithPath(POOL_RADIUS + PATH_WIDTH);

  double pathArea = poolWithPath.getArea() - pool.getArea();
  double fenceLength = poolWithPath.getFerence();

  PoolCosts costs;
  costs.concreteCost = pathArea * CONCRETE_PRICE;
  costs.fenceCost = fenceLength * FENCE_PRICE;
  costs.totalCost = costs.concreteCost + costs.fenceCost;

  return costs;
}
