#include <cmath>
#include <cstdio>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

uint32_t getHightBit(uint32_t v)
{
	if (!v)
		return 0;

	uint32_t chk = 1u << 31;

	int res = 31;

	while (chk)
	{
		if (chk & v)
			return res;

		--res;

		chk >>= 1;
	}

	return res;
}

uint32_t solve(vector<uint32_t> v)
{
    unordered_set<uint32_t> perm(v.begin(), v.end());

    if (perm.size() == 1)
    {
        return 0;
    }
    
    uint32_t max_idx = 0;

	for (auto& x : perm)
	{
		uint32_t idx = getHightBit(x);

		max_idx = std::max(max_idx, idx);
	}

	uint32_t mask = 1u << max_idx;
	unordered_set<uint32_t> high_perm;

	for (auto& x : perm)
	{
		if (mask & x)
			high_perm.insert(x);
	}

	uint32_t result = std::numeric_limits<uint32_t>::max();

	if (high_perm.size() < perm.size())
	{
		for (auto& x : perm)
		{
			if ((mask & x) == 0)
			{
				for (auto& y : high_perm)
				{
					result = min(result, x ^ y);
				}
			}
		}
	}
	else
	{
		for (auto& x : v)
		{
			x ^= mask;
		}

		result = solve(v);
	}

	return result;
}

int main()
{
	uint32_t n;
	cin >> n;

	vector<uint32_t> v(n);
	for (auto& x : v)
	{
		cin >> x;
	}

	cout << solve(v);
}
