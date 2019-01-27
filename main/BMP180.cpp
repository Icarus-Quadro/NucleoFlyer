#include <icarus/BMP180_impl.hpp>

#include "I2CBus.hpp"
#include <icarus/I2CRegisterBank.hpp>

template class icarus::BMP180<icarus::I2CRegisterBank<I2CBus>>;
