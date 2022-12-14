#include <3ds.h>
#include "csvc.h"
#include "cheats.hpp"

#include <vector>

namespace CTRPluginFramework
{
    // これは、amiiboをスキャンするときにタッチスクリーンを無効にするNFCにパッチを適用し、ctrpfが使用されないようにします。
    static void    ToggleTouchscreenForceOn(void)
    {
        static u32 original = 0;
        static u32 *patchAddress = nullptr;

        if (patchAddress && original)
        {
            *patchAddress = original;
            return;
        }

        static const std::vector<u32> pattern =
        {
            0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
            0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
            0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003
        };

        Result  res;
        Handle  processHandle;
        s64     textTotalSize = 0;
        s64     startAddress = 0;
        u32 *   found;

        if (R_FAILED(svcOpenProcess(&processHandle, 16)))
            return;

        svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
        svcGetProcessInfo(&startAddress, processHandle, 0x10005);
        if(R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalSize)))
            goto exit;

        found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalSize, pattern);

        if (found != nullptr)
        {
            original = found[13];
            patchAddress = (u32 *)PA_FROM_VA((found + 13));
            found[13] = 0xE1A00000;
        }

        svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
	exit:
        svcCloseHandle(processHandle);
    }

    // この関数は、メインの前とゲームの開始前に呼び出されます
    // コード編集を安全に行うのに便利です
    void    PatchProcess(FwkSettings &settings)
    {
        ToggleTouchscreenForceOn();
    }

    // この関数は、プロセスが終了したときに呼び出されます
    // 設定の保存、パッチの取り消し、またはクリーンアップに役立ちます
    void    OnProcessExit(void)
    {
        ToggleTouchscreenForceOn();
    }

	// メニュー
	// new MenuEntry("チート名", cheats.cppのチート名), 通常
	// new MenuEntry("チート名", nullptr, cheats.cppのチート名),　歯車
    void    InitMenu(PluginMenu &menu)
    {
       menu += new MenuFolder(Color::Lime<< "移動系", "",
		{

			new MenuEntry("無限ジャンプ",jump_infinity,"movとブロックの差が2ブロック以内の場合はジャンプ出来なくなる"),
			new MenuEntry("無限ジャンプ",nullptr,jump_infinity_rom),
			new MenuEntry("スピードハック1",nullptr,speed1),
			new MenuEntry("スピードハック2",nullptr,speed2),
			new MenuEntry("貫通系",nullptr,kantu),
		});
		
		
		menu += new MenuFolder(Color::Lime<< "ブロック系","",
		{
			new MenuEntry("ブロックドロップ倍率変更",nullptr,block_bairitu),
			new MenuEntry("ブロックワンパン(拳)",nullptr,block_wanpan),
			new MenuEntry("ブロックワンパン(アイテム)",nullptr,block_wanpan_turuhasi),
		});
		
		
		menu += new MenuFolder(Color::Lime<< "アイテム系","",
		{
			new MenuEntry("アイテムスロット白くなる",nullptr,item_slot_siroi),
			new MenuEntry("スロットアイテムの個数文字の配置変更",nullptr,item_slot_suuji),
			new MenuEntry("スロットアイテムの着色（黒）",nullptr,item_slot_color),
			new MenuEntry("スロットアイテムの大きさ変更",nullptr,item_slot_ookisa),
		});
		
		
		menu += new MenuFolder(Color::Lime<< "世界系","",
		{
			new MenuEntry("世界透化",nullptr,sekai_toumei),
			new MenuEntry("時間変更",nullptr,jikan_henkou),
			new MenuEntry("時間逆変更",nullptr,jikan_gyaku),
			new MenuEntry("雨止む",nullptr,ame_yamu),
			new MenuEntry("雷降らす(強制)/act固定",nullptr,kaminari),
			new MenuEntry("霧の色変更",nullptr,kiri_color),
		});


		menu += new MenuFolder(Color::Lime<< "視点系","",
		{
			new MenuEntry("cスティック感度変更",nullptr,c_kando),
			new MenuEntry("走る時の視点感度",nullptr,siten_yura),
		});

		
		
		menu += new MenuFolder(Color::Lime<< "プレイヤー系", "",
		{
			new MenuEntry("HP無限",hp_huan),
			new MenuEntry("空腹度無限",kuuhuku_huan),
			new MenuEntry("HP無限",nullptr,hp_rom),
			new MenuEntry("落下ダメージ食らわない",nullptr,rakka0),
			new MenuEntry("ダメージ倍率変更",nullptr,dameji_bairitu),
			new MenuEntry("プレイヤーモーション",nullptr,motion),
			new MenuEntry("プレイヤー,全mob透化",nullptr,player_toumei),
			new MenuEntry("プレイヤー,全mob発光",nullptr,player_hakkou),
			new MenuEntry("足元のパーティクル変更",nullptr,asi_particle),
			new MenuEntry("足元のパーティクル大きさ変更",nullptr,asi_particle_ookisa),
			new MenuEntry("足元のパーティクル残時間変更",nullptr,asi_particle_jikan),
			new MenuEntry("Cheat Name Unknown",scr),

		});
			
    }

    int     main(void)
    {
	// Pluginのバージョンと説明
        PluginMenu *menu = new PluginMenu("MineCraft_beta", 1, 8, 0,
                                            "作成者 : 姫桜大輝\nコード提供者 : rruu\n                    らいそんちょー");

        // メニューをフレームイベントと同期します
        menu->SynchronizeWithFrame(true);

	// 起動時に「Plugin ready!」を表示する(false)か非表示(true)か
	menu->ShowWelcomeMessage(false);

        // 「Plugin Leady!」と別に文字を表示
        OSD::Notify(Color(0,191,255) << "MineCraft3gx Loaded!");

        // メニューエントリとフォルダを初期化する
        InitMenu(*menu);

        // 起動メニューとメインループ
        menu->Run();

        delete menu;

        // Pluginを終了します
        return (0);
    }
}
