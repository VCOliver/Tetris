#pragma once

#include <vector>

#include "components/renderComponents.hpp"

using Matrix = std::vector<std::vector<IRenderComponent>>;

class Tetrion {
    Matrix matrix;
};