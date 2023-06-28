#pragma once
#include <string>


const int TOTAL_TURN = 78;//һ��78�غ�
static const int SHENTUAN_ID = 1;//���ſ���id

class GameConstants
{
public:
  //��Ϸ��ʼ��
  static const int TrainingBasicValue[5][6][7]; //TrainingBasicValue[�ڼ���ѵ��][LV��][����������pt����]����Ů����LV6
  static const int BasicFiveValueLimit[5];//��ʼ���ޣ�1200���Ϸ���

  //Ů��
  static const int VenusLevelTrainBonus[6];//Ů��ȼ�ѵ���ӳ�
  static const int RedVenusLevelVitalCostDown[6];//��Ů�����������½�����
  static const int BlueVenusLevelHintProbBonus[6];//��Ů���¼�������������
  static const int YellowVenusLevelEventBonus[6];//��Ů���¼���ֵ������
  static const int YellowVenusLevelContinuousEventProb[6];//��Ů�������¼�����������

  static const int BlueVenusRelatedValue[5][6];//��Ů���������
  static const int VenusSpiritTypeProb[8][6];//��Ƭ���Ը��ʣ�01234�ֱ������������ǣ�5����Ϣ��6�������7�Ǳ���



  //����
  static const int FiveValueFinalScore[1200+800*2+1];//��ͬ���Զ�Ӧ������
  static const double ScorePtRate;//Ϊ�˷��㣬ֱ����Ϊÿ1pt��Ӧ���ٷ֡�
  static const double ScorePtRateQieZhe;//Ϊ�˷��㣬ֱ����Ϊÿ1pt��Ӧ���ٷ֡�����


};