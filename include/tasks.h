// Copyright 2022 UNN-CS
#ifndef INCLUDE_TASKS_H_
#define INCLUDE_TASKS_H_

struct PoolCosts
{
  double concreteCost;
  double fenceCost;
  double totalCost;
};

double calculateEarthRopeGap();
PoolCosts calculatePoolCosts();

#endif // INCLUDE_TASKS_H_