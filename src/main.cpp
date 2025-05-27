// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include "tree.h"

int main() {
    std::vector<char> in = {'1','2','3'};
    PMTree tree(in);

    std::cout << "AllPerms:\n";
    auto perms = getAllPerms(tree);
    for (auto& p : perms) {
        for (char c : p) std::cout << c;
        std::cout << '\n';
    }

    auto p1 = getPerm1(tree, 1);
    std::cout << "Perm1: ";
    for (char c : p1) std::cout << c;
    std::cout << '\n';

    auto p2 = getPerm2(tree, 2);
    std::cout << "Perm2: ";
    for (char c : p2) std::cout << c;
    std::cout << '\n';

    std::vector<int> ns = {5,6,7,8};
    std::ofstream csv("result/times.csv");
    csv << "n,getAll,getPerm1,getPerm2\n";
    for (int n : ns) {
        std::vector<char> input;
        for (int i = 1; i <= n; ++i) input.push_back('0' + i);
        PMTree t(input);
        long long total = 1;
        for (int i = 2; i <= n; ++i) total *= i;
        std::mt19937_64 rng(1234);
        std::uniform_int_distribution<long long> dist(1, total);
        int idx = dist(rng);

        using clk = std::chrono::high_resolution_clock;
        auto t0 = clk::now();
        auto all_p = getAllPerms(t);
        auto t1 = clk::now();
        auto perm1 = getPerm1(t, idx);
        auto t2 = clk::now();
        auto perm2 = getPerm2(t, idx);
        auto t3 = clk::now();

        double dt_all = std::chrono::duration<double,std::milli>(t1-t0).count();
        double dt1_ = std::chrono::duration<double,std::milli>(t2-t1).count();
        double dt2_ = std::chrono::duration<double,std::milli>(t3-t2).count();

        csv << n << "," << dt_all << "," << dt1_ << "," << dt2_ << "\n";
        std::cout << "n=" << n << " all=" << dt_all << "ms p1=" << dt1_ << "ms p2=" << dt2_ << "ms\n";
    }

    return 0;
}
