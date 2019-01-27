#include <icarus/AK8963_impl.hpp>

#include "I2CBus.hpp"
#include "MbedWait.hpp"
#include <icarus/I2CRegisterBank.hpp>

template class icarus::AK8963<MbedWait, icarus::I2CRegisterBank<I2CBus>>;
