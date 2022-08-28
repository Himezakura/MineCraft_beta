#ifndef CHEATS_H
#define CHEATS_H

#include <3ds.h>
#include "csvc.h"
#include <vector>
#include <CTRPluginFramework.hpp>
#include "Helpers.hpp"
#include "Unicode.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;
	
	
	void jump_infinity(MenuEntry *entry);
	void jump_infinity_rom(MenuEntry *entry);
	void speed1(MenuEntry *entry);
	void speed2(MenuEntry *entry);
	void kantu(MenuEntry *entry);
	void hp_huan(MenuEntry *entry);
	void kuuhuku_huan(MenuEntry *entry);
	void hp_rom(MenuEntry *entry);
	void dameji_bairitu(MenuEntry *entry);
	void block_bairitu(MenuEntry *entry);
	void block_wanpan(MenuEntry *entry);
	void block_wanpan_turuhasi(MenuEntry *entry);
	void jikan_gyaku(MenuEntry *entry);
	void sekai_toumei(MenuEntry *entry);
	void jikan_henkou(MenuEntry *entry);
	void ame_yamu(MenuEntry *entry);
	void kaminari(MenuEntry *entry);
	void kiri_color(MenuEntry *entry);
	void item_slot_siroi(MenuEntry *entry);
	void item_slot_suuji(MenuEntry *entry);
	void item_slot_color(MenuEntry *entry);
	void item_slot_ookisa(MenuEntry *entry);
	void player_toumei(MenuEntry *entry);
	void player_hakkou(MenuEntry *entry);
	void motion(MenuEntry *entry);
	void c_kando(MenuEntry *entry);
	void rakka0(MenuEntry *entry);
	void siten_yura(MenuEntry *entry);
	void asi_particle(MenuEntry *entry);
	void asi_particle_ookisa(MenuEntry *entry);
	void asi_particle_jikan(MenuEntry *entry);
	void siten_idou(MenuEntry *entry);

}
#endif
