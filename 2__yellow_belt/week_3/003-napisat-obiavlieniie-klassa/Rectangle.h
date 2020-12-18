//
// Created by Addmin on 11.12.2020.
//

#pragma once

// <cstdlib>
// <iostream>
//
// <algorithm>
// <deque>
// <iterator>
// <map>
// <numeric>
// <set>
// <sstream>
// <string>
// <tuple>
// <utility>
// <vector>
//
// <iomanip>
// <fstream>
//
// <type_traits>
//
// <numeric>
// <limits>
//
// <cassert>
// <random>

class Rectangle {
 public:
  Rectangle(int width, int height);
  
  int GetArea() const;
  
  int GetPerimeter() const;
  
  int GetWidth() const;
  
  int GetHeight() const;
 
 private:
  int width_, height_;
};
