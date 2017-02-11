cmake_minimum_required(VERSION 3.6)
project(xClean)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Common.cpp Common.h Solver/Solver.cpp Solver/Solver.h RuleGenerator/RuleGenerator.cpp RuleGenerator/RuleGenerator.h RuleGenerator/SlowLCS.cpp Joiner/Joiner.cpp Joiner/Joiner.h Joiner/BruteForceJoiner.cpp RuleGenerator/FastLCS.cpp RuleGenerator/FastLCS.h RuleGenerator/SlowLCS.h Joiner/BruteForceJoiner.h Joiner/PolynomialJoiner.cpp Joiner/PolynomialJoiner.h Joiner/SigBuilder/DpSigBuilder.cpp RuleGenerator/MyRule.cpp RuleGenerator/MyRule.h Joiner/SigBuilder/DpLargeTokenSigBuilder.cpp Joiner/Verifier/Sigmod13Verifier.cpp Joiner/Verifier/LargeTokenGreedyVerifier.cpp Joiner/SigBuilder/OriginalSigBuilder.cpp Joiner/SigBuilder/OriginalLargeTokenSigBuilder.cpp RuleGenerator/BadBoy.cpp RuleGenerator/BadBoy.h RuleGenerator/WildLCS.cpp RuleGenerator/WildLCS.h RuleGenerator/NLPRule.cpp RuleGenerator/NLPRule.h Joiner/Verifier/GreedyVerifier.cpp)
add_executable(xClean ${SOURCE_FILES})