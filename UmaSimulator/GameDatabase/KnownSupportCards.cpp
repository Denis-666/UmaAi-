#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "GameDatabase.h"
#include "../Game/Game.h"

using json = nlohmann::json;
using namespace std;

unordered_map<int, SupportCard> GameDatabase::AllCards;
unordered_map<int, SupportCard> GameDatabase::DBCards;

void GameDatabase::loadCards(const string& dir)
{
    try
    {
        for (auto entry : filesystem::directory_iterator(dir + "/"))
        {
            //cout << entry.path() << endl;
            if (entry.path().extension() == ".json")
            {
                try
                {
                    ifstream ifs(entry.path());
                    stringstream ss;
                    ss << ifs.rdbuf();
                    ifs.close();
                    json j = json::parse(ss.str(), nullptr, true, true);

                    SupportCard jdata[5];

                    for (int x = 0; x < 5; ++x) {
                        jdata[x].load_from_json(j, x);
                    }

                    cout << "载入支援卡 #" << jdata[4].cardName << " --- " << jdata[4].cardID << endl;
                    if (GameDatabase::AllCards.count(jdata[4].cardID) > 0)
                        cout << "错误：重复支援卡 #" << jdata[4].cardName << " --- " << jdata[4].cardID << endl;
                    else {
                        for (int x = 0; x < 5; ++x) 
                            GameDatabase::AllCards[jdata[x].cardID] = jdata[x];
                    }
                        
                }
                catch (exception& e)
                {
                    cout << "支援卡信息JSON出错: " << entry.path() << endl << e.what() << endl;
                }
            }
        }
        cout << "共载入 " << GameDatabase::AllCards.size() << " 个支援卡数据" << endl;
    }
    catch (exception& e)
    {
        cout << "读取支援卡信息出错: " << endl << e.what() << endl;
    }
    catch (...)
    {
        cout << "读取支援卡信息出错：未知错误" << endl;
    }
}

void GameDatabase::loadDBCards(const string& pathname)
{
    try
    {
        ifstream ifs(pathname);
        stringstream ss;
        ss << ifs.rdbuf();
        ifs.close();
        json j = json::parse(ss.str(), nullptr, true, true);

        SupportCard jdata;
        for (auto & it : j.items()) 
        {


            for (int x = 0; x < 5; ++x) {
                SupportCard jdata;
                jdata.load_from_json(it.value(),x);
                if (GameDatabase::AllCards.count(jdata.cardID) > 0) continue;

                GameDatabase::AllCards[jdata.cardID] = jdata;

            }
            
        }
        cout << "共载入 " << GameDatabase::AllCards.size() << " 支援卡元数据" << endl;
    }
    catch (exception& e)
    {
        cout << "读取支援卡信息出错: " << endl << e.what() << endl;
    }
    catch (...)
    {
        cout << "读取支援卡信息出错：未知错误" << endl;
    }
}

