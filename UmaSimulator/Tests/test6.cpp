#include <iostream>
#include <iomanip> 
#include <sstream>
#include <fstream>
#include <cassert>
#include <thread>  // for std::this_thread::sleep_for
#include <chrono>  // for std::chrono::seconds

#include "../Game/Game.h"
#include "../GameDatabase/GameConfig.h"
#include "../Search/Search.h"
#include "windows.h"
#include <filesystem>
#include <cstdlib>
using namespace std;

template <typename T, std::size_t N>
std::size_t findMaxIndex(const T(&arr)[N]) {
    return std::distance(arr, std::max_element(arr, arr + N));
}

void main_test6()
{
  //const double radicalFactor = 5;//������
  //const int threadNum = 16; //�߳���
 // const int searchN = 12288; //ÿ��ѡ������ؿ���ģ��ľ���

  //������Ϊk��ģ��n��ʱ����׼��ԼΪsqrt(1+k^2/(2k+1))*1200/(sqrt(n))
  //��׼�����30ʱ������Ӱ���ж�׼ȷ��

  Search search;
  vector<Evaluator> evaluators;

  int lastTurn = -1;
  int scoreFirstTurn = 0;   // ��һ�غϷ���
  int scoreLastTurn = 0;   // ��һ�غϷ���

  // ��鹤��Ŀ¼
  wchar_t buf[10240];
  GetModuleFileNameW(0, buf, 10240);
  filesystem::path exeDir = filesystem::path(buf).parent_path();
  filesystem::current_path(exeDir);
  //std::cout << "��ǰ����Ŀ¼��" << filesystem::current_path() << endl;
  cout << "��ǰ����Ŀ¼��" << exeDir << endl;
  GameDatabase::loadUmas("db/uma");
  GameConfig::load("aiConfig.json");

  for (int i = 0; i < GameConfig::threadNum; i++)
      evaluators.push_back(Evaluator(NULL, 128));

  while (true)
  {
    while (!filesystem::exists("./packets/currentGS.json"))
    {
        std::cout << "�Ҳ��� packets/currentGS.json�����鹤��·����URA�������" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));//�ӳټ��룬����ˢ��
    }
    ifstream fs("./packets/currentGS.json");
    if (!fs.good())
    {
      cout << "�ȴ���Ϸ��ʼ" << endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(3000));//�ӳټ��룬����ˢ��
      continue;
    }
    ostringstream tmp;
    tmp << fs.rdbuf();
    fs.close();

    string jsonStr = tmp.str();
    Game game;
    bool suc = game.loadGameFromJson(jsonStr);
    if (!suc)
    {
      cout << "���ִ���" << endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(3000));//�ӳټ��룬����ˢ��
      continue;
    }
    if (game.turn == lastTurn)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(300));//����Ƿ��и���
      continue;
    }
    lastTurn = game.turn;
    if (game.venusIsWisdomActive)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(300));
      continue;
    }

    if (game.turn == 0)//��һ�غϣ���������ai�ĵ�һ�غ�
    {
      scoreFirstTurn = 0;
      scoreLastTurn = 0;
    }
    game.print();
    cout << endl;
    cout << "������...";

    auto printPolicy = [](float p)
    {
      cout << fixed << setprecision(1);
      if (!GameConfig::noColor)
      {
        if (p >= 0.3)cout << "\033[33m";
        //else if (p >= 0.1)cout << "\033[32m";
        else cout << "\033[36m";
      }
      cout << p * 100 << "% ";
      if (!GameConfig::noColor)cout << "\033[0m";
    };

    search.runSearch(game, evaluators.data(), GameConfig::searchN, TOTAL_TURN, 0, GameConfig::threadNum, GameConfig::radicalFactor);
    cout << endl << "�������" << endl;
    cout << ">>" << endl;
    {
      auto policy = search.extractPolicyFromSearchResults(1);
      if (game.venusAvailableWisdom != 0)
      {
        cout << "ʹ��Ů���ʣ�";
        printPolicy(policy.useVenusPolicy);
        cout << endl;
      }
      if (!game.isRacing)
      {
        if (game.venusAvailableWisdom != 0)
        {
          cout << "��" << (policy.useVenusPolicy > 0.5 ? "" : " �� ") << "ʹ��Ů���ǰ���£�";
        }

        cout << "���������ǣ�";
        for (int i = 0; i < 5; i++)
          printPolicy(policy.trainingPolicy[i]);
        cout << endl;

        cout << "��Ϣ�������������";
        for (int i = 0; i < 3; i++)
          printPolicy(policy.trainingPolicy[5 + i]);
        cout << endl;

        cout << "Ů����ѡһ�¼����죬�����ƣ�";
        for (int i = 0; i < 3; i++)
          printPolicy(policy.threeChoicesEventPolicy[i]);
        cout << endl;

        cout << "���Ů������Լ���ͨ�����";
        for (int i = 0; i < 6; i++)
          printPolicy(policy.outgoingPolicy[i] * policy.trainingPolicy[6]);
        cout << endl;

        cout << "\033[1m\033[33m" << "���־��ߣ�" << "\033[0m" << "�Ƿ�ʹ��Ů��";
        if (policy.useVenusPolicy > 0.5) {
            cout << "\033[32m" << "��" << "\033[0m";
        }
        else {
            cout << "\033[31m" << "��" << "\033[0m";
        }

        cout << "��������ѡһ��";
        std::size_t godChoice = findMaxIndex(policy.threeChoicesEventPolicy);
        switch (godChoice) {
        case 0:
            cout << "\033[41m" << "�죨1��" << "\033[0m";
            break;
        case 1:
            cout << "\033[44m" << "����2��" << "\033[0m";
            break;
        case 2:
            cout << "\033[43m" << "�ƣ�3��" << "\033[0m";
            break;
        }

        cout << "\033[0m" << " | �ж���" << "\033[32m";
        std::size_t trainChoice = findMaxIndex(policy.trainingPolicy);
        switch (trainChoice) {
        case 0:
            cout << "�ٶ�ѵ����ѵ��1����";
            break;
        case 1:
            cout << "����ѵ����ѵ��2��;";
            break;
        case 2:
            cout << "����ѵ����ѵ��3��;";
            break;
        case 3:
            cout << "����ѵ����ѵ��4��;";
            break;
        case 4:
            cout << "����ѵ����ѵ��5��;";
            break;
        case 5:
            cout << "��Ϣ;";
            break;
        case 6: 
        {
            cout << "�����";
            std::size_t outgoingPolicy = findMaxIndex(policy.outgoingPolicy);
            switch (outgoingPolicy) {
            case 0:
                cout << "\033[31m" << "��Ů�� - 1";
                break;
            case 1:
                cout << "\033[34m" << "��Ů�� - 2";
                break;
            case 2:
                cout << "\033[33m" << "��Ů�� - 3";
                break;
            case 3:
                cout << "\033[36m" << "��Ů�� - 4-1";
                break;
            case 4:
                cout << "\033[36m" << "��Ů�� - 4-2";
                break;
            case 5:
                cout << "\033[35m" << "��ͨ���";
            }
            cout << "\033[0m";
            break;
        }
        case 7:
            cout << "����;";
            break;
        }
        cout << "\033[0m" << endl;
      }
    }

    float maxScore = -1e6;
    for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < 8; j++)
      {
        float s = search.allChoicesValue[i][j].avgScoreMinusTarget;
        if (s > maxScore)maxScore = s;
      }
    }
    if(game.turn==0)
    {
      scoreFirstTurn = maxScore;
    }
    else
    {
      cout<<"��������ָ��û�п��Ǽ��ܣ����ܺ��½�����" << endl;
      cout << "�˾�������" << maxScore - scoreFirstTurn  << endl;
      cout << "�˻غ�������" << maxScore - scoreLastTurn  << endl; 
      double raceLoss = maxScore - max(search.allChoicesValue[0][7].avgScoreMinusTarget, search.allChoicesValue[1][7].avgScoreMinusTarget);
      if (raceLoss < 5e5)//raceLoss��Լ1e6������ܱ���
        cout << "������������ѡ������غϣ�����ɷ�˿��Ŀ�꣩��" << raceLoss << endl;
      cout << "<<" << endl;
      cout.flush();
    }
    scoreLastTurn = maxScore;
  }

}