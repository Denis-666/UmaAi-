#include "GameConstants.h"
#include "UmaData.h"

//�������߱Ƚ϶̵��б�������ǰ��
const double GameConstants::ScorePtRate = 1.8;
const double GameConstants::ScorePtRateQieZhe = 2.0;
const int GameConstants::BasicFiveValueLimit[5] = { 1800,1600,1800,1400,1400 }; //��Ϸ��ԭ����1500 1400 1500 1300 1300��ģ������1200���Ϸ���

const int GameConstants::VenusLevelTrainBonus[6] = { 0,5,8,11,13,15 };
const int GameConstants::RedVenusLevelVitalCostDown[6] = { 0,10,15,18,20,23 };//��Ů�����������½�����
const int GameConstants::BlueVenusLevelHintProbBonus[6] = { 0,20,25,30,33,35 };//��Ů���¼�������������
const int GameConstants::YellowVenusLevelEventBonus[6] = { 0,10,15,20,23,25 };//��Ů���¼���ֵ������
const int GameConstants::YellowVenusLevelContinuousEventProb[6] = { 0,20,40,50,80,90 };//��Ů�������¼�����������

const int GameConstants::BlueVenusRelatedValue[5][6] = //��Ů���������
{
  {6,0,2,0,0,0},
  {0,6,0,2,0,0},
  {0,2,6,0,0,0},
  {1,0,1,6,0,0},
  {0,0,0,0,6,5},
};
const int GameConstants::VenusSpiritTypeProb[8][6] =
{
  {4,1,4,1,1,4},
  {1,4,1,4,1,4},
  {1,4,4,1,1,4},
  {17,6,17,17,6,17},
  {4,1,1,1,4,4},
  {1,1,1,1,1,1},
  {1,1,1,1,1,1},
  {1,1,1,1,1,1},
};

const int GameConstants::TrainingBasicValue[5][6][7] =
{
  //��
  {
    { 10, 0, 3, 0, 0, 5, -19},
    { 11, 0, 3, 0, 0, 5, -21},
    { 12, 0, 4, 0, 0, 5, -22},
    { 13, 0, 4, 0, 0, 5, -24},
    { 14, 0, 5, 0, 0, 5, -25},
    { 15, 0, 6, 0, 0, 5, -26},
  },
  //��
  {
    { 0, 8, 0, 6, 0, 5, -20},
    { 0, 9, 0, 6, 0, 5, -22},
    { 0, 10, 0, 7, 0, 5, -23},
    { 0, 11, 0, 7, 0, 5, -25},
    { 0, 12, 0, 8, 0, 5, -26},
    { 0, 13, 0, 9, 0, 5, -27},
  },
  //��
  {
    { 0, 4, 9, 0, 0, 5, -20},
    { 0, 4, 10, 0, 0, 5, -22},
    { 0, 5, 11, 0, 0, 5, -23},
    { 0, 5, 12, 0, 0, 5, -25},
    { 0, 6, 13, 0, 0, 5, -26},
    { 0, 7, 14, 0, 0, 5, -27},
  },
  //��
  {
    { 2, 0, 3, 8, 0, 5, -20},
    { 2, 0, 3, 9, 0, 5, -22},
    { 2, 0, 3, 10, 0, 5, -23},
    { 2, 0, 3, 11, 0, 5, -25},
    { 3, 0, 4, 12, 0, 5, -26},
    { 4, 0, 5, 13, 0, 5, -27},
  },
  //��
  {
    { 2, 0, 0, 0, 8, 5, 5},
    { 2, 0, 0, 0, 9, 5, 5},
    { 3, 0, 0, 0, 10, 5, 5},
    { 3, 0, 0, 0, 11, 5, 5},
    { 4, 0, 0, 0, 12, 5, 5},
    { 5, 0, 0, 0, 13, 5, 5},
  },
};

