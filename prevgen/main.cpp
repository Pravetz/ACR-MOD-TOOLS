#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cctype>
#include <algorithm>

using std::cin, std::cout, std::endl, std::ofstream, std::ifstream, std::unordered_map, std::vector, std::string;

enum TOKEN_TYPES {
	NULLTOK = 0,
	IDENTIFIER,
	BREAK
};

struct token {
	char type;
	string text;
};

enum MODIFIER_TYPE {
	Constant = 0,
	Additive = 1,
	Multiplicative = 2,
	Unknown
};

static inline string upper_str(string str){
	for(size_t i = 0; i < str.length(); i++){
		str[i] = std::toupper(str[i]);
	}
	return str;
}

unordered_map<string, char> modifiers = {
	{"army_tradition", Additive},
	{"army_tradition_decay", Additive},
	{"army_tradition_from_battle", Multiplicative},
	{"yearly_army_professionalism", Multiplicative},
	{"drill_gain_modifier", Multiplicative},
	{"drill_decay_modifier", Multiplicative},
	{"infantry_cost", Multiplicative},
	{"infantry_power", Multiplicative},
	{"infantry_fire", Additive},
	{"infantry_shock", Additive},
	{"cavalry_cost", Multiplicative},
	{"cavalry_power", Multiplicative},
	{"cavalry_fire", Additive},
	{"cavalry_shock", Additive},
	{"artillery_cost", Multiplicative},
	{"artillery_power", Multiplicative},
	{"artillery_fire", Additive},
	{"artillery_shock", Additive},
	{"cav_to_inf_ratio", Additive},
	{"cavalry_flanking", Multiplicative},
	{"artillery_levels_available_vs_fort", Additive},
	{"artillery_level_modifier", Multiplicative},
	{"backrow_artillery_damage", Multiplicative},
	{"discipline", Multiplicative},
	{"land_morale", Multiplicative},
	{"land_morale_constant", Additive},
	{"movement_speed", Multiplicative},
	{"fire_damage", Multiplicative},
	{"fire_damage_received", Multiplicative},
	{"shock_damage", Multiplicative},
	{"shock_damage_received", Multiplicative},
	{"morale_damage", Multiplicative},
	{"morale_damage_received", Multiplicative},
	{"recover_army_morale_speed", Multiplicative},
	{"reserves_organisation", Multiplicative},
	{"land_attrition", Multiplicative},
	{"reinforce_cost_modifier", Multiplicative},
	{"no_cost_for_reinforcing", Constant},
	{"reinforce_speed", Multiplicative},
	{"manpower_recovery_speed", Multiplicative},
	{"global_manpower", Additive},
	{"global_manpower_modifier", Multiplicative},
	{"global_regiment_cost", Multiplicative},
	{"global_regiment_recruit_speed", Multiplicative},
	{"global_supply_limit_modifier", Additive},
	{"land_forcelimit", Additive},
	{"land_forcelimit_modifier", Multiplicative},
	{"land_maintenance_modifier", Multiplicative},
	{"possible_condottieri", Multiplicative},
	{"hostile_attrition", Additive},
	{"max_hostile_attrition", Additive},
	{"siege_ability", Multiplicative},
	{"artillery_barrage_cost", Multiplicative},
	{"assault_fort_cost_modifier", Multiplicative},
	{"assault_fort_ability", Multiplicative},
	{"defensiveness", Multiplicative},
	{"garrison_size", Multiplicative},
	{"global_garrison_growth", Multiplicative},
	{"garrison_damage", Multiplicative},
	{"fort_maintenance_modifier", Multiplicative},
	{"rival_border_fort_maintenance", Multiplicative},
	{"war_exhaustion", Additive},
	{"war_exhaustion_cost", Multiplicative},
	{"leader_land_fire", Additive},
	{"leader_land_manuever", Additive},
	{"leader_land_shock", Additive},
	{"leader_siege", Additive},
	{"max_general_fire", Additive},
	{"max_general_maneuver", Additive},
	{"max_general_shock", Additive},
	{"max_general_siege", Additive},
	{"general_cost", Multiplicative},
	{"free_leader_pool", Additive},
	{"free_land_leader_pool", Additive},
	{"free_navy_leader_pool", Additive},
	{"raze_power_gain", Multiplicative},
	{"loot_amount", Multiplicative},
	{"available_province_loot", Multiplicative},
	{"prestige_from_land", Multiplicative},
	{"war_taxes_cost_modifier", Multiplicative},
	{"leader_cost", Multiplicative},
	{"may_recruit_female_generals", Constant},
	{"manpower_in_true_faith_provinces", Multiplicative},
	{"regiment_manpower_usage", Multiplicative},
	{"military_tactics", Additive},
	{"capped_by_forcelimit", Constant},
	{"global_attacker_dice_roll_bonus", Additive},
	{"global_defender_dice_roll_bonus", Additive},
	{"own_territory_dice_roll_bonus", Additive},
	{"manpower_in_accepted_culture_provinces", Multiplicative},
	{"manpower_in_culture_group_provinces", Multiplicative},
	{"manpower_in_own_culture_provinces", Multiplicative},
	{"may_build_supply_depot", Constant},
	{"may_refill_garrison", Constant},
	{"may_return_manpower_on_disband", Constant},
	{"attack_bonus_in_capital_terrain", Additive},
	{"can_bypass_forts", Constant},
	{"force_march_free", Constant},
	{"enable_forced_march", Constant},
	{"warscore_from_battles_modifier", Multiplicative},
	{"mercenary_cost", Multiplicative},
	{"merc_maintenance_modifier", Multiplicative},
	{"mercenary_discipline", Multiplicative},
	{"mercenary_manpower", Multiplicative},
	{"merc_leader_army_tradition", Multiplicative},
	{"allow_mercenary_drill", Constant},
	{"merc_independent_from_trade_range", Constant},
	{"allow_mercenaries_to_split", Constant},
	{"special_unit_forcelimit", Multiplicative},
	{"special_unit_cost_modifier", Multiplicative},
	{"special_unit_manpower_cost_modifier", Multiplicative},
	{"has_marines", Constant},
	{"allowed_marine_fraction", Multiplicative},
	{"has_banners", Constant},
	{"amount_of_banners", Multiplicative},
	{"can_recruit_cawa", Constant},
	{"amount_of_cawa", Multiplicative},
	{"cawa_cost_modifier", Multiplicative},
	{"has_carolean", Constant},
	{"amount_of_carolean", Multiplicative},
	{"can_recruit_hussars", Constant},
	{"amount_of_hussars", Additive},
	{"hussars_cost_modifier", Multiplicative},
	{"can_recruit_janissaries", Constant},
	{"janissary_cost_modifier", Multiplicative},
	{"allow_janissaries_from_own_faith", Constant},
	{"can_recruit_cossacks", Constant},
	{"allowed_cossack_fraction", Multiplicative},
	{"can_recruit_rajputs", Constant},
	{"allowed_rajput_fraction", Multiplicative},
	{"can_recruit_revolutionary_guards", Constant},
	{"allowed_rev_guard_fraction", Multiplicative},
	{"has_streltsy", Constant},
	{"allowed_streltsy_fraction", Multiplicative},
	{"amount_of_streltsy", Additive},
	{"has_tercio", Constant},
	{"allowed_tercio_fraction", Multiplicative},
	{"amount_of_tercio", Additive},
	{"has_samurai", Constant},
	{"allowed_samurai_fraction", Multiplicative},
	{"amount_of_samurai", Additive},
	{"has_musketeer", Constant},
	{"allowed_musketeer_fraction", Multiplicative},
	{"amount_of_musketeers", Additive},
	{"has_mamluks", Constant},
	{"allowed_mamluks_fraction", Multiplicative},
	{"amount_of_mamluks", Additive},
	{"has_qizilbash", Constant},
	{"allowed_qizilbash_fraction", Multiplicative},
	{"amount_of_qizilbash", Additive},
	{"navy_tradition", Additive},
	{"navy_tradition_decay", Additive},
	{"naval_tradition_from_battle", Multiplicative},
	{"naval_tradition_from_trade", Multiplicative},
	{"heavy_ship_cost", Multiplicative},
	{"heavy_ship_power", Multiplicative},
	{"light_ship_cost", Multiplicative},
	{"light_ship_power", Multiplicative},
	{"galley_cost", Multiplicative},
	{"galley_power", Multiplicative},
	{"transport_cost", Multiplicative},
	{"transport_power", Multiplicative},
	{"global_ship_cost", Multiplicative},
	{"global_ship_recruit_speed", Multiplicative},
	{"global_ship_repair", Multiplicative},
	{"naval_forcelimit", Additive},
	{"naval_forcelimit_modifier", Multiplicative},
	{"naval_maintenance_modifier", Multiplicative},
	{"global_sailors", Additive},
	{"global_sailors_modifier", Multiplicative},
	{"sailor_maintenance_modifer", Multiplicative},
	{"sailors_recovery_speed", Multiplicative},
	{"blockade_efficiency", Multiplicative},
	{"siege_blockade_progress", Additive},
	{"capture_ship_chance", Additive},
	{"global_naval_engagement_modifier", Multiplicative},
	{"global_naval_engagement", Additive},
	{"naval_attrition", Multiplicative},
	{"naval_morale", Multiplicative},
	{"naval_morale_constant", Additive},
	{"naval_morale_damage", Multiplicative},
	{"naval_morale_damage_received", Multiplicative},
	{"ship_durability", Multiplicative},
	{"sunk_ship_morale_hit_recieved", Multiplicative},
	{"recover_navy_morale_speed", Multiplicative},
	{"prestige_from_naval", Multiplicative},
	{"leader_naval_fire", Additive},
	{"leader_naval_manuever", Additive},
	{"leader_naval_shock", Additive},
	{"max_admiral_fire", Additive},
	{"max_admiral_maneuver", Additive},
	{"max_admiral_shock", Additive},
	{"max_admiral_siege", Additive},
	{"own_coast_naval_combat_bonus", Multiplicative},
	{"admiral_cost", Multiplicative},
	{"global_naval_barrage_cost", Multiplicative},
	{"flagship_cost", Multiplicative},
	{"disengagement_chance", Multiplicative},
	{"transport_attrition", Multiplicative},
	{"landing_penalty", Additive},
	{"regiment_disembark_speed", Multiplicative},
	{"may_perform_slave_raid", Constant},
	{"may_perform_slave_raid_on_same_religion", Constant},
	{"coast_raid_range", Additive},
	{"sea_repair", Constant},
	{"movement_speed_in_fleet_modifier", Additive},
	{"max_flagships", Additive},
	{"number_of_cannons", Additive},
	{"number_of_cannons_modifier", Multiplicative},
	{"heavy_ship_number_of_cannons_modifier", Multiplicative},
	{"light_ship_number_of_cannons_modifier", Multiplicative},
	{"galley_number_of_cannons_modifier", Multiplicative},
	{"transport_number_of_cannons_modifier", Multiplicative},
	{"hull_size", Additive},
	{"hull_size_modifier", Multiplicative},
	{"heavy_ship_hull_size_modifier", Multiplicative},
	{"light_ship_hull_size_modifier", Multiplicative},
	{"galley_hull_size_modifier", Multiplicative},
	{"transport_hull_size_modifier", Multiplicative},
	{"engagement_cost", Additive},
	{"engagement_cost_modifier", Multiplicative},
	{"ship_trade_power", Additive},
	{"ship_trade_power_modifier", Multiplicative},
	{"can_transport_units", Constant},
	{"admiral_skill_gain_modifier", Additive},
	{"flagship_durability", Multiplicative},
	{"flagship_morale", Multiplicative},
	{"flagship_naval_engagement_modifier", Additive},
	{"movement_speed_onto_off_boat_modifier", Multiplicative},
	{"flagship_landing_penalty", Multiplicative},
	{"number_of_cannons_flagship_modifier", Multiplicative},
	{"number_of_cannons_flagship", Additive},
	{"naval_maintenance_flagship_modifier", Multiplicative},
	{"trade_power_in_fleet_modifier", Multiplicative},
	{"morale_in_fleet_modifier", Multiplicative},
	{"blockade_impact_on_siege_in_fleet_modifier", Multiplicative},
	{"exploration_mission_range_in_fleet_modifier", Additive},
	{"barrage_cost_in_fleet_modifier", Multiplicative},
	{"naval_attrition_in_fleet_modifier", Multiplicative},
	{"privateering_efficiency_in_fleet_modifier", Multiplicative},
	{"prestige_from_battles_in_fleet_modifier", Multiplicative},
	{"naval_tradition_in_fleet_modifier", Multiplicative},
	{"cannons_for_hunting_pirates_in_fleet", Multiplicative},
	{"has_geobukseon", Constant},
	{"allowed_geobukseon_fraction", Multiplicative},
	{"amount_of_geobukseon", Additive},
	{"has_galleass", Constant},
	{"allowed_galleass_fraction", Multiplicative},
	{"amount_of_galleass", Additive},
	{"has_voc_indiamen", Constant},
	{"allowed_voc_indiamen_fraction", Multiplicative},
	{"amount_of_voc_indiamen", Additive},
	{"has_man_of_war", Constant},
	{"allowed_man_of_war_fraction", Multiplicative},
	{"amount_of_man_of_war", Additive},
	{"has_galleon", Constant},
	{"allowed_galleon_fraction", Multiplicative},
	{"amount_of_galleon", Additive},
	{"has_caravel", Constant},
	{"allowed_caravel_fraction", Multiplicative},
	{"amount_of_caravel", Additive},
	{"diplomats", Additive},
	{"diplomatic_reputation", Additive},
	{"diplomatic_upkeep", Additive},
	{"envoy_travel_time", Multiplicative},
	{"improve_relation_modifier", Multiplicative},
	{"ae_impact", Multiplicative},
	{"diplomatic_annexation_cost", Multiplicative},
	{"province_warscore_cost", Multiplicative},
	{"unjustified_demands", Multiplicative},
	{"rival_change_cost", Multiplicative},
	{"justify_trade_conflict_cost", Multiplicative},
	{"stability_cost_to_declare_war", Additive},
	{"accept_vassalization_reasons", Additive},
	{"transfer_trade_power_reasons", Additive},
	{"monthly_federation_favor_growth", Additive},
	{"monthly_favor_modifier", Multiplicative},
	{"cb_on_overseas", Constant},
	{"cb_on_primitives", Constant},
	{"idea_claim_colonies", Constant},
	{"cb_on_government_enemies", Constant},
	{"cb_on_religious_enemies", Constant},
	{"reduced_stab_impacts", Constant},
	{"can_fabricate_for_vassals", Constant},
	{"global_tax_income", Additive},
	{"global_tax_modifier", Multiplicative},
	{"production_efficiency", Multiplicative},
	{"state_maintenance_modifier", Multiplicative},
	{"inflation_action_cost", Multiplicative},
	{"may_not_reduce_inflation", Constant},
	{"inflation_reduction", Additive},
	{"monthly_gold_inflation_modifier", Multiplicative},
	{"gold_depletion_chance_modifier", Multiplicative},
	{"interest", Additive},
	{"can_not_build_buildings", Constant},
	{"development_cost", Multiplicative},
	{"development_cost_in_primary_culture", Multiplicative},
	{"development_cost_modifier", Multiplicative},
	{"tribal_development_growth", Additive},
	{"add_tribal_land_cost", Multiplicative},
	{"settle_cost", Multiplicative},
	{"global_allowed_num_of_buildings", Additive},
	{"global_allowed_num_of_manufactories", Additive},
	{"build_cost", Multiplicative},
	{"build_time", Multiplicative},
	{"great_project_upgrade_cost", Multiplicative},
	{"great_project_upgrade_time", Multiplicative},
	{"global_monthly_devastation", Additive},
	{"global_prosperity_growth", Additive},
	{"administrative_efficiency", Multiplicative},
	{"free_concentrate_development", Constant},
	{"expand_infrastructure_cost_modifier", Multiplicative},
	{"centralize_state_cost", Multiplicative},
	{"core_creation", Multiplicative},
	{"core_decay_on_your_own", Multiplicative},
	{"enemy_core_creation", Multiplicative},
	{"ignore_coring_distance", Constant},
	{"technology_cost", Multiplicative},
	{"idea_cost", Multiplicative},
	{"embracement_cost", Multiplicative},
	{"global_institution_spread", Multiplicative},
	{"institution_spread_from_true_faith", Multiplicative},
	{"native_advancement_cost", Multiplicative},
	{"all_power_cost", Multiplicative},
	{"innovativeness_gain", Multiplicative},
	{"yearly_innovativeness", Additive},
	{"free_adm_policy", Additive},
	{"free_dip_policy", Additive},
	{"free_mil_policy", Additive},
	{"possible_adm_policy", Additive},
	{"possible_dip_policy", Additive},
	{"possible_mil_policy", Additive},
	{"possible_policy", Additive},
	{"free_policy", Additive},
	{"country_admin_power", Additive},
	{"country_diplomatic_power", Additive},
	{"country_military_power", Additive},
	{"prestige", Additive},
	{"prestige_decay", Additive},
	{"monthly_splendor", Additive},
	{"yearly_corruption", Additive},
	{"advisor_cost", Multiplicative},
	{"same_culture_advisor_cost", Multiplicative},
	{"same_religion_advisor_cost", Multiplicative},
	{"advisor_pool", Additive},
	{"female_advisor_chance", Multiplicative},
	{"heir_chance", Multiplicative},
	{"monthly_heir_claim_increase", Additive},
	{"monthly_heir_claim_increase_modifier", Multiplicative},
	{"block_introduce_heir", Constant},
	{"adm_advisor_cost", Multiplicative},
	{"dip_advisor_cost", Multiplicative},
	{"mil_advisor_cost", Multiplicative},
	{"monthly_support_heir_gain", Multiplicative},
	{"power_projection_from_insults", Multiplicative},
	{"monarch_lifespan", Multiplicative},
	{"local_heir_adm", Additive},
	{"local_heir_dip", Additive},
	{"local_heir_mil", Additive},
	{"national_focus_years", Additive},
	{"yearly_absolutism", Additive},
	{"max_absolutism", Additive},
	{"max_absolutism_effect", Multiplicative},
	{"legitimacy", Additive},
	{"republican_tradition", Additive},
	{"devotion", Additive},
	{"horde_unity", Additive},
	{"meritocracy", Additive},
	{"yearly_government_power", Additive},
	{"imperial_mandate", Additive},
	{"election_cycle", Additive},
	{"candidate_random_bonus", Additive},
	{"reelection_cost", Multiplicative},
	{"max_terms", Additive},
	{"governing_capacity", Additive},
	{"governing_capacity_modifier", Multiplicative},
	{"governing_cost", Multiplicative},
	{"state_governing_cost", Multiplicative},
	{"territories_governing_cost", Multiplicative},
	{"trade_company_governing_cost", Multiplicative},
	{"state_governing_cost_increase", Additive},
	{"expand_administration_cost", Multiplicative},
	{"yearly_revolutionary_zeal", Additive},
	{"max_revolutionary_zeal", Additive},
	{"reform_progress_growth", Multiplicative},
	{"monthly_reform_progress", Additive},
	{"monthly_reform_progress_modifier", Multiplicative},
	{"move_capital_cost_modifier", Multiplicative},
	{"can_revoke_parliament_seats", Constant},
	{"parliament_backing_chance", Multiplicative},
	{"parliament_effect_duration", Additive},
	{"parliament_debate_duration", Additive},
	{"parliament_chance_of_decision", Multiplicative},
	{"num_of_parliament_issues", Additive},
	{"max_possible_parliament_seats", Additive},
	{"all_estate_influence_modifier", Multiplicative},
	{"all_estate_loyalty_equilibrium", Multiplicative},
	{"all_estate_possible_privileges", Additive},
	{"allow_free_estate_privilege_revocation", Constant},
	{"loyalty_change_on_revoked", Multiplicative},
	{"estate_interaction_cooldown_modifier", Multiplicative},
	{"imperial_authority", Multiplicative},
	{"imperial_authority_value", Additive},
	{"free_city_imperial_authority", Additive},
	{"reasons_to_elect", Additive},
	{"imperial_mercenary_cost", Multiplicative},
	{"max_free_cities", Additive},
	{"max_electors", Additive},
	{"legitimate_subject_elector", Additive},
	{"manpower_against_imperial_enemies", Additive},
	{"imperial_reform_catholic_approval", Additive},
	{"culture_conversion_cost", Multiplicative},
	{"culture_conversion_time", Multiplicative},
	{"num_accepted_cultures", Additive},
	{"promote_culture_cost", Multiplicative},
	{"relation_with_same_culture", Additive},
	{"relation_with_same_culture_group", Additive},
	{"relation_with_accepted_culture", Additive},
	{"relation_with_other_culture", Additive},
	{"can_not_declare_war", Constant},
	{"global_unrest", Additive},
	{"stability_cost_modifier", Multiplicative},
	{"global_autonomy", Additive},
	{"min_autonomy", Constant},
	{"autonomy_change_time", Multiplicative},
	{"harsh_treatment_cost", Multiplicative},
	{"global_rebel_suppression_efficiency", Multiplicative},
	{"years_of_nationalism", Additive},
	{"min_autonomy_in_territories", Additive},
	{"unrest_catholic_provinces", Additive},
	{"no_stability_loss_on_monarch_death", Constant},
	{"overextension_impact_modifier", Multiplicative},
	{"vassal_forcelimit_bonus", Multiplicative},
	{"vassal_naval_forcelimit_bonus", Multiplicative},
	{"vassal_manpower_bonus", Multiplicative},
	{"vassal_sailors_bonus", Multiplicative},
	{"vassal_income", Multiplicative},
	{"overlord_naval_forcelimit", Additive},
	{"overlord_naval_forcelimit_modifier", Multiplicative},
	{"can_transfer_vassal_wargoal", Constant},
	{"liberty_desire", Additive},
	{"liberty_desire_from_subject_development", Multiplicative},
	{"reduced_liberty_desire", Additive},
	{"reduced_liberty_desire_on_same_continent", Additive},
	{"reduced_liberty_desire_on_other_continent", Additive},
	{"allow_client_states", Constant},
	{"colonial_type_change_cost_modifier", Multiplicative},
	{"colonial_subject_type_upgrade_cost_modifier", Multiplicative},
	{"years_to_integrate_personal_union", Additive},
	{"chance_to_inherit", Multiplicative},
	{"monarch_power_tribute", Additive},
	{"tributary_conversion_cost_modifier", Multiplicative},
	{"annexation_relations_impact", Multiplicative},
	{"spy_offence", Multiplicative},
	{"global_spy_defence", Multiplicative},
	{"fabricate_claims_cost", Multiplicative},
	{"claim_duration", Multiplicative},
	{"can_chain_claim", Constant},
	{"discovered_relations_impact", Multiplicative},
	{"rebel_support_efficiency", Multiplicative},
	{"can_claim_states", Constant},
	{"no_claim_cost_increasement", Constant},
	{"spy_action_cost_modifier", Multiplicative},
	{"global_missionary_strength", Additive},
	{"global_heretic_missionary_strength", Additive},
	{"global_heathen_missionary_strength", Additive},
	{"can_not_build_missionaries", Constant},
	{"may_not_convert_territories", Constant},
	{"missionaries", Additive},
	{"missionary_maintenance_cost", Multiplicative},
	{"religious_unity", Additive},
	{"tolerance_own", Additive},
	{"tolerance_heretic", Additive},
	{"tolerance_heathen", Additive},
	{"tolerance_of_heretics_capacity", Additive},
	{"tolerance_of_heathens_capacity", Additive},
	{"papal_influence", Additive},
	{"papal_influence_from_cardinals", Multiplicative},
	{"appoint_cardinal_cost", Multiplicative},
	{"curia_treasury_contribution", Multiplicative},
	{"curia_powers_cost", Multiplicative},
	{"monthly_church_power", Additive},
	{"church_power_modifier", Multiplicative},
	{"monthly_fervor_increase", Additive},
	{"yearly_patriarch_authority", Additive},
	{"monthly_piety", Additive},
	{"monthly_piety_accelerator", Additive},
	{"harmonization_speed", Multiplicative},
	{"yearly_harmony", Additive},
	{"monthly_karma", Additive},
	{"monthly_karma_accelerator", Additive},
	{"yearly_karma_decay", Multiplicative},
	{"yearly_doom_reduction", Additive},
	{"yearly_authority", Additive},
	{"enforce_religion_cost", Multiplicative},
	{"prestige_per_development_from_conversion", Additive},
	{"warscore_cost_vs_other_religion", Multiplicative},
	{"establish_order_cost", Multiplicative},
	{"global_religious_conversion_resistance", Multiplicative},
	{"relation_with_same_religion", Additive},
	{"relation_with_heretics", Additive},
	{"relation_with_heathens", Additive},
	{"reverse_relation_with_same_religion", Additive},
	{"reverse_relation_with_heretic_religion", Additive},
	{"reverse_relation_with_heathen_religion", Additive},
	{"no_religion_penalty", Constant},
	{"extra_manpower_at_religious_war", Constant},
	{"can_not_build_colonies", Constant},
	{"colonists", Additive},
	{"colonist_placement_chance", Additive},
	{"global_colonial_growth", Additive},
	{"colony_cost_modifier", Multiplicative},
	{"range", Multiplicative},
	{"native_uprising_chance", Multiplicative},
	{"native_assimilation", Multiplicative},
	{"migration_cost", Multiplicative},
	{"global_tariffs", Multiplicative},
	{"treasure_fleet_income", Multiplicative},
	{"expel_minorities_cost", Multiplicative},
	{"may_explore", Constant},
	{"auto_explore_adjacent_to_colony", Constant},
	{"may_establish_frontier", Constant},
	{"free_maintenance_on_expl_conq", Constant},
	{"colony_development_boost", Additive},
	{"caravan_power", Multiplicative},
	{"can_not_send_merchants", Constant},
	{"merchants", Additive},
	{"placed_merchant_power", Additive},
	{"placed_merchant_power_modifier", Multiplicative},
	{"global_trade_power", Multiplicative},
	{"global_foreign_trade_power", Multiplicative},
	{"global_own_trade_power", Multiplicative},
	{"global_prov_trade_power_modifier", Multiplicative},
	{"global_trade_goods_size_modifier", Multiplicative},
	{"global_trade_goods_size", Additive},
	{"trade_efficiency", Multiplicative},
	{"trade_range_modifier", Multiplicative},
	{"trade_steering", Multiplicative},
	{"global_ship_trade_power", Multiplicative},
	{"privateer_efficiency", Multiplicative},
	{"embargo_efficiency", Multiplicative},
	{"ship_power_propagation", Multiplicative},
	{"center_of_trade_upgrade_cost", Multiplicative},
	{"trade_company_investment_cost", Multiplicative},
	{"mercantilism_cost", Multiplicative},
	{"reduced_trade_penalty_on_non_main_tradenode", Multiplicative},
	{"max_attrition", Additive},
	{"attrition", Additive},
	{"local_hostile_attrition", Additive},
	{"local_attacker_dice_roll_bonus", Additive},
	{"local_defender_dice_roll_bonus", Additive},
	{"fort_level", Additive},
	{"garrison_growth", Multiplicative},
	{"local_defensiveness", Multiplicative},
	{"local_fort_maintenance_modifier", Multiplicative},
	{"local_garrison_size", Multiplicative},
	{"local_garrison_damage", Multiplicative},
	{"local_assault_fort_cost_modifier", Multiplicative},
	{"local_assault_fort_ability", Multiplicative},
	{"local_friendly_movement_speed", Multiplicative},
	{"local_hostile_movement_speed", Multiplicative},
	{"local_manpower", Additive},
	{"local_manpower_modifier", Multiplicative},
	{"local_regiment_cost", Multiplicative},
	{"regiment_recruit_speed", Multiplicative},
	{"supply_limit", Additive},
	{"supply_limit_modifier", Multiplicative},
	{"local_own_coast_naval_combat_bonus", Additive},
	{"local_has_banners", Constant},
	{"local_has_carolean", Constant},
	{"local_has_streltsy", Constant},
	{"local_has_tercio", Constant},
	{"local_has_musketeers", Constant},
	{"local_has_samurai", Constant},
	{"local_has_mamluks", Constant},
	{"local_has_qizilbash", Constant},
	{"local_naval_engagement_modifier", Multiplicative},
	{"local_sailors", Additive},
	{"local_sailors_modifier", Multiplicative},
	{"local_ship_cost", Multiplicative},
	{"local_ship_repair", Multiplicative},
	{"ship_recruit_speed", Multiplicative},
	{"blockade_force_required", Multiplicative},
	{"hostile_disembark_speed", Multiplicative},
	{"hostile_fleet_attrition", Multiplicative},
	{"block_slave_raid", Constant},
	{"local_has_geobukseon", Constant},
	{"local_has_man_of_war", Constant},
	{"local_has_galleon", Constant},
	{"local_has_galleass", Constant},
	{"local_has_caravel", Constant},
	{"local_has_voc_indiamen", Constant},
	{"local_warscore_cost_modifier", Multiplicative},
	{"inflation_reduction_local", Additive},
	{"local_state_maintenance_modifier", Multiplicative},
	{"local_build_cost", Multiplicative},
	{"local_build_time", Multiplicative},
	{"local_great_project_upgrade_cost", Multiplicative},
	{"local_great_project_upgrade_time", Multiplicative},
	{"local_monthly_devastation", Additive},
	{"local_prosperity_growth", Additive},
	{"local_production_efficiency", Multiplicative},
	{"local_tax_modifier", Multiplicative},
	{"tax_income", Additive},
	{"allowed_num_of_buildings", Additive},
	{"allowed_num_of_manufactories", Additive},
	{"local_development_cost", Multiplicative},
	{"local_development_cost_modifier", Multiplicative},
	{"local_gold_depletion_chance_modifier", Multiplicative},
	{"local_institution_spread", Multiplicative},
	{"local_core_creation", Multiplicative},
	{"local_governing_cost", Multiplicative},
	{"statewide_governing_cost", Multiplicative},
	{"local_governing_cost_increase", Additive},
	{"local_centralize_state_cost", Multiplicative},
	{"institution_growth", Additive},
	{"local_culture_conversion_cost", Multiplicative},
	{"local_culture_conversion_time", Multiplicative},
	{"local_unrest", Additive},
	{"local_autonomy", Additive},
	{"local_years_of_nationalism", Additive},
	{"min_local_autonomy", Additive},
	{"local_missionary_strength", Additive},
	{"local_religious_unity_contribution", Additive},
	{"local_missionary_maintenance_cost", Additive},
	{"local_religious_conversion_resistance", Additive},
	{"local_tolerance_of_heretics", Additive},
	{"local_tolerance_of_heathens", Additive},
	{"local_colonial_growth", Additive},
	{"local_colonist_placement_chance", Additive},
	{"local_colony_cost_modifier", Multiplicative},
	{"province_trade_power_modifier", Multiplicative},
	{"province_trade_power_value", Additive},
	{"trade_goods_size_modifier", Multiplicative},
	{"trade_goods_size", Additive},
	{"trade_value_modifier", Multiplicative},
	{"trade_value", Additive},
	{"local_center_of_trade_upgrade_cost", Multiplicative},
	{"base_deputy_support", Multiplicative}
};

