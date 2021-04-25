//
// Created by Harper on 4/23/21.
//

#ifndef LEETCODE_LC132_H
#define LEETCODE_LC132_H

#include <string>
#include <cstring>
#include <assert.h>
#include <vector>
#include <unordered_map>

using namespace std;

namespace lc132 {
    class Solution {
    private:
        uint32_t *trace_;
    public:
        int minCut(string s) {
            int length = s.size();

            unordered_map<int, vector<int>> edges;

            for (int i = 0; i < length - 1; ++i) {
                if (s[i] == s[i + 1]) {
                    // Try the even Palindrome
                    int j = 0;
                    while (i - j >= 0 && i + 1 + j < length) {
                        if (s[i - j] == s[i + 1 + j]) {
                            if (edges.find(i - j) == edges.end()) {
                                edges[i - j] = vector<int>();
                            }
                            edges[i - j].push_back(i + 1 + j + 1);
                            j++;
                        } else {
                            break;
                        }
                    }
                }
                int j = 1;
                while (i - j >= 0 && i + j < length) {
                    if (s[i - j] == s[i + j]) {
                        if (edges.find(i - j) == edges.end()) {
                            edges[i - j] = vector<int>();
                        }
                        edges[i - j].push_back(i + j + 1);
                        j++;
                    } else {
                        break;
                    }
                }
            }

            // Look for shortest paths from 0 to length
            uint32_t shortest[length + 1];

            for (int i = 0; i <= length; ++i) {
                shortest[i] = INT32_MAX;
            }
            shortest[0] = 0;
            vector<int> scan;
            scan.push_back(0);

            uint8_t visited[length + 1];
            memset(visited, 0, length + 1);
            uint8_t scheduled[length + 1];
            memset(scheduled, 0, length + 1);

            int pointer = 0;
            while (pointer < scan.size()) {
                int current = scan[pointer++];
                visited[current] = 1;
                if (current == length) {
                    break;
                }
                auto found = edges.find(current);
                if (found == edges.end()) {
                    if (!visited[current + 1]) {
                        if (shortest[current + 1] > shortest[current] + 1) {
                            shortest[current + 1] = shortest[current] + 1;
                        }
                        if (!scheduled[current + 1]) {
                            scan.push_back(current + 1);
                            scheduled[current + 1] = 1;
                        }
                    }
                } else {
                    if (!visited[current + 1]) {
                        if (shortest[current + 1] > shortest[current] + 1) {
                            shortest[current + 1] = shortest[current] + 1;
                        }
                        if (!scheduled[current + 1]) {
                            scan.push_back(current + 1);
                            scheduled[current + 1] = 1;
                        }
                    }
                    for (auto &next: found->second) {
                        if(!visited[next]) {
                            if (shortest[next] > shortest[current] + 1) {
                                shortest[next] = shortest[current] + 1;
                            }
                            if(!scheduled[next]) {
                                scan.push_back(next);
                                scheduled[next] = 1;
                            }
                        }
                    }
                }
            }

            return shortest[length] - 1;
        }
    };

    class Solution2 {
    public:
        int minCut(string s) {
            int length = s.size();

            // trace[i][j] is the minimal cut between [i][j]
            uint32_t trace[length][length];
            memset(trace, INT32_MAX, length * length * sizeof(int));

            for (int i = 0; i < length; ++i) {
                trace[i][i] = 0;
            }
            for (int i = 0; i < length - 1; ++i) {
                trace[i][i + 1] = (s[i] != s[i + 1]);
            }

            for (int i = 2; i < length; ++i) {
                for (int j = 0; j < length - i; ++j) {
                    // Compute entry (j,j+i)
                    // entry (j, j+i) can grow from entry (j+1, j+i-1) if s[j] == s[j+i]
                    if (s[j] == s[j + i] && trace[j + 1][j + i - 1] == 0) {
                        trace[j][j + i] = 0;
                    } else {
                        auto min = trace[j][j + i];
                        for (int k = j; k < j + i; ++k) {
                            if (trace[j][k] + trace[k + 1][j + i] + 1 < min) {
                                min = trace[j][k] + trace[k + 1][j + i] + 1;
                            }
                        }
                        trace[j][j + i] = min;
                    }

                }
            }
            return trace[0][length - 1];
        }
    };

