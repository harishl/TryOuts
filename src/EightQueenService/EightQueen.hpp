#include <array>

namespace EightQueenLambda
{
using namespace std;

static constexpr size_t boardSz = 8;    
class EightQueenBoard 
{
public:
    void printBoard() const;
    void reset();
    bool toggleQueen(size_t r, size_t c);
    bool verifySolution() const;

private:
    array<array<bool, boardSz>, boardSz> eightQueenBoard {};
    unsigned short currentQueenCount = 0;
}; 
} // end namespace EightQueenLambda