vector<token> parse_file(const vector<char> &chars){
	vector<token> tokens;
	bool comment = false;
	token current = {};
	
	for(const auto &c : chars){
		switch(c){
			case '#':
				comment = true;
				if(current.type != NULLTOK){
					tokens.push_back(current);
					current = {};
				}
			break;
			case '\n':
				comment = false;
			case ' ':
			case '=':
			case '\t':
			case '\v':
			case '{':
			case '[':
			case ']':
			case '(':
			case ')':
				if(current.type != NULLTOK){
					tokens.push_back(current);
					current = {};
				}
			break;
			case '}':
				if(current.type != NULLTOK){
					tokens.push_back(current);
					current = {};
				}
				tokens.push_back(token{ .type = BREAK, .text = "}" });
			break;
			default:{
				if(comment){
					continue;
				}
				current.type = IDENTIFIER;
				current.text.push_back(c);
			}break;
		}
	}
	
	return tokens;
}

std::vector<std::string> split_string(const std::string &str, const std::string &separators){
	size_t last_seppos = 0;
	size_t seppos = 0;
	std::vector<std::string> strings;
	bool last_pos_was_separator = false;
	
	while((seppos = str.find_first_of(separators, seppos)) != std::string::npos){
		if(seppos - last_seppos - (last_seppos > 0) > 0){
			last_pos_was_separator = (separators.find_first_of(str[last_seppos]) != std::string::npos);
			strings.push_back(str.substr(last_seppos + last_pos_was_separator, seppos - last_seppos - last_pos_was_separator));
		}
		last_seppos = seppos;
		seppos++;
	}
	if(last_seppos + 1 < str.length()){
		strings.push_back(str.substr(last_seppos + 1));
	}
	if(!strings.empty() && !strings[strings.size() - 1].length()){
		strings.pop_back();
	}
	
	return strings;
}

