#include <algorithm>
#include <ios>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "utils.hpp"

class Solution {
  constexpr static std::string_view vowels{"aeiou"};

  public:
  Solution() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
  }
  int findTheLongestSubstring(std::string s) {
    int ans = 0;
    int mask = 0;
    std::vector<int> first(1 << vowels.size(), s.size());
    first[0] = -1;
    for (auto i = 0; i < s.size(); ++i) {
      const auto vowel_idx = vowels.find(s[i]);
      if (vowel_idx != std::string_view::npos) {
        mask ^= 0x1 << vowel_idx;
      }
      ans = std::max(ans, i - first[mask]);
      if (first[mask] == s.size()) {
        first[mask] = i;
      }
    }
    return ans;
  }
};

#include <gtest/gtest.h>

TEST(Test, Example1) {
  std::string input = "eleetminicoworoep";
  ASSERT_EQ(13, Solution().findTheLongestSubstring(input));
}

TEST(Test, Example2) {
  std::string input = "leetcodeisgreat";
  ASSERT_EQ(5, Solution().findTheLongestSubstring(input));
}

TEST(Test, Example3) {
  std::string input = "bcbcbc";
  ASSERT_EQ(6, Solution().findTheLongestSubstring(input));
}

TEST(Test, Example4) { ASSERT_EQ(1, Solution().findTheLongestSubstring("id")); }

TEST(Test, Example5) {
  ASSERT_EQ(
      2870,
      Solution().findTheLongestSubstring(
          "lcwbgnkxnooovtxtuuolbgvieqyxdzyngkdaxuhgwzmgjjvylhavhtijfzvwdalxewsy"
          "mpoyvdhtlbchfgnexmmslcbrozsljwlxzkladmjibvyqpibpkwnxosrqhfqbmigkgxdt"
          "fnnsitxecihwisfonaejqeenboqxpqxbmdwzxjnodurnznaitbjikqaerbgkxdfjxnqy"
          "ecqpqcnluezomtkvjprcqeaucgttwlpqeyfwenybcluxwzjvixlljnmpolktwnezewpi"
          "uwinsptbjqzplpeoeuwpehkycvrsslfznunjihtauplcipxmobnipqekegxmddzkepuq"
          "zoqepebgwmkuxipjbncgaskmzjhjnlokvxidvlbjgxsdtxiaikdmojrilepbdmokaouh"
          "ekegpfjlhuywvgtbtozivvooplnnchlbkdvmrwwpkegczippokorcptixrudwszencxe"
          "mdnxrgearvtddcukdvsrulnvmcnuojxynomtrteotpmdkiueivbdyfxvbakkbfnotanr"
          "smdvmbaehqpumkejtessereyeshxgagprozlpunqanhwmitayqkdzqyhnieqosyrlidx"
          "xxcwlmolnvqopmrabpkyhdalcwfwpdheoxcfuiypwlfhbjuorrotjhajpeggfjcifmuz"
          "yszjxyfomvczltlhazrtfotejmekkiaegiguabubojhqyudxctegfanffokbotqlwjse"
          "rtqbhdophqkdvjeiunidaalqfbkfbbaihaxjpxxtupkscgflwxczlelgomoltschhdhc"
          "xjqlcdstlhrjyujzdfwngoeygcncmeshjitqxspmddvlopvmgskeuikugtbvmikzdueg"
          "lpuksbbwoeopqygziitejdkhkkgydngnyeqrcmamemltyqmtexvcyvqhygppmywkiraq"
          "yqwxxiamxqmeftidndwpmbpcschkmtvvklwvyihneyhvmtxbhgseskfdygnbqkrywllv"
          "wnhlymchoelulcoqznmyicooveiwwazqlnhlwozkoqyaezwyhzwdhilhsfollwbwvfmr"
          "llvrsnjqiocbdrixjzgnrszghicnmvqjjtpcnhwgpdqlsyrcbckhocgboecvpczbepew"
          "pnpjatirudtcurrtlbhrvreaymbekvmrzctyojkgnpcmyizauvudjxhssmamcuschcnq"
          "orjqybepptlerdgirzapuvsoeekmoitoszlwmyvtscagrhhtvlnrydcayhukhxgqfrcq"
          "fbjuiswvklnlygatspefmafailygnvgzhnvsgnsmbfsaugdbjermtlfsyvffqepucofz"
          "yjilohswbxhugzzihzxwnxwiwhlzpnzgoqvqzkbhhrendrcynnqmtodzgbmgrwgnqxqw"
          "tqtpyludmuvyjqzlkfnvzrhgchcivnxhpuibmlmongbjheekvvxrvjtsonvjlxkihomx"
          "kbsygzyvdvuehlewqoymiankekcgmgmtqrcvuogdezmdmyqsxzyhoyprcfyalbsoeypm"
          "gxgtbkgpixfrpqxqnbegajnwcfuamjqejefjqhzzvjzotgqgwbgtmklvmybvmcfpeljf"
          "bwpollltqxrgyrehnzvchijrokuoapwpeanmfjrwmgsvmzxwahupklojcbqkfeblphtu"
          "wbbapooynhmfdhjjhadgnvjpyizjduoeikzjsrkbjgioqxqhyakodcnlibewwuqjlzkm"
          "fybokfthpftnrmdjyctofsnpuexcarwrpstrehbrzjnzvsoislrkqlsbfnhpulvixxyh"
          "ctijqybjppwfcvsqrgbssqkjcrthsufevxnutkuwgtyovfaygbacmzlngfanbhbmdllr"
          "temqudxkpuaohmrcntsmalqjhmpmlbbntnsfwekgepnkyyalllxczymewubebxjikbce"
          "ehkgyfognlejzsfoasfxudbxenvjqygbctqyqrwnxiwprooustcskdjhybhdgfuymymu"
          "eshrugpwsuevxuydmolvatzpupybhtjfqtpcxkciwzqjverubkceqwefvyatrabcyrlp"
          "bvquvrcoosvailoclcffysasmgsvhepdlqvptdxtrvfqjdjctdskrosxsjojyqozzros"
          "ejsicvjbsmwepsuyxwkvidsjnhhmrscmveibviyhkcimdehpkonycqsobngmssvyitty"
          "eembauboalqokzfwvgxotgvgmkywoiifjvcyttrcqtpssrhdpdoqrfdwukqwzmshqdzo"
          "hdycpisqjaktzvzmhneqsocpinxzrsrcwdmdimbcrlcmvppxvuufmbimvmmoawvhrecp"
          "mgdywwogmumnaziaybpxneytfxgqmjcrbnweofjbujsjbtqkjbpcfxuyvytmwupiozan"
          "bjyblgkfhecbdejkpsstpamsrmhxqerydnrmhratsrknzmruvgenfdsdxjflppyqfsiu"
          "whicwqkhuztrhiyfuebolethjxbnopxbfrmzvvpuxkjiflvqxxlcynhwldlhwclvrvvv"
          "jbslqamvdaasfodglcqemfotdqiwpzflveduecumffhzjdbtgatwgazuowgtmjekltmd"
          "zttgkanoxgfaqiohzccgtxehzhwrlqqasqgobdfnevzpqhhblfzrvfnrhilyyuztrgjs"
          "hdrbkjrfxenkrjtayurhakpbgmdowuzmprrgyyodvugyyufuitwiaczvvmazgqkiusgy"
          "preobmqmmbubjlhxgorppbyrgdkwjnxzhwxfisivrsldvwlnqnophdfqtotobdcmmyig"
          "uvpsvvltmrqzdsahpmiticfmdzb"));
}
