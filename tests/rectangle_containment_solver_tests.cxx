#include <algorithm>

#include "gtest/gtest.h"

#include "rectangle_containment_solver.hxx"
#include "rectangle.hxx"
#include "rectangle_position.hxx"

using namespace packing;

TEST(RectangleContainmentSolver, SiteExample)
{
  const std::vector<Rectangle> input = {
    Rectangle(8, 8),
    Rectangle(4, 3),
    Rectangle(4, 3)
  };

  std::vector<RectanglePosition> expectedResult = {
    RectanglePosition(0,0),
    RectanglePosition(8,0),
    RectanglePosition(8,3)
  };

  auto result = RectangleContainmentSolver(input, BoundingBox(11, 8)).compute();

  EXPECT_EQ(expectedResult.size(), result.size());

  // Check that each element in result is present in expectedResult
  for(auto position: result) {
    EXPECT_TRUE(std::find(expectedResult.begin(),
                          expectedResult.end(),
                          position) != expectedResult.end())
      << "position x=" << position.getX() << ", y=" << position.getY() << " not expected";
  }
}

TEST(RectangleContainmentSolver, SiteExampleBoundingBoxTooSmall)
{
  const std::vector<Rectangle> input = {
    Rectangle(8, 8),
    Rectangle(4, 3),
    Rectangle(4, 3)
  };

  auto result = RectangleContainmentSolver(input, BoundingBox(10, 8)).compute();

  EXPECT_TRUE(result.empty());
}

TEST(RectangleContainmentSolver, Square10)
{
  std::vector<Rectangle> input;
  for(int i = 1; i <= 10; i++) {
    input.push_back(Rectangle(i, i));
  }

  // Bouding box one size too small
  auto result = RectangleContainmentSolver(input, BoundingBox(26, 15)).compute();

  EXPECT_TRUE(result.empty());

  result = RectangleContainmentSolver(input, BoundingBox(27, 15)).compute();

  EXPECT_FALSE(result.empty());
}

TEST(RectangleContainmentSolver, Rectangle10_tooSmall)
{
  std::vector<Rectangle> input;
  for(int i = 0; i < 10; i++) {
    input.push_back(Rectangle(i + 1, i));
  }

  // Bouding box one size too small
  auto result = RectangleContainmentSolver(input, BoundingBox(26, 16)).compute();

  EXPECT_TRUE(result.empty());
}

TEST(RectangleContainmentSolver, Rectangle10)
{
  std::vector<Rectangle> input;
  for(int i = 0; i < 10; i++) {
    input.push_back(Rectangle(i + 1, i));
  }

  auto result = RectangleContainmentSolver(input, BoundingBox(26, 17)).compute();

  EXPECT_FALSE(result.empty());
}