unordered_map<string, string> ldlang(const string &path){
	ifstream file;
	unordered_map<string, string> keys;
	
	file.open(path);
	if(file){
		string getl;
		while(std::getline(file, getl)){
			vector<string> tokens = split_string(getl, ":");
			if(tokens.size() < 2){
				continue;
			}
			keys[tokens[0]] = tokens[1];
		}
	}
	file.close();
	
	return keys;
}

vector<char> read_file(const string &path){
	vector<char> raw_src;
	
	ifstream _file;
	_file.open(path.c_str(), std::fstream::binary);
	if(_file){
		_file.seekg(0, _file.end);
		size_t srclen = _file.tellg();
		_file.seekg(0, _file.beg);
		raw_src.resize(srclen);
		_file.clear();
		_file.read(raw_src.data(), srclen);
	}
	else{
		raw_src.clear();
		cout<<"File in path \'"<<path<<"\' doesn't exist."<<endl;
	}
	
	
	return raw_src;
}

static inline string get_localized_target_name(const unordered_map<string, string> &localizations, const string &key, bool extended_search){
	if(!extended_search){
		return localizations.find(key) != localizations.end() ? localizations.at(key) : key;
	}
	std::string key_upper = upper_str(key);
	std::string key_upper_may = "MAY_" + key_upper;
	std::string key_upper_modmay = "MODIFIER_MAY_" + key_upper;

	size_t pos_mod = key_upper.find("_MODIFIER");
	std::string key_upper_no_last_modifier = (pos_mod != std::string::npos) ? key_upper.substr(0, pos_mod) : key_upper;

	size_t pos_speed = key_upper.find("_SPEED");
	std::string key_upper_no_speed = (pos_speed != std::string::npos) ? key_upper.substr(0, pos_speed) : key_upper;
	
	size_t pos_is = key_upper.find("_RECEIVED");
	std::string key_upper_invalid_spelling = key_upper;
	if(pos_is != std::string::npos){
		key_upper_invalid_spelling.replace(pos_is, pos_is + 9, "_RECIEVED");
	}
	
	std::string key_upper_modifier_invs = "MODIFIER_" + key_upper_invalid_spelling;
	std::string key_upper_modifier = "MODIFIER_" + key_upper;
	std::string key_upper_first_modifier = "MODIFIER_" + key_upper_no_last_modifier;
	std::string key_upper_number_of = "NUMBER_OF_" + key_upper;

	std::string key_upper_no_glob = key_upper;
	std::string key_upper_l = key_upper;
	if (key_upper.compare(0, 5, "LOCAL") == 0) {
		key_upper_l.replace(0, 5, "L");
	}
	if (key_upper.compare(0, 7, "GLOBAL_") == 0) {
		key_upper_no_glob.replace(0, 7, "");
	}
	
	std::string key_upper_no_S = key_upper;
	key_upper_no_S.erase(std::remove(key_upper_no_S.begin(), key_upper_no_S.end(), 'S'), key_upper_no_S.end());
	
	const std::string* search_keys[] = {
		&key_upper, &key_upper_may, &key_upper_modmay, &key_upper_no_last_modifier,
		&key_upper_no_speed, &key_upper_modifier, &key_upper_first_modifier,
		&key_upper_number_of, &key_upper_l, &key_upper_no_S, &key_upper_no_glob, &key_upper_invalid_spelling, &key_upper_modifier_invs
	};
	
	std::cout << "Search:\n";
	for (const auto* search_key : search_keys) {
		std::cout << "\t" << *search_key << '\n';
		auto it = localizations.find(*search_key);
		if (it != localizations.end()) {
			std::cout << "found " << it->second << '\n';
			return it->second;
		}
	}

	return key;
}

