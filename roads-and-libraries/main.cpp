#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <memory>

using namespace std;

struct query_t
{
    map<std::uint64_t, std::shared_ptr<vector<std::uint64_t>>> city;

    std::uint64_t library_cost;
    std::uint64_t road_cost;

	void read()
	{
		std::uint64_t n, m;
		cin >> n >> m;

		cin >> library_cost >> road_cost;

		for (std::uint64_t i = 1; i <= n; i++)
		{
			city.insert(make_pair(i, make_shared<vector<std::uint64_t>>(1, i)));
		}

		while (m--)
		{
			std::uint64_t x, y;
			cin >> x >> y;

			auto x_list = city[x];
			auto y_list = city[y];

			if (x_list != y_list)
			{
				x_list->insert(x_list->end(), y_list->begin(), y_list->end());
				
				std::vector<std::uint64_t> buffer(y_list->begin(), y_list->end());
				for_each(buffer.begin(), buffer.end(),
					[&](std::uint64_t i)
				{
					city[i] = x_list;
				});
			}
		}
	}

    std::uint64_t calculate()
    {
        if (library_cost < road_cost)
        {
            return city.size() * library_cost;
        }

        std::uint64_t cost = 0;

        for (auto& node : city)
        {
            std::uint64_t size = node.second->size();

            if (size)
            {
                cost += library_cost;
                cost += (size - 1) * road_cost;
                node.second->clear();
            }
        }

        return cost;
    }
};

int main()
{
    int q;
    cin >> q;

    vector<query_t> n(q);
	for_each(begin(n), end(n), 
		[](query_t& q)
	{
		q.read();
	});

    vector<std::uint64_t> r;
    transform(begin(n), end(n), back_inserter(r),
        [](query_t q)
    {
        return q.calculate();
    });

    copy(begin(r), end(r),
        ostream_iterator<std::uint64_t>(cout, "\n"));

    return 0;
}