const int GameConstants::FiveValueFinalScore[2801] = {
0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,24,25,25,26,27,28,29,29,30,31,32,33,33,34,35,36,37,37,38,39,40,41,41,42,43,44,45,45,46,47,48,49,49,50,51,52,53,53,54,55,56,57,57,58,59,60,61,61,62,63,64,65,
66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,120,121,122,124,125,126,128,129,130,131,133,134,135,137,138,139,141,142,143,144,146,147,148,150,151,152,154,155,156,157,159,160,161,163,164,165,167,168,169,170,172,173,174,176,177,178,180,
181,183,184,186,188,189,191,192,194,196,197,199,200,202,204,205,207,208,210,212,213,215,216,218,220,221,223,224,226,228,229,231,232,234,236,237,239,240,242,244,245,247,248,250,252,253,255,256,258,260,261,263,265,267,269,270,272,274,276,278,279,281,283,285,287,288,290,292,294,296,297,299,301,303,305,306,308,310,312,314,315,317,319,321,323,324,326,328,330,332,333,335,337,339,341,342,344,346,348,350,
352,354,356,358,360,362,364,366,368,371,373,375,377,379,381,383,385,387,389,392,394,396,398,400,402,404,406,408,410,413,415,417,419,421,423,425,427,429,431,434,436,438,440,442,444,446,448,450,452,455,457,459,462,464,467,469,471,474,476,479,481,483,486,488,491,493,495,498,500,503,505,507,510,512,515,517,519,522,524,527,529,531,534,536,539,541,543,546,548,551,553,555,558,560,563,565,567,570,572,575,
577,580,582,585,588,590,593,595,598,601,603,606,608,611,614,616,619,621,624,627,629,632,634,637,640,642,645,647,650,653,655,658,660,663,666,668,671,673,676,679,681,684,686,689,692,694,697,699,702,705,707,710,713,716,719,721,724,727,730,733,735,738,741,744,747,749,752,755,758,761,763,766,769,772,775,777,780,783,786,789,791,794,797,800,803,805,808,811,814,817,819,822,825,828,831,833,836,839,842,845,
847,850,853,856,859,862,865,868,871,874,876,879,882,885,888,891,894,897,900,903,905,908,911,914,917,920,923,926,929,932,934,937,940,943,946,949,952,955,958,961,963,966,969,972,975,978,981,984,987,990,993,996,999,1002,1005,1008,1011,1014,1017,1020,1023,1026,1029,1032,1035,1038,1041,1044,1047,1050,1053,1056,1059,1062,1065,1068,1071,1074,1077,1080,1083,1086,1089,1092,1095,1098,1101,1104,1107,1110,1113,1116,1119,1122,1125,1128,1131,1134,1137,1140,
1143,1146,1149,1152,1155,1158,1161,1164,1167,1171,1174,1177,1180,1183,1186,1189,1192,1195,1198,1202,1205,1208,1211,1214,1217,1220,1223,1226,1229,1233,1236,1239,1242,1245,1248,1251,1254,1257,1260,1264,1267,1270,1273,1276,1279,1282,1285,1288,1291,1295,1298,1301,1304,1308,1311,1314,1318,1321,1324,1328,1331,1334,1337,1341,1344,1347,1351,1354,1357,1361,1364,1367,1370,1374,1377,1380,1384,1387,1390,1394,1397,1400,1403,1407,1410,1413,1417,1420,1423,1427,1430,1433,1436,1440,1443,1446,1450,1453,1456,1460,
1463,1466,1470,1473,1477,1480,1483,1487,1490,1494,1497,1500,1504,1507,1511,1514,1517,1521,1524,1528,1531,1534,1538,1541,1545,1548,1551,1555,1558,1562,1565,1568,1572,1575,1579,1582,1585,1589,1592,1596,1599,1602,1606,1609,1613,1616,1619,1623,1626,1630,1633,1637,1640,1644,1647,1651,1654,1658,1661,1665,1668,1672,1675,1679,1682,1686,1689,1693,1696,1700,1703,1707,1710,1714,1717,1721,1724,1728,1731,1735,1738,1742,1745,1749,1752,1756,1759,1763,1766,1770,1773,1777,1780,1784,1787,1791,1794,1798,1801,1805,
1808,1812,1816,1820,1824,1828,1832,1836,1840,1844,1847,1851,1855,1859,1863,1867,1871,1875,1879,1883,1886,1890,1894,1898,1902,1906,1910,1914,1918,1922,1925,1929,1933,1937,1941,1945,1949,1953,1957,1961,1964,1968,1972,1976,1980,1984,1988,1992,1996,2000,2004,2008,2012,2016,2020,2024,2028,2032,2036,2041,2045,2049,2053,2057,2061,2065,2069,2073,2077,2082,2086,2090,2094,2098,2102,2106,2110,2114,2118,2123,2127,2131,2135,2139,2143,2147,2151,2155,2159,2164,2168,2172,2176,2180,2184,2188,2192,2196,2200,2205,
2209,2213,2217,2221,2226,2230,2234,2238,2242,2247,2251,2255,2259,2263,2268,2272,2276,2280,2284,2289,2293,2297,2301,2305,2310,2314,2318,2322,2326,2331,2335,2339,2343,2347,2352,2356,2360,2364,2368,2373,2377,2381,2385,2389,2394,2398,2402,2406,2410,2415,2419,2423,2427,2432,2436,2440,2445,2449,2453,2458,2462,2466,2470,2475,2479,2483,2488,2492,2496,2501,2505,2509,2513,2518,2522,2526,2531,2535,2539,2544,2548,2552,2556,2561,2565,2569,2574,2578,2582,2587,2591,2595,2599,2604,2608,2612,2617,2621,2625,2630,
2635,2640,2645,2650,2656,2661,2666,2671,2676,2682,2687,2692,2697,2702,2708,2713,2718,2723,2728,2734,2739,2744,2749,2754,2760,2765,2770,2775,2780,2786,2791,2796,2801,2806,2812,2817,2822,2827,2832,2838,2843,2848,2853,2858,2864,2869,2874,2879,2884,2890,2895,2901,2906,2912,2917,2923,2928,2934,2939,2945,2950,2956,2961,2967,2972,2978,2983,2989,2994,3000,3005,3011,3016,3022,3027,3033,3038,3044,3049,3055,3060,3066,3071,3077,3082,3088,3093,3099,3104,3110,3115,3121,3126,3132,3137,3143,3148,3154,3159,3165,
3171,3178,3184,3191,3198,3204,3211,3217,3224,3231,3237,3244,3250,3257,3264,3270,3277,3283,3290,3297,3303,3310,3316,3323,3330,3336,3343,3349,3356,3363,3369,3376,3382,3389,3396,3402,3409,3415,3422,3429,3435,3442,3448,3455,3462,3468,3475,3481,3488,3495,3501,3508,3515,3522,3529,3535,3542,3549,3556,3563,3569,3576,3583,3590,3597,3603,3610,3617,3624,3631,3637,3644,3651,3658,3665,3671,3678,3685,3692,3699,3705,3712,3719,3726,3733,3739,3746,3753,3760,3767,3773,3780,3787,3794,3801,3807,3814,3821,3828,3835,
3841,3841,3849,3849,3857,3857,3865,3865,3873,3873,3881,3881,3889,3889,3897,3897,3905,3905,3912,3912,3920,3920,3928,3928,3936,3936,3944,3944,3952,3952,3960,3960,3968,3968,3976,3976,3984,3984,3992,3992,4001,4001,4009,4009,4017,4017,4025,4025,4033,4033,4041,4041,4049,4049,4057,4057,4065,4065,4073,4073,4082,4082,4090,4090,4098,4098,4107,4107,4115,4115,4123,4123,4132,4132,4140,4140,4148,4148,4156,4156,4165,4165,4173,4173,4182,4182,4190,4190,4198,4198,4207,4207,4215,4215,4224,4224,4232,4232,4240,4240,
4249,4249,4257,4257,4266,4266,4274,4274,4283,4283,4291,4291,4300,4300,4308,4308,4317,4317,4325,4325,4334,4334,4343,4343,4351,4351,4360,4360,4368,4368,4377,4377,4386,4386,4394,4394,4403,4403,4411,4411,4420,4420,4429,4429,4438,4438,4447,4447,4455,4455,4464,4464,4473,4473,4482,4482,4491,4491,4499,4499,4508,4508,4517,4517,4526,4526,4535,4535,4544,4544,4553,4553,4562,4562,4571,4571,4580,4580,4588,4588,4597,4597,4606,4606,4615,4615,4624,4624,4633,4633,4642,4642,4651,4651,4660,4660,4669,4669,4678,4678,
4688,4688,4697,4697,4706,4706,4715,4715,4724,4724,4734,4734,4743,4743,4752,4752,4761,4761,4770,4770,4780,4780,4789,4789,4798,4798,4808,4808,4817,4817,4826,4826,4836,4836,4845,4845,4854,4854,4863,4863,4873,4873,4882,4882,4892,4892,4901,4901,4910,4910,4920,4920,4929,4929,4939,4939,4948,4948,4957,4957,4967,4967,4977,4977,4986,4986,4996,4996,5005,5005,5015,5015,5025,5025,5034,5034,5044,5044,5053,5053,5063,5063,5073,5073,5083,5083,5092,5092,5102,5102,5112,5112,5121,5121,5131,5131,5141,5141,5150,5150,
5160,5160,5170,5170,5180,5180,5190,5190,5199,5199,5209,5209,5219,5219,5229,5229,5239,5239,5248,5248,5258,5258,5268,5268,5278,5278,5288,5288,5298,5298,5308,5308,5318,5318,5328,5328,5338,5338,5348,5348,5359,5359,5369,5369,5379,5379,5389,5389,5399,5399,5409,5409,5419,5419,5429,5429,5439,5439,5449,5449,5460,5460,5470,5470,5480,5480,5490,5490,5500,5500,5511,5511,5521,5521,5531,5531,5541,5541,5551,5551,5562,5562,5572,5572,5582,5582,5593,5593,5603,5603,5613,5613,5624,5624,5634,5634,5644,5644,5654,5654,
5665,5665,5675,5675,5686,5686,5696,5696,5707,5707,5717,5717,5728,5728,5738,5738,5749,5749,5759,5759,5770,5770,5781,5781,5791,5791,5802,5802,5812,5812,5823,5823,5834,5834,5844,5844,5855,5855,5865,5865,5876,5876,5887,5887,5898,5898,5908,5908,5919,5919,5930,5930,5940,5940,5951,5951,5962,5962,5972,5972,5983,5983,5994,5994,6005,6005,6016,6016,6027,6027,6038,6038,6049,6049,6060,6060,6071,6071,6081,6081,6092,6092,6103,6103,6114,6114,6125,6125,6136,6136,6147,6147,6158,6158,6169,6169,6180,6180,6191,6191,
6203,6203,6214,6214,6225,6225,6236,6236,6247,6247,6258,6258,6269,6269,6280,6280,6291,6291,6302,6302,6314,6314,6325,6325,6336,6336,6348,6348,6359,6359,6370,6370,6382,6382,6393,6393,6404,6404,6415,6415,6427,6427,6438,6438,6450,6450,6461,6461,6472,6472,6484,6484,6495,6495,6507,6507,6518,6518,6529,6529,6541,6541,6552,6552,6564,6564,6575,6575,6587,6587,6598,6598,6610,6610,6621,6621,6633,6633,6644,6644,6656,6656,6668,6668,6680,6680,6691,6691,6703,6703,6715,6715,6726,6726,6738,6738,6750,6750,6761,6761,
6773,6773,6785,6785,6797,6797,6809,6809,6820,6820,6832,6832,6844,6844,6856,6856,6868,6868,6879,6879,6891,6891,6903,6903,6915,6915,6927,6927,6939,6939,6951,6951,6963,6963,6975,6975,6987,6987,6998,6998,7011,7011,7023,7023,7035,7035,7047,7047,7059,7059,7071,7071,7083,7083,7095,7095,7107,7107,7119,7119,7132,7132,7144,7144,7156,7156,7168,7168,7180,7180,7193,7193,7205,7205,7217,7217,7229,7229,7241,7241,7254,7254,7266,7266,7278,7278,7291,7291,7303,7303,7315,7315,7328,7328,7340,7340,7352,7352,7364,7364,
7377,7377,7389,7389,7402,7402,7414,7414,7426,7426,7439,7439,7451,7451,7464,7464,7476,7476,7488,7488,7501,7501,7514,7514,7526,7526,7539,7539,7551,7551,7564,7564,7577,7577,7589,7589,7602,7602,7614,7614,7627,7627,7640,7640,7653,7653,7665,7665,7678,7678,7691,7691,7703,7703,7716,7716,7729,7729,7741,7741,7754,7754,7767,7767,7780,7780,7793,7793,7805,7805,7818,7818,7831,7831,7844,7844,7857,7857,7869,7869,7882,7882,7895,7895,7908,7908,7921,7921,7934,7934,7947,7947,7960,7960,7973,7973,7986,7986,7999,7999,
8013,8013,8026,8026,8039,8039,8052,8052,8065,8065,8078,8078,8091,8091,8104,8104,8117,8117,8130,8130,8144,8144,8157,8157,8170,8170,8183,8183,8196,8196,8210,8210,8223,8223,8236,8236,8249,8249,8262,8262,8276,8276,8289,8289,8303,8303,8316,8316,8329,8329,8343,8343,8356,8356,8370,8370,8383,8383,8396,8396,8410,8410,8423,8423,8437,8437,8450,8450,8464,8464,8477,8477,8491,8491,8504,8504,8518,8518,8531,8531,8545,8545,8559,8559,8572,8572,8586,8586,8599,8599,8613,8613,8627,8627,8640,8640,8654,8654,8667,8667,
8681,8681,8695,8695,8709,8709,8723,8723,8736,8736,8750,8750,8764,8764,8778,8778,8792,8792,8805,8805,8819,8819,8833,8833,8847,8847,8861,8861,8875,8875,8889,8889,8903,8903,8917,8917,8931,8931,8944,8944,8958,8958,8972,8972,8986,8986,9000,9000,9014,9014,9028,9028,9042,9042,9056,9056,9070,9070,9084,9084,9099,9099,9113,9113,9127,9127,9141,9141,9155,9155,9169,9169,9183,9183,9197,9197,9211,9211,9225,9225,9240,9240,9254,9254,9268,9268,9283,9283,9297,9297,9311,9311,9326,9326,9340,9340,9354,9354,9368,9368,
9383,9383,9397,9397,9412,9412,9426,9426,9440,9440,9455,9455,9469,9469,9484,9484,9498,9498,9512,9512,9527,9527,9541,9541,9556,9556,9570,9570,9585,9585,9599,9599,9614,9614,9628,9628,9643,9643,9657,9657,9672,9672,9687,9687,9702,9702,9716,9716,9731,9731,9746,9746,9760,9760,9775,9775,9790,9790,9804,9804,9819,9819,9834,9834,9849,9849,9864,9864,9878,9878,9893,9893,9908,9908,9923,9923,9938,9938,9952,9952,9967,9967,9982,9982,9997,9997,10012,10012,10027,10027,10042,10042,10057,10057,10072,10072,10087,10087,10101,10101,
10117,10117,10132,10132,10147,10147,10162,10162,10177,10177,10192,10192,10207,10207,10222,10222,10237,10237,10252,10252,10268,10268,10283,10283,10298,10298,10313,10313,10328,10328,10344,10344,10359,10359,10374,10374,10389,10389,10404,10404,10420,10420,10435,10435,10450,10450,10466,10466,10481,10481,10496,10496,10512,10512,10527,10527,10542,10542,10557,10557,10573,10573,10588,10588,10604,10604,10619,10619,10635,10635,10650,10650,10666,10666,10681,10681,10697,10697,10712,10712,10728,10728,10744,10744,10759,10759,10775,10775,10790,10790,10806,10806,10822,10822,10837,10837,10853,10853,10868,10868,
10884,10884,10900,10900,10916,10916,10931,10931,10947,10947,10963,10963,10978,10978,10994,10994,11010,11010,11025,11025,11041,11041,11057,11057,11073,11073,11089,11089,11105,11105,11121,11121,11137,11137,11153,11153,11169,11169,11184,11184,11200,11200,11216,11216,11232,11232,11248,11248,11264,11264,11280,11280,11296,11296,11312,11312,11328,11328,11344,11344,11361,11361,11377,11377,11393,11393,11409,11409,11425,11425,11441,11441,11457,11457,11473,11473,11489,11489,11505,11505,11522,11522,11538,11538,11554,11554,11570,11570,11586,11586,11603,11603,11619,11619,11635,11635,11651,11651,11667,11667,
11684,11684,11700,11700,11717,11717,11733,11733,11749,11749,11766,11766,11782,11782,11799,11799,11815,11815,11831,11831,11848,11848,11864,11864,11881,11881,11897,11897,11914,11914,11930,11930,11947,11947,11963,11963,11980,11980,11996,11996,12013,12013,12030,12030,12046,12046,12063,12063,12079,12079,12096,12096,12113,12113,12129,12129,12146,12146,12162,12162,12179,12179,12196,12196,12213,12213,12230,12230,12246,12246,12263,12263,12280,12280,12297,12297,12314,12314,12330,12330,12347,12347,12364,12364,12381,12381,12398,12398,12415,12415,12432,12432,12449,12449,12466,12466,12483,12483,12499,12499,
12516,12516,12533,12533,12550,12550,12567,12567,12584,12584,12601,12601,12618,12618,12635,12635,12652,12652,12669,12669,12687,12687,12704,12704,12721,12721,12738,12738,12755,12755,12773,12773,12790,12790,12807,12807,12824,12824,12841,12841,12859,12859,12876,12876,12893,12893,12911,12911,12928,12928,12945,12945,12963,12963,12980,12980,12997,12997,13014,13014,13032,13032,13049,13049,13067,13067,13084,13084,13101,13101,13119,13119,13136,13136,13154,13154,13171,13171,13188,13188,13206,13206,13224,13224,13241,13241,13259,13259,13276,13276,13294,13294,13312,13312,13329,13329,13347,13347,13364,13364,
13382,13382,13400,13400,13418,13418,13435,13435,13453,13453,13471,13471,13488,13488,13506,13506,13524,13524,13541,13541,13559,13559,13577,13577,13595,13595,13613,13613,13630,13630,13648,13648,13666,13666,13684,13684,13702,13702,13719,13719,13737,13737,13755,13755,13773,13773,13791,13791,13809,13809,13827,13827,13845,13845,13863,13863,13881,13881,13898,13898,13917,13917,13935,13935,13953,13953,13971,13971,13989,13989,14007,14007,14025,14025,14043,14043,14061,14061,14079,14079,14098,14098,14116,14116,14134,14134,14152,14152,14170,14170,14189,14189,14207,14207,14225,14225,14243,14243,14261,14261,
14280,
};
