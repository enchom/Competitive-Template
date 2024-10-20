#include <vector>
#include <string.h>
#include <iostream>
using namespace std;

namespace tmpl
{
    /**
    Container must supported indexation and elements must support equality

    Returns 0-based sequence of matches
    **/
    template <typename Container>
    vector<int> kmp(Container pattern, int n, Container text, int m)
    {
        vector<int> F(n + 1, 0);
        vector<int> matches;

        for (int i = 1; i < pattern.size(); i++)
        {
            int cur = F[i];

            while(cur != 0 && pattern[cur] != pattern[i])
            {
                cur = F[cur];
            }

            if (cur == 0)
            {
                if (pattern[0] == pattern[i])
                    F[i + 1] = 1;
                else
                    F[i + 1] = 0;
            }
            else
            {
                F[i + 1] = cur + 1;
            }
        }

        int cur = 0;
        for (int i = 0; i < m; i++)
        {
            while (pattern[cur] != text[i] && cur != 0)
            {
                cur = F[cur];
            }

            if (cur == 0)
            {
                if (pattern[cur] == text[i])
                    cur = 1;
                else
                    cur = 0;
            }
            else
            {
                cur++;
            }


            if (cur == n)
            {
                matches.push_back(i - n + 1);
                cur = F[cur];
            }
        }

        return matches;
    }
}

int main()
{
    string a = "abc", b = "xabcxabc";
    auto x = tmpl::kmp(a, a.length(), b, b.length());

    for (auto m : x)
    {
        printf("%d\n", m);
    }
}
