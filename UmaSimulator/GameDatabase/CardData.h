#pragma once
#include "GameConstants.h"
#include "../SupportCard/CardEffect.h"
#include "../External/json.hpp"
#include "../External/utils.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using json = nlohmann::json;

class Game;

struct CardValue {
	//ȥ������basic�ֶ�
	bool filled;
	double youQing;//����ӳ�
	double ganJing;//�ɾ��ӳ�
	double xunLian;//ѵ���ӳ�
	double bonus[6];//����������pt�ļӳ�
	int wizVitalBonus;//������Ȧ�����ظ���
	int initialBonus[6];//��������������pt������
	int initialJiBan;//��ʼ�
	double saiHou;//����
	int hintBonus[6];//Ϊ�˼򻯣��Ѻ��ļ��ܵ�Ч�ɶ������ԡ��ۺϿ��Ǽ�����Ч�ʣ�����߷�90%��Ч�����˼���������ƽ���Լ۱����ۿۣ������ظ������ܣ�����30%��
	double hintProbIncrease;//��������������
	double deYiLv;//������
	double failRateDrop; //ʧ���ʽ���
	double vitalCostDrop; //���������½�
};
struct SkillList {
	int skillNum;
	std::vector<int> skillIdList; // ��Ƭӵ�еļ��ܱ��
};
struct SupportCard
{
	int cardID;//֧Ԯ��id�����ֿ����бȽϸ��ӵĹ��У�����id�����
	int cardType;//֧Ԯ�����ͣ�0��1��2��3��4��5���˻��Ŷ�
	std::string cardName; //��Ƭ����

	CardValue level[5];
	// ����ͻ�Ƶȼ�������

	double youQing;//����ӳ�
	double ganJing;//�ɾ��ӳ�
	double xunLian;//ѵ���ӳ�
	double bonus[6];//����������pt�ļӳ�
	int wizVitalBonus;//������Ȧ�����ظ���
	int initialBonus[6];//��������������pt������
	int initialJiBan;//��ʼ�
	double saiHou;//����
	int hintBonus[6];//Ϊ�˼򻯣��Ѻ��ļ��ܵ�Ч�ɶ������ԡ��ۺϿ��Ǽ�����Ч�ʣ�����߷�90%��Ч�����˼���������ƽ���Լ۱����ۿۣ������ظ������ܣ�����30%��
	double hintProbIncrease;//��������������
	double deYiLv;//������
	double failRateDrop; //ʧ���ʽ���
	double vitalCostDrop; //���������½�
	// ������ã����ݿ�Ƭ�ĵȼ�����Ϸ��ʼ�׶θ�ֵ

	SkillList cardSkill;
	//��Ƭӵ�еļ����б�
	
	int effectFactor; // ��Ϊ������д���Ĳ���
	CardTrainingEffect getCardEffect(const Game& game, int atTrain, int jiBan, int effecFactor) const;//������Ϸ״̬����֧Ԯ���ġ����С�

	void cardValueInit(int x) {

		while (x <= 4 && level[x].filled == false)
			x++;
		if (x > 4) {
			std::cout << "δ֪��Ƭ��Ϣ����Ƭ����¼�����: " << cardName << '\n';
			exit(0);
		}

		youQing = level[x].youQing; 
		ganJing = level[x].ganJing;
		xunLian = level[x].xunLian;
		for (int i = 0; i < 6; ++i)
			bonus[i] = level[x].bonus[i];
		wizVitalBonus = level[x].wizVitalBonus;
		for (int i = 0; i < 6; ++i)
			initialBonus[6] = level[x].initialBonus[i];
		initialJiBan = level[x].initialJiBan;
		saiHou = level[x].saiHou;
		for (int i = 0; i < 6; ++i)
			hintBonus[6] = level[x].hintBonus[i];
		hintProbIncrease = level[x].hintProbIncrease;
		deYiLv = level[x].deYiLv;
		failRateDrop = level[x].failRateDrop;
		vitalCostDrop = level[x].vitalCostDrop;

		effectFactor = 0;

		return ;

	}

	void write_to_json(json& j,const std::string cdname,const int id)
	{
		j["cardId"] = id;
		j["cardType"] = cardType;

		j["cardName"] = string_To_UTF8(cdname);

		j["cardValue"][0]["filled"] = false;
		j["cardValue"][1]["filled"] = false;
		j["cardValue"][2]["filled"] = false;
		j["cardValue"][3]["filled"] = false;

		for (int x = 0; x < 5; ++x) {
			if (j["cardValue"][x]["filled"] == false) {
				j["cardValue"][x]["filled"] = false;
				continue;
			}
			j["cardValue"][x]["filled"] = true;
			j["cardValue"][x]["youQing"] = level[x].youQing;
			j["cardValue"][x]["ganJing"] = level[x].ganJing;
			j["cardValue"][x]["xunLian"] = level[x].xunLian;
			j["cardValue"][x]["bonus"] = level[x].bonus;
			j["cardValue"][x]["wizVitalBonus"] = level[x].wizVitalBonus;
			j["cardValue"][x]["initialBonus"] = level[x].initialBonus;
			j["cardValue"][x]["initialJiBan"] = level[x].initialJiBan;
			j["cardValue"][x]["saiHou"] = level[x].saiHou;
			j["cardValue"][x]["hintBonus"] = level[x].hintBonus;
			j["cardValue"][x]["hintProbIncrease"] = level[x].hintProbIncrease;
			j["cardValue"][x]["deYiLv"] = level[x].deYiLv;
			j["cardValue"][x]["failRateDrop"] = level[x].failRateDrop;
			j["cardValue"][x]["vitalCostDrop"] = level[x].vitalCostDrop;
		}


		


		j["cardSkill"]["skillNum"] = 0;
		j["cardSkill"]["SkillList"] = NULL;
		
	}

	void load_from_json(json& j) {

		j.at("cardId").get_to(cardID);
		j.at("cardType").get_to(cardType);
		std::string st;
		j.at("cardName").get_to(st);
		cardName = UTF8_To_string(st);


		for (int x = 0; x < 5; ++x) {

			j["cardValue"][x].at("filled").get_to(level[x].filled);
			if (level[x].filled == false) continue;

			j["cardValue"][x].at("youQing").get_to(level[x].youQing);
			j["cardValue"][x].at("ganJing").get_to(level[x].ganJing);
			j["cardValue"][x].at("xunLian").get_to(level[x].xunLian);
			j["cardValue"][x].at("bonus").get_to(level[x].bonus);
			j["cardValue"][x].at("wizVitalBonus").get_to(level[x].wizVitalBonus);
			j["cardValue"][x].at("initialBonus").get_to(level[x].initialBonus);
			j["cardValue"][x].at("initialJiBan").get_to(level[x].initialJiBan);
			j["cardValue"][x].at("saiHou").get_to(level[x].saiHou);
			j["cardValue"][x].at("hintBonus").get_to(level[x].hintBonus);
			j["cardValue"][x].at("hintProbIncrease").get_to(level[x].hintProbIncrease);
			j["cardValue"][x].at("deYiLv").get_to(level[x].deYiLv);
			j["cardValue"][x].at("failRateDrop").get_to(level[x].failRateDrop);
			j["cardValue"][x].at("vitalCostDrop").get_to(level[x].vitalCostDrop);
		}

		cardSkill.skillNum = j["cardSkill"]["skillNum"];

		cardSkill.skillIdList.resize(cardSkill.skillNum);
		for (int i = 0; i < cardSkill.skillNum; ++i) {
			cardSkill.skillIdList[i] = j["cardSkill"]["skillList"][i];
		}

		return;
	}
};