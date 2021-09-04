#include "ppt.h"

template <typename T>
struct Object {};

template <typename SourceTestType>
struct TestType {
  auto Lift() -> TestType<Object<SourceTestType>> {
    return TestType<Object<SourceTestType>>{};
  }
};

int main() {
  auto t = TestType<int>().Lift().Lift();
  PPT(t);
  return 0;
}