    void run() {
        Solution solution;

//        {
//            assert(1 == solution.minCut("aab"));
//        }
//        {
//            assert(0 == solution.minCut("a"));
//        }
//        {
//            assert(1 == solution.minCut("ab"));
//        }
//        {
//            assert(0 == solution.minCut("efe"));
//        }
//        {
//            assert(3 == solution.minCut("ccaacabacb"));
//        }
//        {
//            assert(1 == solution.minCut("aaabaa"));
//        }
        {
            std::cout << solution.minCut(
                    "fiefhgdcdcgfeibggchibffahiededbbegegdfibdbfdadfbdbceaadeceeefiheibahgececggaehbdcgebaigfacifhdbe"
                    "cbebfhiefchaaheiichgdbheacfbhfiaffaecicbegdgeiaiccghggdfggbebdaefcagihbdhhigdgbghbahhhdagbdaefec"
                    "cfiaifffcfehfcdiiieibadcedibbedgfegibefagfccahfcbegdfdhhdgfhgbchiaieehdgdabhidhfeecgfiibediiafac"
                    "agigbhchcdhbaigdcedggehhgdhedaebchcafcdehcffdiagcafcgiidhdhedgaaegdchibhdaegdfdaiiidcihifbfidech"
                    "icighbcbgibadbabieaafgeagfhebfaheaeeibagdfhadifafghbfihehgcgggffgbfccgafigieadfehieafaehaggeeaaa"
                    "ehggffccddchibegfhdfafhadgeieggiigacbfgcagigbhbhefcadafhafdiegahbhccidbeeagcgebehheebfaechceefdi"
                    "afgeddhdfcadfdafbhiifigcbddahbabbeedidhaieagheihhgffbfbiacgdaifbedaegbhigghfeiahcdieghhdabdggfcg"
                    "bafgibiifdeefcbegcfcdihaeacihgdchihdadifeifdgecbchgdgdcifedacfddhhbcagaicbebbiadgbddcbagbafeadhd"
                    "daeebdgdebafabghcabdhdgieiahggddigefddccfccibifgbfcdccghgceigdfdbghdihechfabhbacifgbiiiihcgifhdb"
                    "hfcaiefhccibebcahidachfabicbdabibiachahggffiibbgchbidfbbhfcicfafgcagaaadbacddfiigdiiffhbbehaaaci"
                    "dggfbhgeaghigihggfcdcidbfccahhgaffiibbhidhdacacdfebedbiacaidaachegffaiiegeabfdgdcgdacfcfhdcbfiaa"
                    "ifgfaciacfghagceaaebhhibbieehhcbiggabefbeigcbhbcidbfhfcgdddgdffghidbbbfbdhcgabaagddcebaechbbiege"
                    "iggbabdhgghciheabdibefdfghbfbfebidhicdhbeghebeddgfdfhefebiiebdchifbcbahaddhbfafbbcebiigadhgcfbeb"
                    "gbebhfddgdeehhgdegaeedfadegfeihcgeefbbagbbacbgggciehdhiggcgaaicceeaefgcehfhfdciaghcbbgdihbhecfbg"
                    "ffefhgiefgeiggcebgaacefidghdfdhiabgibchdicdehahbibeddegfciaeaffgbefbbeihbafbagagedgbdadfdggfeaeb"
                    "aidchgdbcifhahgfdcehbahhdggcdggceiabhhafghegfdiegbcadgaecdcdddfhicabdfhbdiiceiegiedecdifhbhhfhgd"
                    "bhibbdgafhgdcheefdhifgddchadbdggiidhbhegbdfdidhhfbehibiaacdfbiagcbheabaaebfeaeafbgigiefeaeheabif"
                    "gcfibiddadicheahgbfhbhddaheghddceedigddhchecaghdegigbegcbfgbggdgbbigegffhcfcbbebdchffhddbfhhfgeg"
                    "ggibhafiebcfgeaeehgdgbccbfghagfdbdfcbcigbigaccecfehcffahiafgabfcaefbghccieehhhiighcfeabffggfchfd"
                    "gcfhadgidabdceediefdccceidcfbfiiaidechhbhdccccaigeegcaicabbifigcghcefaafaefd") << '\n';
        }
    }
}

#endif //LEETCODE_LC132_H
