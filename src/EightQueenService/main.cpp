#include <cstdio>
#include <vector>
#include <string>
#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include "EightQueen.hpp"

using namespace std;
using namespace aws::lambda_runtime;
using namespace EightQueenLambda;

static invocation_response my_handler(invocation_request const& req)
{
    EightQueenBoard eqb;
    using namespace Aws::Utils::Json;
    JsonValue json(req.payload);
    if (!json.WasParseSuccessful()) {
        return invocation_response::failure("Failed to parse input JSON", "InvalidJSON");
    }
    auto v = json.View();
    for (int i=1; i<=8; i++)
    {
        string key { "q" + to_string(i) };
        if(!v.ValueExists(key) || !v.GetObject(key).IsObject())
        {
            return invocation_response::failure("keys missing or malformed", "InvalidJSON");
        }

        auto objval = v.GetObject(key);
        if(!objval.ValueExists("r") || !objval.GetObject("r").IsIntegerType() ||
            !objval.ValueExists("c") || !objval.GetObject("c").IsIntegerType())
        {
            return invocation_response::failure("malformed r and c in json", "InvalidJSON");
        }
        size_t row = static_cast<size_t>(objval.GetInteger("r"));
        size_t col = static_cast<size_t>(objval.GetInteger("c"));
        eqb.toggleQueen(row, col);
    }

    JsonValue response;
    response.WithBool("valid", eqb.verifySolution());

    return invocation_response::success(response.View().WriteCompact(), "application/json");
}

int main()
{
    run_handler(my_handler);
    return 0;
}

// int main()
// {
//     EightQueenBoard eqb;

//     auto buildBoard = [&board=eqb] (const vector<size_t>&& input)
//     {
//         board.reset();
//         int i = 0;
//         for (auto j : input) 
//         {
//             board.toggleQueen(i, j); 
//             i++; 
//         }
//     };

//     auto verify = [&board=eqb] ()
//     {
//         bool pass = board.verifySolution();
//         board.printBoard();
//         if (pass) { printf("success!\n"); }
//         else { printf("try again\n"); }
//     };

//     buildBoard({0, 1, 2, 3, 4, 5, 6, 7});
//     verify();

//     buildBoard({1, 4, 6, 3, 0, 7, 5, 2});
//     verify();

//     buildBoard({1, 4, 6, 3, 0, 7, 5});
//     verify();

//     buildBoard({1, 7, 6, 3, 0, 7, 4});
//     verify();
// }