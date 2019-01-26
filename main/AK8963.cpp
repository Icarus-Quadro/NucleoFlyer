#include <icarus/AK8963_impl.hpp>

#include "I2CBus.hpp"
#include <icarus/I2CRegisterBank.hpp>

template class icarus::AK8963<icarus::I2CRegisterBank<I2CBus>>;
