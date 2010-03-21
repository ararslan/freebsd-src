/*-
 * Copyright (C) 2004 Maxim Sobolev <sobomax@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/tools/regression/lib/libc/stdlib/test-sort.h,v 1.1.32.1 2010/02/10 00:26:20 kensmith Exp $
 */

#ifndef _TEST_SORT_H
#define _TEST_SORT_H

static int
sorthelp(const void *a, const void *b)
{
  const int *oa, *ob;

  oa = a;
  ob = b;
  /* Don't use "return *oa - *ob" since it's easy to cause overflow! */
  if (*oa > *ob)
    return 1;
  if (*oa < *ob)
    return -1;
  return 0;
}

/* Reference sorting routine (slooow!) */
static void
ssort(int v[], int nmemb)
{
  int i, j, k;

  for (i = 0; i < nmemb; i++) {
    for (j = i + 1; j < nmemb; j++) {
      if (v[j] < v[i]) {
        k = v[i];
        v[i] = v[j];
        v[j] = k;
      }
    }
  }
}

/* Some random data */
static int initvector[1024] = {
  599853225, 371951333, -428880425, 1450668530, 85530178, -460170550,
  -270680269, 717137591, 106244401, -1138072905, -113532586,
  599690958, 464993720, 107690177, 24249019, -1151018550, 794225588,
  1494905642, -62951716, -734531757, 1197251494, 1020063925,
  -634536734, -216634704, 617366508, -18840190, 481010395,
  -1555785724, 128221950, -1747743676, 1119012320, -252160437,
  617137855, 1159833073, -106647920, -1570719046, -769400990,
  -130308848, 1186546396, 215253591, 445832488, 160263176, 777264170,
  -274636650, -696134447, 1057957088, -626175254, 188632134,
  -98941793, -1602334908, -373717125, 885013862, 571258221,
  -399572192, 407761463, -733249776, 12094800, -367046815, 178974501,
  -452638559, -516580143, -94282073, 1411115180, -1151792797,
  1442815268, 1106583674, 515269284, -74019972, 598818901, 696848474,
  -657910766, -287309335, 1538095746, 143543003, 851444033,
  -947573348, 296222973, 1339592140, -947505360, 872027891,
  -418844714, -583075597, -324758197, -964531573, 1016795914,
  -866842580, -304084402, -286930819, 338975583, 803597943,
  -452483372, 1525283506, -1185830826, -596405894, 905191340,
  -1638026278, 106749913, 582771197, -730713796, 56052422,
  1498040174, 644967266, 182541575, 280483468, -1932835017,
  -435546874, 940106007, 1753388509, -340355019, -231577358,
  -714879035, 1051182949, 204261785, 1321346243, -895289878,
  -240369893, 566608506, -350777580, -1384849829, -876816409,
  1013787299, -1408035937, -222626650, 1708168486, -645148461,
  1854654, -393012507, 179327030, -1607975548, -715202732, 730588290,
  246968517, -550975254, -101136772, -174103176, 1188941016,
  2004650834, -1501389866, -2021225998, 1219042515, -464113898,
  268565342, 126451123, -1045877126, -198918003, 310177444,
  1578314812, 1828867082, 453336898, -908485523, 749777130,
  -1028565802, 61360571, 241484853, -175693399, 1816211059,
  533940889, -1496933703, 385185125, -821132413, -8923391,
  -1429546239, 46190992, 449247332, -20432494, 778761611, -178782699,
  -811194695, -632276211, 70196094, 890817525, -1447776908,
  -323783741, -62333222, 954929503, 247668507, -1394420605,
  367913886, 1364926759, 1298781924, 357923028, -73644747,
  -319744305, 61718202, -1454549286, 387493522, 2018321449,
  861026653, 289973298, 1755939093, -84772204, 43425266, -1325753781,
  -679938775, 1228500370, -763816405, 548903035, 1765563727,
  425183052, 1424621863, -188287424, 554385654, 751831998,
  1377088085, 66622090, 139224450, -1305816167, 650140724, 593988868,
  -444913321, 589045097, 1261428989, 101292769, -780376786,
  559307348, 1644593236, -1838606833, 53570301, -680576100,
  -44969538, 268718267, -632104125, 276904628, 626299449, -11761453,
  545899086, -1027343598, -432251872, 539353494, -399575006,
  -568383580, -677802882, 1296513472, 801202048, 806425805, 1983363,
  850487421, 38046173, 1535399484, 1998285544, -1301751898,
  -46561973, 56545408, -1107662676, 456041145, -452923904,
  -262219453, -371849200, 392524281, 1650231392, 1185585356,
  126610511, -1125389657, 1015981177, -1318481342, -213835789,
  1263484054, -654361441, 1408272041, -231555284, -1121778152,
  -395512897, 332277674, -349703586, 1809474399, -223731607,
  -1342224737, 736165236, 67535587, 89879082, 471445838, 423788300,
  -384354470, 907475706, 154886390, -1406736539, -8558766,
  -203405718, -422127884, 1048520863, 747418501, 87438975, 727668160,
  -914936981, 428266976, -455742009, -949014605, 487159058,
  -262526850, -309451504, -76928461, 1072951428, -1370953830,
  238231681, -1831047244, -405735199, -35941848, 469048670,
  505307987, -660553590, 876537439, -314195871, 999234339,
  -1405846240, -579885695, 629067031, 863481510, -742301385,
  -1723403128, -153070386, 782682839, -343111818, -877101810,
  1438467302, -319951459, -1585702508, -338381888, 484108815,
  -1726935191, -749923706, 1657932127, -816151395, -566321865,
  -133542331, 84961164, 598275578, 1302065347, -533098653,
  -1766383037, 53169714, -464201288, 617735133, 862536123,
  -141730724, -1967377125, -1023736305, -1012511106, 64484992,
  -1250856831, 426409332, -355670055, -298251663, -867634978,
  -776124819, 74018333, -425385214, -108004251, -1192766130,
  1294193867, -109867195, -78667637, 1164855393, -826007552,
  -522528066, 1160283046, -1095276403, -1218917472, -396475366,
  -77394733, -425603169, 251928357, -393559355, 1488845184,
  898455978, -773338691, -37627855, -345014717, 204298578, 209084274,
  1047080643, -414348222, 26496664, 705759824, 575149152, 604904761,
  624988690, 1446041250, 1000757225, -1354896151, 1422958189,
  -1607165311, -832757521, 365074225, 1171764999, 1200795217,
  -203957828, 23166236, -846818698, -547439867, -790192498,
  -122123561, 914298013, 66225525, -36163174, -480698856,
  -1269421818, 624641703, 254923102, 1564329013, -583609221,
  -649433551, -743396069, 1182455435, 102658744, 285599336,
  692480463, -852737563, -660090184, 1374350065, 72300985, 690541659,
  -1194212957, -1151816525, 157415641, 487398246, 1030153072,
  933723020, 1359181027, -1303457764, -1543773272, 774306017,
  -854382652, 755485667, -864943584, -63242545, -1271480354,
  157720215, -205001173, 889984130, -581583822, -473779111,
  -932136577, 735326252, 428638717, 1888884222, 561493709,
  -1966427364, -1710208603, 340121869, 918894036, 927172509,
  904178436, 1476687667, 90796414, 651591731, -550913123, -42218158,
  637756529, 1091478400, 124976584, -48739309, -798898083, 393581349,
  -1078624722, -789291577, 1010582542, -512317005, 1222773656,
  466454593, 1183558811, 822782663, -851624703, -850404012,
  1473672600, 852527073, 1073953362, 137635828, 936104739, -86567759,
  -882563252, 1845232980, -737978404, -104703380, 149802989,
  -349118325, 1479797538, 1966007488, 1254228842, 414304661,
  -790805785, 31583329, -76864151, 558202855, -1447047313, 716720607,
  -404224238, -54107627, 1747385914, -657407390, 202940208,
  1083067056, -532861378, 163426933, -130289277, 1301785258,
  -302920320, -637947485, -644895903, -1668027530, 391890467,
  -126586485, -536836984, -1154536413, -339505118, -1187229462,
  -670985870, -601310813, -1350055158, -482479784, 139847714,
  -253955849, 5190414, -542857077, 1175835684, -584165057,
  1132775766, -592091269, -891445655, -340995936, 736395810,
  779967964, 515095845, -1138437307, -259226729, -167820100,
  -801611617, -282451622, -1313679283, -1436126694, 1258773990,
  -717601098, -583559645, -1307478759, 1238647247, 1589011223,
  -1029216445, -107030650, 400152690, -1349079913, 1428582247,
  21546946, 208807686, -169450574, -1086213374, -1242715198,
  669098277, 416626722, -1122525014, -1389466669, -391843085,
  -56318357, 421040094, 212303518, 738666684, -1185364904,
  -506192760, 646735912, -1424722633, 745226976, 1019191717,
  -190891744, -310320868, -373655022, -665117060, 830760000,
  583906512, -330536027, 611092636, -321344259, -1255008904,
  -777959046, -523043472, 88896910, 346062204, -163734816, 336635665,
  906060268, -128891583, 740952564, 916767203, 296514859, 198670559,
  358136672, -152253676, 12038867, -1469916749, -1020980597,
  -897143313, 354240970, -97959800, 814172811, 1983363241, 264990663,
  105154676, 1060463014, 430172143, 375111946, -824526943,
  -708877751, -1377442616, -236559551, 684724584, 1602131358,
  -42140186, -763499840, -605167, 98575879, -376577598, 1689746083,
  -777973879, -1396984691, -187780326, 281040966, 1858859521,
  158395760, 1022807978, -218458812, 811779708, 1495113833,
  1192561226, 629539535, -1365196683, -1120253162, 1091681956,
  134286445, 1172218369, -34093658, -137087343, -27869226,
  -180889478, 55705436, 52362743, -1745516232, -926564477,
  -513701675, -1666272054, 1457952810, 843953275, -478275722,
  -1240291080, 101859661, -1606687523, 916365333, 314713310,
  -22002688, 1019022641, -1171741314, -129050627, -211955813,
  -1020176299, 1357865293, -609819628, 724533854, -1141449545,
  22285231, -97731145, -302329687, 191910894, -1300709885,
  -644951895, 640448036, -1289009824, 1445456129, 846416471,
  1821291740, -1639640821, -712724532, -447475807, 132156847,
  258067455, 324301319, 278586969, -1544082357, 636007277, 977122066,
  127462480, 365126129, 1086276825, -432124148, 896598926,
  -388550179, 273357331, -845018695, -1089465389, 384439820,
  -558419772, 1476422025, 730712769, 190665059, -764968927,
  -789708218, 637873581, 348429858, 1386000168, -638123594,
  -842010345, -607926448, 19535163, -742771490, -18323344, 246155488,
  350409468, 1290907730, -492566468, 300358636, 501876267, 252441807,
  1233551975, -1431067042, 517177374, -1540299707, -948380761,
  1253997663, 693795998, 148707823, 152894502, 98729538, -30042824,
  -563057441, 723726409, 367338961, 1395435261, 217868876,
  1220652431, 953572083, -1134905155, -734486813, -587470130,
  -864647866, 1030737023, 781798521, -321076732, -460548153,
  122681678, -873728847, -1286304399, -75472885, 113390881,
  -1556849198, -1070802176, 924389470, 957478910, 5974049, 709413506,
  476334647, 572869787, 776298405, -8822420, -99326499, -707855342,
  -1187216303, 668038414, 262454769, -1120293198, -32011040,
  249812104, -101835410, 1082281087, -570183855, -954535179,
  1384361473, -983199686, 2017611313, 328926483, -878162849,
  -1202254181, -225604951, 966898955, 247213529, -1257544612,
  -197005970, -1039902730, -1947925142, 1752780907, -313410699,
  -464474556, 416580338, -1063356643, -292212702, 57509168,
  1034124629, 1059212593, 468522867, 845369497, 1872717306,
  -1216544764, -1419907623, 1376869956, -66585488, -1590974467,
  -367070705, -1456529060, 791844031, 336217635, -1106832215,
  1476739427, -751018210, -1411671555, -1880387375, -1714242595,
  1169006474, -479442380, -892267555, -1471250266, -267888858,
  808634418, 1324777189, -585449929, 1127186951, 468768901,
  -2002989138, -52352849, 186493053, 1258464606, 117157186,
  445919258, 908401949, -1112221136, 863904453, -942718649,
  796754809, -38943966, -781978872, -56814078, 1273857459,
  -1781920832, 209979504, 811828269, -1150814437, 850061883,
  -532968763, 252506408, -885025629, 391567580, -1295702482,
  574894420, 1462248349, 1622584325, -88443443, -1122006092,
  -169758578, 456282338, -443233309, 436693483, -956563815,
  -480221349, 435252860, -1114099391, 1060053979, -470893945,
  -1273682879, -734596176, 639950927, -1278648701, 306274747,
  -410562146, 1137869228, -1970746553, 1313830798, 1248071822,
  -247297704, 1015218053, -1607348116, -261817613, -821413148,
  -782942639, -628711083, 240953091, -629550668, -1584736319,
  856616893, -186759752, 197905373, 541638393, 603407919, -278480495,
  410077039, 544065371, -1509627427, 402918436, -450463799,
  -131169308, 249920630, 1079548609, -927911828, 1444577689,
  -353002528, -224292462, 1247795279, -790844631, -40427503,
  59829765, -332587567, 1319862109, -1261340753, 121711726,
  1342756342, -643495787, 100326201, -934436714, -69134888,
  -898880561, -379524737, -577234570, -805827092, -1575493557,
  -289920678, -476605057, 1235714994, -317239591, 418553949,
  410053338, -204985448, 1206503615, 202610372, -932244873,
  782207875, -288661931, -806814809, 1270953679, 2060991595,
  -311412846, 327279979, 1148562672, 55239149, -610114433,
  -1511688434, 87619740, -433503545, 326150519, -581293393,
  -97417688, -289736140, -1543886029, -1251976119, 1585774446,
  1570011421, 432602745, 486343696, -834680922, 265004849,
  -1132107706, 502627197, -815873818, 249635389, 1985714127,
  -1095817653, -130743522, -645266828, -334621094, 199921747,
  1059256177, 378031303, 1519740920, 925540689, 1405957844,
  1387748290, -56138046, -770637828, -187984510, -1361735163,
  1294823206, -608941238, 451860688, -510549867, 1143516283,
  -779090703, 1459305047, -600335915, -1684168049, 1516622316,
  -631733335, -4360068, 499778796, 587600402, -1296000335, -37959743,
  -1084203927, 1162902556, 246374600, -515103645, 341724568,
  -702303954, 452229900, 485108287, 1170048553, -1510148355,
  611133912, 1997927484, -142022671, -724776653, -336090522,
  708283514, -1409637378, -2052637687, 376055110, 226628105,
  -1714452033, -1776158002, 369167930, 1800807012, 710680889,
  -69951947, -1223849766, -1862239787, 218536127, -656411794,
  -1202269188, 609634805, -224425858, 519797951, 284223080,
  869408930, 270750206, -544967439, 2097168510, 31650971, -600985417,
  -165303097, -257809088, -1043223971, 1827891621, -156827355,
  499719603
};

#define	IVEC_LEN	(sizeof(initvector) / sizeof(initvector[0]))

#endif
