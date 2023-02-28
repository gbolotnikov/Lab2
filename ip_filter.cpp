#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

using FilterHandler = bool(*)(const std::array<uint8_t, 4>& ip);

auto split(const std::string &str, char d)
{
    std::vector<std::string> r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(str.substr(start));
    return r;
}

auto strToNum(const std::vector<std::string>& vectror) {
    std::array<uint8_t, 4> ip;
    for(uint8_t i = 0; i < ip.size(); ++i) {
        ip[i] = std::stoi(vectror[i]);
    }
    return ip;
}

void read(std::vector<std::array<uint8_t, 4>>& ip_pool) {
    for(std::string line; std::getline(std::cin, line);) {
        auto v = split(line, '\t');
        ip_pool.push_back(strToNum(split(v.at(0), '.')));
    }
}

void write(const std::vector<std::array<uint8_t, 4>>& ip_pool, FilterHandler filter) {
    for(auto ip = ip_pool.begin(); ip != ip_pool.end(); ++ip) {
        if (filter(*ip)) {
            for(auto ip_part = ip->begin(); ip_part != ip->end(); ++ip_part) {
                if (ip_part != ip->begin()) {
                    std::cout << ".";
                }
                std::cout << unsigned(*ip_part);
            }
            std::cout << std::endl;
        }       
    }
}


void sort(std::vector<std::array<uint8_t, 4>>& ip_pool) {
    std::sort(ip_pool.begin(), ip_pool.end(), [](const auto& ip1, const auto& ip2) {       
        for (uint8_t i = 0; i < std::min(ip1.size(), ip2.size()); ++i) {
            if (ip1[i] == ip2[i]) {
                continue;
            }
            return ip1[i] > ip2[i];
        }
        return false;
    });
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::array<uint8_t, 4>> ip_pool;
        read(ip_pool);
        sort(ip_pool);
        write(ip_pool, [](const std::array<uint8_t, 4>& ip) {
            return true;
        });
        write(ip_pool, [](const std::array<uint8_t, 4>& ip) {
            return ip[0] == 1;
        });
        write(ip_pool, [](const std::array<uint8_t, 4>& ip) {
            return ip[0] == 46 &&
                ip[1] == 70;
        });
        write(ip_pool, [](const std::array<uint8_t, 4>& ip) {
            auto result = std::find_if(ip.begin(), ip.end(), [](const auto& ip_part) {
                return ip_part == 46;
            });
            return result != ip.end();
        });


        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
