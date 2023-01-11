#include <iostream>
#include <string>

class Solution
{
public:
    std::string toRoman(int n)
    {
        const auto unitsToRoman = [] (int numLessThan10) -> std::string
        {
            switch (numLessThan10)
            {
                case 1:
                    return std::string("I");
                case 2:
                    return std::string("II");
                case 3:
                    return std::string("III");
                case 4:
                    return std::string("IV");
                case 5:
                    return std::string("V");
                case 6:
                    return std::string("VI");
                case 7:
                    return std::string("VII");
                case 8:
                    return std::string("VIII");
                case 9:
                    return std::string("IX");
                default:
                    return std::string();
            }
        };

        const auto tensToRoman = [] (int numLessThan100) -> std::string
        {
            switch (numLessThan100)
            {
                case 1:
                    return std::string("X");
                case 2:
                    return std::string("XX");
                case 3:
                    return std::string("XXX");
                case 4:
                    return std::string("XL");
                case 5:
                    return std::string("L");
                case 6:
                    return std::string("LX");
                case 7:
                    return std::string("LXX");
                case 8:
                    return std::string("LXXX");
                case 9:
                    return std::string("XC");
                default:
                    return std::string();
            }
        };

        const auto hunderedsToRoman = [] (int numLessThan1000) -> std::string
        {
            switch (numLessThan1000)
            {
                case 1:
                    return std::string("C");
                case 2:
                    return std::string("CC");
                case 3:
                    return std::string("CCC");
                case 4:
                    return std::string("CD");
                case 5:
                    return std::string("D");
                case 6:
                    return std::string("DC");
                case 7:
                    return std::string("DCC");
                case 8:
                    return std::string("DCCC");
                case 9:
                    return std::string("CM");
                default:
                    return std::string();
            }
        };

        const auto thousandsToRoman = [] (int numLessThan4000) -> std::string
        {
            switch (numLessThan4000)
            {
                case 1:
                    return std::string("M");
                case 2:
                    return std::string("MM");
                case 3:
                    return std::string("MMM");
                default:
                    return std::string();
            }
        };

        std::string roman = thousandsToRoman(n/1000) 
                            + hunderedsToRoman(n/100 - 10*(n/1000))
                            + tensToRoman(n/10 - 10*(n/100))
                            + unitsToRoman(n%10);
        return roman;
    }
};

int main()
{
    Solution s;
    std::cout << s.toRoman(3999) << std::endl;
}