static inline char get_modifier_type(const string &key){
	return modifiers.find(key) != modifiers.end() ? modifiers.at(key) : Unknown;
}

static inline bool is_number(const string &str){
	return str.find_first_not_of("0123456789.+-") == std::string::npos;
}

static inline bool is_eu4_boolean(const string &str){
	return str == "yes" || str == "no";
}

static inline string convert_to_numerical_or_bool(const string &str){
	if(is_eu4_boolean(str)){
		return "";
	}
	double value = std::stod(str);
	char buf[32] = {};
	snprintf(buf, 32, "%+.2lf", value);
	return string(buf);
}

static inline string convert_to_pcnt(const string &str){
	double value = std::stod(str);
	value *= 100.0;
	char buf[32] = {};
	snprintf(buf, 32, "%+.1lf%%", value);
	return string(buf);
}

static inline string interpret_arg(const string &arg, char arg_type){
	switch(arg_type){
		case Additive:			return ": §O" + convert_to_numerical_or_bool(arg) + "§!";
		case Constant:			return (is_eu4_boolean(arg) ? "§O" : ": §O") + convert_to_numerical_or_bool(arg) + "§!";
		case Multiplicative:	return ": §O" + convert_to_pcnt(arg) + "§!";
	}
	
	return "";
}

void generate_modifier_previews(unordered_map<string, string> &localizations, unordered_map<string, string> &loc_targets, const vector<char> &src, const string &respath) {
	vector<token> tokens = parse_file(src);
	ofstream resf;
	bool met_modifier = false;
	string result = "";
	string current_effect = "";
	
	resf.open(respath);
	if(resf){
		for(size_t i = 0; i < tokens.size(); i++){
			switch(tokens[i].type){
				case IDENTIFIER:{
					if(!met_modifier){
						met_modifier = true;
						result += tokens[i].text + "_preview:0 \"When active, §Y" + get_localized_target_name(loc_targets, tokens[i].text, false) + "§! has following effects:\\n";
					}
					else {
						if(current_effect.empty()){
							if(modifiers.find(tokens[i].text) == modifiers.end()){
								cout<<"Unknown effect \'"<<tokens[i].text<<"\' skipped\\n";
								i++;
								continue;
							}
							current_effect = tokens[i].text;
							result += get_localized_target_name(localizations, current_effect, true);
						}
						else{
							result += interpret_arg(tokens[i].text, get_modifier_type(current_effect)) + "\\n";
							current_effect = "";
						}
					}
				}break;
				case BREAK:{
					met_modifier = false;
					resf << ' ' << result << "\"\n";
					result = "";
					current_effect = "";
				}break;
			}
		}
		resf.close();
	}
}

int main(void){
	string cmd = "";
	unordered_map<string, string> loc;
	unordered_map<string, string> loc_targets;
	vector<char> src;
	
	while(cmd != "!exit")	{
		std::getline(cin, cmd);
		
		if(cmd == "!ldlang"){
			cout<< "Localized modifiers path: "; std::getline(cin, cmd);
			loc = ldlang(cmd);
			for(const auto &l : loc){
				cout<<l.first<<'\t'<<l.second<<endl;
			}
		}
		if(cmd == "!preview"){
			cout<< "Localized target modifiers path: "; std::getline(cin, cmd);
			loc_targets = ldlang(cmd);
			cout<< "Target file path: "; std::getline(cin, cmd);
			src = read_file(cmd);
			cout<< "Result path: "; std::getline(cin, cmd);
			generate_modifier_previews(loc, loc_targets, src, cmd);
		}
	}
	return 0;
}