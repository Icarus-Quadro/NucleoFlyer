#include <icarus/MPU9255_impl.hpp>

#include "I2CBus.hpp"
#include <icarus/I2CRegisterBank.hpp>

template class icarus::MPU9255<icarus::I2CRegisterBank<I2CBus>>;
