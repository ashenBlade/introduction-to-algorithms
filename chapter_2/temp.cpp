#include <iostream>
#include <vector>

int main() {
  std::vector<long> vec = std::vector<long>(2);
  vec.push_back(1);
  vec.push_back(2);
  for (const auto& value: vec) {
    std::cout << value << " ";
  }
  return 1;
}
