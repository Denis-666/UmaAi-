#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "GameDatabase.h"
#include "../Game/Game.h"


using json = nlohmann::json;
using namespace std;

unordered_map<int, SupportCard> GameDatabase::AllCards;

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
                    if (AllCards.count(jdata.cardID) > 0)
                        cout << "�����ظ�֧Ԯ�� #" << jdata.cardName << " --- " << jdata.cardID << endl;
                    else
                        AllCards[jdata.cardID] = jdata;
                }
                catch (exception& e)
                {
                    cout << "֧Ԯ����ϢJSON����: " << entry.path() << endl << e.what() << endl;
                }
            }
        }
        cout << "������ " << AllCards.size() << " ��֧Ԯ������" << endl;
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
      youQing,
      ganJing,
      xunLian,
      {bonus[0],bonus[1],bonus[2],bonus[3],bonus[4],bonus[5]},
      wizVitalBonus
    };

    bool isShining = true;//�Ƿ�����
    if (cardType < 5)//���������ǿ�
    {
        if (jiBan < 80)isShining = false;
        if (cardType != atTrain)isShining = false;
    }
    else if (GameDatabase::AllCards[cardID].cardType == 5)//����
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
    if (cardID == 1)
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
    else if (cardID == 2)
    {
        if (game.turn < 24)
            effect.xunLian = 4 + 0.6666667 * game.turn;
    }
    //3.����
    else if (cardID == 3)
    {
        //ɶ��û��
    }
    //4.��������
    else if (cardID == 4)
    {
        //ɶ��û��
    }
    //5.������
    else if (cardID == 5)
    {
        //ɶ��û��
    }
    //6.ˮ˾��
    else if (cardID == 6)
    {
        int traininglevel = game.getTrainingLevel(atTrain);
        effect.xunLian = 5 + traininglevel * 5;
        if (effect.xunLian > 25)effect.xunLian = 25;
    }
    //7.����˹
    else if (cardID == 7)
    {
        if (jiBan < 80)
        {
            effect.bonus[2] = 0;
        }
    }
    //8.���ʵ�
    else if (cardID == 8)
    {
        if (jiBan < 80)
        {
            effect.bonus[0] = 0;
        }
    }
    //9.������
    else if (cardID == 9)
    {
        //ɶ��û��
    }
    //10.�ٱ�Ѩ
    else if (cardID == 10)
    {
        if (jiBan < 100)
        {
            effect.bonus[0] = 0;
        }
    }
    //11.�ͺ���
    else if (cardID == 11)
    {
        //ɶ��û��
    }
    //12.�Ǻø��
    else if (cardID == 12)
    {
        if (jiBan < 80)
        {
            effect.bonus[0] = 0;
        }
    }
    //13.���ƽ��
    else if (cardID == 13)
    {
        if (jiBan < 100)
        {
            effect.bonus[3] = 0;
        }
    }
    //14.�ǲ���
    else if (cardID == 14)
    {
        //ɶ��û��
    }
    //15.�͵Ҷ�˹
    else if (cardID == 15)
    {
        int totalJiBan = 0;
        for (int i = 0; i < 6; i++)
            totalJiBan += game.cardJiBan[i];
        effect.xunLian = totalJiBan / 30;
    }
    //16.��С��ñ
    else if (cardID == 16)
    {
        //ɶ��û��
    }
    //17�����
    else if (cardID == 17) {
        //ɶ��û��
    }
    //�ٱ���
    else if (cardID == 18) {
        //ɶ��û��
    }
    //����
    else if (cardID == 19) {
        //ɶ��û��
    }
    //����
    else if (cardID == 20) {
        if (jiBan < 100)
        {
            effect.youQing = 22;
        }
    }
    //21�͹���
    else if (cardID == 21)
    {
        //ɶ��û��
    }
    //22���͹��
    else if (cardID == 22)
    {
      if (game.turn < 24)
        effect.bonus[1] = 1;
      else if (game.turn < 48)
        effect.bonus[1] = 2;
      else
        effect.bonus[1] = 3;
    }
    //23������
    else if (cardID == 23)
    {
      int traininglevel = game.getTrainingLevel(atTrain);
      effect.xunLian = 5 + traininglevel * 5;
      if (effect.xunLian > 25)effect.xunLian = 25;
    }
    //24������
    else if (cardID == 24)
    {
        if (jiBan < 100)
        {
            effect.xunLian = 0;
        }
    }
    //25����ǡ
    else if (cardID == 25)
    {
      if (jiBan < 100)
      {
        effect.bonus[2] = 0;
      }
    }
    //28������
    else if (cardID == 28)
    {
      //�Ժ�����취
    }
    //29������
    else if (cardID == 29)
    {
      if (jiBan < 80 || atTrain == 3)
        effect.xunLian = 0;
    }
    //30������
    else if (cardID == 30)
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
    else if (cardID == 45)
    {
        if (jiBan < 80)
        {

            effect.bonus[5] = 0;
        }
    }
    //����
    else if (cardID == 46)
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
    else if (cardID == 48)
    {
        if (jiBan < 80)
        {
            effect.bonus[2] = 0;
        }
    }
    //����ǡ
    else if (cardID == 49)
    {
        //ɶ��û��
    }

    else
    {
      //  std::cout << "δ֪��";
    }

    return effect;
}
