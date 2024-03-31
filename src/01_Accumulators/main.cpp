
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

#include <string>
#include <iostream>
#include <unordered_map>

using Accumulator = 
    boost::accumulators::accumulator_set<
        double, 
        boost::accumulators::stats<
            boost::accumulators::tag::count,
            boost::accumulators::tag::max,
            boost::accumulators::tag::mean,
            boost::accumulators::tag::variance,
            boost::accumulators::tag::sum
        >
    >;

static bool profile = false;
static std::unordered_map<std::string, Accumulator> stats;
static std::unordered_map<std::string, std::list<double>> chart;

void OnRequest(const std::string& route, double t)
{
    // --> Start timer
    
    // === Parseing the request ===
    // === Build the response ===
    
    // --> Stop timer
    if (profile)
    {
        stats[route](t);
    }

    // === Send the respose ===
}

void Cycle1S()
{
    for (auto& acc : stats)
    {
        using namespace boost::accumulators;
        chart[acc.first].push_back(mean(acc.second));
    }
}

int main()
{
    // === Start a web server ===

    profile = true;
    for (size_t i = 0; i < 20; i++)
    {
        if (i == 0)
        {
            OnRequest("index", 20);
            OnRequest("imprint", 10);
        }
        else
        {
            OnRequest("index", 5 + i / 3);
            if (i % 2 == 0)
            {
                OnRequest("imprint", 2 + i / 4);
            }
        }
    }

    // === Collect metrics ==
    for (auto& acc : stats)
    {
        using namespace boost::accumulators;

        std::cout << acc.first
            << ": #" << count(acc.second)
            << " =" << mean(acc.second)
            << " ~" << variance(acc.second)
            << " (+" << max(acc.second) << ")"
            << " ==" << sum(acc.second) 
            << std::endl
            ;
    }

    return 0;
}
