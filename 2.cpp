#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <string>

std::string input = "1208	412	743	57	1097	53	71	1029	719	133	258	69	1104	373	367	365\n"
  "4011	4316	1755	4992	228	240	3333	208	247	3319	4555	717	1483	4608	1387	3542\n"
  "675	134	106	115	204	437	1035	1142	195	1115	569	140	1133	190	701	1016\n"
  "4455	2184	5109	221	3794	246	5214	4572	3571	3395	2054	5050	216	878	237	3880\n"
  "4185	5959	292	2293	118	5603	2167	5436	3079	167	243	256	5382	207	5258	4234\n"
  "94	402	126	1293	801	1604	1481	1292	1428	1051	345	1510	1417	684	133	119\n"
  "120	1921	115	3188	82	334	366	3467	103	863	3060	2123	3429	1974	557	3090\n"
  "53	446	994	71	872	898	89	982	957	789	1040	100	133	82	84	791\n"
  "2297	733	575	2896	1470	169	2925	1901	195	2757	1627	1216	148	3037	392	221\n"
  "1343	483	67	1655	57	71	1562	447	58	1561	889	1741	1338	88	1363	560\n"
  "2387	3991	3394	6300	2281	6976	234	204	6244	854	1564	210	195	7007	3773	3623\n"
  "1523	77	1236	1277	112	171	70	1198	86	1664	1767	75	315	143	1450	1610\n"
  "168	2683	1480	200	1666	1999	3418	2177	156	430	2959	3264	2989	136	110	3526\n"
  "8702	6973	203	4401	8135	7752	1704	8890	182	9315	255	229	6539	647	6431	6178\n"
  "2290	157	2759	3771	4112	2063	153	3538	3740	130	3474	1013	180	2164	170	189\n"
  "525	1263	146	954	188	232	1019	918	268	172	1196	1091	1128	234	650	420\n";

int main() {
  int start = 0;
  std::vector<std::vector<int> > parsed;
  std::vector<int> *current = new std::vector<int>();
  while( start < input.size()) {
    int end = start;
    while(input[end] != '\t' && input[end] != '\n') end++;
    current->push_back(atoi(input.substr(start, end).c_str()));
    if(input[end] == '\n') {
      parsed.push_back(*current);
      delete current;
      current = new std::vector<int>();
    }
    end++;
    start = end;
  }
  delete current;
  int result = 0;

  for(int i = 0; i < parsed.size(); ++i) {
    int largest =  parsed[i][0];
    int smallest =  parsed[i][0];
    for(int j = 1; j < parsed[i].size(); ++j) {
      largest = std::max(largest, parsed[i][j]);
      smallest = std::min(smallest, parsed[i][j]);
    }
    result += largest - smallest;
  }
  std::cout << result << std::endl;

  int result2 = 0;
  for(int i = 0; i < parsed.size(); ++i) {
    for(int j = 0; j < parsed[i].size(); ++j) {
      for(int k = j+1; k < parsed[i].size(); ++k) {
        if((parsed[i][j]%parsed[i][k])==0) {
          result2 += parsed[i][j] / parsed[i][k];
        } else if((parsed[i][k]%parsed[i][j])==0) {
          result2 += parsed[i][k] / parsed[i][j];
        }
      }
    }
  }
  std::cout << result2 << std::endl;

}
