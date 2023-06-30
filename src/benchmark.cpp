#include <benchmark/benchmark.h>

#include "StdRandom.h"

#include <random>

class VirtualFixture : public benchmark::Fixture {
public:
  void SetUp(const benchmark::State &state) override {
    (void)state;
    rng.init(999);
  }

  void Run() {
    double num = rng();
    benchmark::DoNotOptimize(num);
  }

  void TearDown(const benchmark::State &state) override { (void)state; }

private:
  qmcplusplus::StdRandom<double> rng;
};

class RawFixture : public benchmark::Fixture {
public:
  void SetUp(const benchmark::State &state) override {
    (void)state;
    engine.seed(999);
  }

  void Run() {
    double num = distribution(engine);
    benchmark::DoNotOptimize(num);
  }

  void TearDown(const benchmark::State &state) override { (void)state; }

private:
  qmcplusplus::uniform_real_distribution_as_boost<double> distribution;
  std::mt19937 engine;
};

BENCHMARK_F(VirtualFixture, StdRandom)(benchmark::State &state) {
  for (auto _ : state) {
    this->Run();
  }
}

BENCHMARK_F(RawFixture, StdMt19937)(benchmark::State &state) {
  for (auto _ : state) {
    this->Run();
  }
}

// Run the benchmark
BENCHMARK_MAIN();
