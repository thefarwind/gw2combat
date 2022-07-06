#include "system.hpp"

#include <numeric>

#include <spdlog/spdlog.h>

#include "gw2combat/component/condition/burning.hpp"
#include "gw2combat/component/condition_tick_status.hpp"
#include "gw2combat/component/effective_attributes.hpp"
#include "gw2combat/component/effective_incoming_damage.hpp"

namespace gw2combat::system {

void incoming_condition_damage_calculation(context& ctx) {
    ctx.registry.view<component::burning>().each([&](const entt::entity entity,
                                                     component::burning& burning) {
        double burning_damage_per_stack_per_second =
            131.0 * (double)burning.stacks.size() +
            0.155 * std::accumulate(burning.stacks.cbegin(),
                                    burning.stacks.cend(),
                                    0.0,
                                    [&](const double accumulated, const effect& next) {
                                        double source_condition_damage =
                                            ctx.registry
                                                .get<component::effective_attributes>(next.source)
                                                .condition_damage;
                                        return accumulated + source_condition_damage;
                                    });
        double incoming_condition_damage_for_tick =
            burning_damage_per_stack_per_second * (ctx.tick_rate / 1'000.0);
        burning.buffered_damage += incoming_condition_damage_for_tick;

        if (ctx.registry.get<component::condition_tick_status>(*singleton_entity)
                .apply_condition_damage) {
            auto& effective_incoming_damage =
                ctx.registry.get_or_emplace<component::effective_incoming_damage>(
                    entity, component::effective_incoming_damage{0});
            effective_incoming_damage.value += (unsigned int)std::round(burning.buffered_damage);

            spdlog::info("entity: {}, incoming condition damage: {}, effective incoming damage: {}",
                         static_cast<std::uint32_t>(entity),
                         burning.buffered_damage,
                         effective_incoming_damage.value);

            burning.buffered_damage = 0.0;
        }
    });
}

}  // namespace gw2combat::system
