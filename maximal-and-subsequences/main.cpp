#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <bitset>

using namespace std;

long long pow(int a, int b, int MOD)
{
	long long x = 1, y = a;
	while (b > 0)
	{
		if (b % 2 == 1)
		{
			x = (x*y);
			if (x>MOD) x %= MOD;
		}
		y = (y*y);
		if (y>MOD) y %= MOD;
		b /= 2;
	}
	return x;
}

long long InverseEuler(int n, int MOD)
{
	return pow(n, MOD - 2, MOD);
}

long long C(int n, int r, int MOD)
{
	vector<long long> f(n + 1, 1);
	for (int i = 2; i <= n; i++)
		f[i] = (f[i - 1] * i) % MOD;
	return (f[n] * ((InverseEuler(f[r], MOD) * InverseEuler(f[n - r], MOD)) % MOD)) % MOD;
}


int main()
{
	ios::sync_with_stdio(false);

	int n, k;
	cin >> n >> k;

	vector<uint64_t> v(n);
	for (size_t i = 0; i < n; i++)
	{
		cin >> v[i];
	}

	vector<uint64_t> set;
	int64_t curr_pos = 64;

	while (--curr_pos >= 0)
	{
		uint64_t mask = 1ULL << curr_pos;

		vector<uint64_t> tmp;
		copy_if(v.begin(), v.end(), back_inserter(tmp),
			[&](uint64_t x) { return x & mask; });

		if (set.empty() && tmp.size() >= k)
		{
			set = tmp;
		}
		
		if (!set.empty() && tmp.size() >= k)
		{
			int64_t new_cnt = count_if(set.begin(), set.end(),
				[&](uint64_t x) { return x & mask; });

			if (new_cnt >= k)
			{
				auto iter = remove_if(set.begin(), set.end(),
					[&](uint64_t x) { return !(x & mask); });
				set.erase(iter, set.end());
			}
		}
	}

	uint64_t max_val = set.empty() ? 0 : set[0];
	for (size_t i = 1; i < set.size(); i++)
	{
		max_val &= set[i];
	}

	cout << max_val << "\n" << C(set.empty() ? n : set.size(), k, 1000000007);

	return 0;
}
