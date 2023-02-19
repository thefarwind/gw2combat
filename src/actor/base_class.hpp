#ifndef GW2COMBAT_ACTOR_BASE_CLASS_HPP
#define GW2COMBAT_ACTOR_BASE_CLASS_HPP

#include "common.hpp"

namespace gw2combat::actor {

enum class base_class_t : std::uint8_t
{
    INVALID,

    UNIVERSAL,
    GUARDIAN,
    RANGER,
};

NLOHMANN_JSON_SERIALIZE_ENUM(base_class_t,
                             {
                                 {base_class_t::INVALID, "Invalid"},

                                 {base_class_t::UNIVERSAL, "UNIVERSAL"},
                                 {base_class_t::UNIVERSAL, "universal"},

                                 {base_class_t::GUARDIAN, "GUARDIAN"},
                                 {base_class_t::GUARDIAN, "guardian"},

                                 {base_class_t::GUARDIAN, "RANGER"},
                                 {base_class_t::GUARDIAN, "ranger"},
                             })

}  // namespace gw2combat::actor

#endif  // GW2COMBAT_ACTOR_BASE_CLASS_HPP
