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

                    SupportCard jdata;
                    jdata.load_from_json(j);
                    cout << "����֧Ԯ�� #" << jdata.cardName<<" --- "<<jdata.cardID << endl;
                    if (GameDatabase::AllCards.count(jdata.cardID) > 0)
                        cout << "�����ظ�֧Ԯ�� #" << jdata.cardName << " --- " << jdata.cardID << endl;
                    else
                        GameDatabase::AllCards[jdata.cardID] = jdata;
                }
                catch (exception& e)
                {
                    cout << "֧Ԯ����ϢJSON����: " << entry.path() << endl << e.what() << endl;
                }
            }
        }
        cout << "������ " << GameDatabase::AllCards.size() << " ��֧Ԯ������" << endl;
    }
    catch (exception& e)
    {
        cout << "��ȡ֧Ԯ����Ϣ����: " << endl << e.what() << endl;
    }
    catch (...)
    {
        cout << "��ȡ֧Ԯ����Ϣ����δ֪����" << endl;
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
            SupportCard jdata;
            jdata.load_from_json(it.value());
            GameDatabase::DBCards[jdata.cardID] = jdata;
        }
        cout << "������ " << GameDatabase::DBCards.size() << " ֧Ԯ��Ԫ����" << endl;
    }
    catch (exception& e)
    {
        cout << "��ȡ֧Ԯ����Ϣ����: " << endl << e.what() << endl;
    }
    catch (...)
    {
        cout << "��ȡ֧Ԯ����Ϣ����δ֪����" << endl;
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
      wizVitalBonusBasic
    };



    bool isShining = true;//�Ƿ�����
    if (cardType < 5)//���������ǿ�
    {
        if (jiBan < 80)isShining = false;
        if (cardType != atTrain)isShining = false;
    }
    else if (cardType == 5)//����
    {
        if (!game.venusCardIsQingRe)
            isShining = false;
    }
    else std::cout << "δ֪��";

    if (game.venusIsWisdomActive && game.venusAvailableWisdom == 3)//��Ů��
        isShining = true;

    if (!isShining)
    {
        effect.youQing = 0;
    }
    if (!isShining || atTrain != 4)
        effect.vitalBonus = 0;

    //�������Ǹ��ֹ���
    //1.����
    if (cardID == 30137)
    {
        if (jiBan < 100)
        {
            if (isShining)
                effect.youQing = 20;
            effect.ganJing = 0;
            effect.bonus[5] = 0;
        }
    }
    //2.�߷�
    //Ϊ�˼򻯣���Ϊ��ʼѵ���ӳ���4%����һ��������20%��Ҳ���ǵ�n���غ�4+n*(2/3)%
    else if (cardID == 30134)
    {
        if (game.turn < 24)
            effect.xunLian = 4 + 0.6666667 * game.turn;
    }
    //3.����
    else if (cardID == 30010)
    {
        //ɶ��û��
    }
    //4.��������
    else if (cardID == 30019)
    {
        //ɶ��û��
    }
    //5.������
    else if (cardID == 30011)
    {
        //ɶ��û��
    }
    //6.ˮ˾��
    else if (cardID ==30107)
    {

        int traininglevel = game.getTrainingLevel(atTrain);
        effect.xunLian = 5 + traininglevel * 5;
        if (effect.xunLian > 25)effect.xunLian = 25;
    }
    //7.����˹
    else if (cardID == 30130)
    {
        if (jiBan < 80)
        {
            effect.bonus[2] = 0;
        }
    }
    //8.���ʵ�
    else if (cardID == 30037)
    {
        if (jiBan < 80)
        {
            effect.bonus[0] = 0;
        }
    }
    //9.������
    else if (cardID == 30027)
    {
        //ɶ��û��
    }
    //10.�ٱ�Ѩ
    else if (cardID == 30147)
    {
        if (jiBan < 100)
        {
            effect.bonus[0] = 0;
        }
    }
    //11.�ͺ���
    else if (cardID == 30016)
    {
        //ɶ��û��
    }
    //12.�Ǻø��
    else if (cardID == 30152)
    {
        if (jiBan < 80)
        {
            effect.bonus[0] = 0;
        }
    }
    //13.���ƽ��
    else if (cardID == 30153)
    {
        if (jiBan < 100)
        {
            effect.bonus[3] = 0;
        }
    }
    //14.�ǲ���
    else if (cardID == 30141)
    {
        //ɶ��û��
    }
    //15.�͵Ҷ�˹
    else if (cardID == 30099)
    {
        int totalJiBan = 0;
        for (int i = 0; i < 6; i++)
            totalJiBan += game.cardJiBan[i];
        effect.xunLian = totalJiBan / 30;
    }
    //����
    else if (cardID == 30101) {
        if (jiBan < 100)
        {
            effect.youQing = 22;
        }
    }
    //22���͹��
    else if (cardID == 30142)
    {
      if (game.turn < 24)
        effect.bonus[1] = 1;
      else if (game.turn < 48)
        effect.bonus[1] = 2;
      else
        effect.bonus[1] = 3;
    }
    //23������
    else if (cardID == 30123)
    {
      int traininglevel = game.getTrainingLevel(atTrain);
      effect.xunLian = 5 + traininglevel * 5;
      if (effect.xunLian > 25)effect.xunLian = 25;
    }
    //24������
    else if (cardID == 30151)
    {
        if (jiBan < 100)
        {
            effect.xunLian = 0;
        }
    }
    //25����ǡ
    else if (cardID == 30138)
    {
      if (jiBan < 100)
      {
        effect.bonus[2] = 0;
      }
    }
    //28������
    else if (cardID == 30112)
    {
      //�Ժ�����취
    }
    //29������
    else if (cardID == 30083)
    {
      if (jiBan < 80 || atTrain == 3)
        effect.xunLian = 0;
    }
    //30������
    else if (cardID == 30094)
    {
      if (effect.youQing > 0)
      {
        float extraBonus = 5 + (100 - game.vital) / 7.0;
        if (extraBonus > 15)extraBonus = 15;
        if (extraBonus < 5)extraBonus = 5; // std::cout << effect.youQing << " ";

        effect.youQing = 120 * (1 + 0.01 * extraBonus) - 100;

      }

    }
    //Ҳ��
    else if (cardID == 30126)
    {
        if (jiBan < 80)
        {

            effect.bonus[5] = 0;
        }
    }
    //����
    else if (cardID == 30127)
    {
        if (isShining)
        {
            effect.ganJing = 60;
        }
    }
    //����
    else if (cardID == 47)
    {
        //null
    }
    //�ٶ���
    else if (cardID == 30119)
    {
        if (jiBan < 80)
        {
            effect.bonus[2] = 0;
        }
    }
    // ����
    else if (cardID == 30067) {

        if (jiBan < 80)
            effect.bonus[5] = 0;

    }

    else
    {
      //  std::cout << "δ֪��";
    }

    return effect;
}