CardTrainingEffect SupportCard::getCardEffect(const Game& game, int atTrain, int jiBan,int effectFactor) const
{
    CardTrainingEffect effect =
    {
      youQingBasic,
      ganJingBasic,
      xunLianBasic,
      {bonusBasic[0],bonusBasic[1],bonusBasic[2],bonusBasic[3],bonusBasic[4],bonusBasic[5]},
      wizVitalBonusBasic,
      failRateDrop,
      vitalCostDrop
    };



    bool isShining = true;//是否闪彩
    if (cardType < 5)//速耐力根智卡
    {
        if (jiBan < 80)isShining = false;
        if (cardType != atTrain)isShining = false;
    }
    else if (cardType == 5)//神团
    {
        if (!game.venusCardIsQingRe)
            isShining = false;
    }
    else std::cout << "未知卡";

    if (game.venusIsWisdomActive && game.venusAvailableWisdom == 3)//黄女神
        isShining = true;

    if (!isShining)
    {
        effect.youQing = 0;
    }
    if (!isShining || atTrain != 4)
        effect.vitalBonus = 0;


    int cardSpecialEffectId = cardID / 10;


    //接下来是各种固有
    //1.神团
    if (cardSpecialEffectId == 30137)
    {
        if (jiBan < 100)
        {
            if (isShining)
                effect.youQing = 20;
            effect.ganJing = 0;
            effect.bonus[5] = 0;
        }
    }
    //2.高峰
    //为了简化，视为初始训练加成是4%，第一年逐渐增大到20%，也就是第n个回合4+n*(2/3)%
    else if (cardSpecialEffectId == 30134)
    {
        if (game.turn < 24)
            effect.xunLian = 4 + 0.6666667 * game.turn;
    }
    //3.美妙
    else if (cardSpecialEffectId == 30010)
    {
        //啥都没有
    }
    //4.根乌拉拉
    else if (cardSpecialEffectId == 30019)
    {
        //啥都没有
    }
    //5.根风神
    else if (cardSpecialEffectId == 30011)
    {
        //啥都没有
    }
    //6.水司机
    else if (cardSpecialEffectId ==30107)
    {

        int traininglevel = game.getTrainingLevel(atTrain);
        effect.xunLian = 5 + traininglevel * 5;
        if (effect.xunLian > 25)effect.xunLian = 25;
    }
    //7.根凯斯
    else if (cardSpecialEffectId == 30130)
    {
        if (jiBan < 80)
        {
            effect.bonus[2] = 0;
        }
    }
    //8.根皇帝
    else if (cardSpecialEffectId == 30037)
    {
        if (jiBan < 80)
        {
            effect.bonus[0] = 0;
        }
    }
    //9.根善信
    else if (cardSpecialEffectId == 30027)
    {
        //啥都没有
    }
    //10.速宝穴
    else if (cardSpecialEffectId == 30147)
    {
        if (jiBan < 100)
        {
            effect.bonus[0] = 0;
        }
    }
    //11.耐海湾
    else if (cardSpecialEffectId == 30016)
    {
        //啥都没有
    }
    //12.智好歌剧
    else if (cardSpecialEffectId == 30152)
    {
        if (jiBan < 80)
        {
            effect.bonus[0] = 0;
        }
    }
    //13.根黄金城
    else if (cardSpecialEffectId == 30153)
    {
        if (jiBan < 100)
        {
            effect.bonus[3] = 0;
        }
    }
    //14.智波旁
    else if (cardSpecialEffectId == 30141)
    {
        //啥都没有
    }
    //15.耐狄杜斯
    else if (cardSpecialEffectId == 30099)
    {
        int totalJiBan = 0;
        for (int i = 0; i < 6; i++)
            totalJiBan += game.cardJiBan[i];
        effect.xunLian = totalJiBan / 30;
    }
    //速子
    else if (cardSpecialEffectId == 30101) {
        if (jiBan < 100)
        {
            effect.youQing = 22;
        }
    }
    //22，耐桂冠
    else if (cardSpecialEffectId == 30142)
    {
      if (game.turn < 24)
        effect.bonus[1] = 1;
      else if (game.turn < 48)
        effect.bonus[1] = 2;
      else
        effect.bonus[1] = 3;
    }
    //23力白仁
    else if (cardSpecialEffectId == 30123)
    {
      int traininglevel = game.getTrainingLevel(atTrain);
      effect.xunLian = 5 + traininglevel * 5;
      if (effect.xunLian > 25)effect.xunLian = 25;
    }
    //24力重炮
    else if (cardSpecialEffectId == 30151)
    {
        if (jiBan < 100)
        {
            effect.xunLian = 0;
        }
    }
    //25力内恰
    else if (cardSpecialEffectId == 30138)
    {
      if (jiBan < 100)
      {
        effect.bonus[2] = 0;
      }
    }
    //28根涡轮
    else if (cardSpecialEffectId == 30112)
    {
      //以后再想办法
    }
    //29根进王
    else if (cardSpecialEffectId == 30083)
    {
      if (jiBan < 80 || atTrain == 3)
        effect.xunLian = 0;
    }
    //30根青竹
    else if (cardSpecialEffectId == 30094)
    {
      if (effect.youQing > 0)
      {
        float extraBonus = 5 + (100 - game.vital) / 7.0;
        if (extraBonus > 15)extraBonus = 15;
        if (extraBonus < 5)extraBonus = 5; // std::cout << effect.youQing << " ";

        effect.youQing = 120 * (1 + 0.01 * extraBonus) - 100;

      }

    }
    //也问
    else if (cardSpecialEffectId == 30126)
    {
        if (jiBan < 80)
        {

            effect.bonus[5] = 0;
        }
    }
    //耐特
    else if (cardSpecialEffectId == 30127)
    {
        if (isShining)
        {
            effect.ganJing = 60;
        }
    }
    //根特
    else if (cardSpecialEffectId == 47)
    {
        //null
    }
    //速尔丹
    else if (cardSpecialEffectId == 30119)
    {
        if (jiBan < 80)
        {
            effect.bonus[2] = 0;
        }
    }
    // 皇团
    else if (cardSpecialEffectId == 30067) {

        if (jiBan < 80)
            effect.bonus[5] = 0;

    }
    // 红宝
    else if (cardSpecialEffectId == 30114) {
        if (jiBan < 80)
            effect.bonus[2] = 0;
    }
    // 福来
    else if (cardSpecialEffectId == 30078) {
        effect.failRateDrop += 10;
    }
    // 绿帽
    else if (cardSpecialEffectId == 30021) {
        effect.failRateDrop += 7;
        effect.vitalCostDrop += 4;
    }
    // 智茶座
    else if (cardSpecialEffectId == 30157) {
      if (jiBan < 100)
      {
        effect.bonus[4] = 0;
        effect.bonus[5] = 0;
      }
    }
    else
    {
      //  std::cout << "未知卡";
    }

    return effect;
}
