//
// Created by toby on 2/1/23.
//

#ifndef MEOWTEST_TESTER_H
#define MEOWTEST_TESTER_H

#include <functional>
#include <map>


#include "test_unit.h"
#include "tools.h"

inline TestUnitGroup currentGroup;
inline std::map<std::string, TestUnitGroup> allGroups;

struct AddTestUnitAutoRun {
    // This function is called when add test unit.
    rewritable AddTestUnitAutoRun(UnitFunc call, const std::string &filepath, std::string name,
                                  std::string describe = std::string(), UnitType type = UnitType::continueWhenErr);
};


#define AddTestUnit(UNIT_NAME, ...) \
void TestUnit##UNIT_NAME(UnitTestFuncParams);              \
static AddTestUnitAutoRun add##UNIT_NAME##UnitAutoRun(&TestUnit##UNIT_NAME,__FILE__,#UNIT_NAME,##__VA_ARGS__); \
void TestUnit##UNIT_NAME(UnitTestFuncParams)

struct SetGroupAutoRun {
    // This function is called when add Group.
    explicit SetGroupAutoRun(std::string name, std::string describe = "");
};

struct PushCurrentGroupAutoRun {
    explicit PushCurrentGroupAutoRun();
};


#define Group(name, ...) \
namespace name{                         \
static SetGroupAutoRun Set##name##GroupAutoRun{#name,##__VA_ARGS__}; \

#define GroupEnd() static PushCurrentGroupAutoRun pushGroupAutoRun;};

struct GroupTestContext {
public:
    size_t idx = 0;
    size_t count = 0;
    size_t successCount = 0;
};

// Rewritable
void test_group(const TestUnitGroup &group);

// Rewritable
bool test_unit(const TestUnit &unit, GroupTestContext state);

// Rewritable, If you need to customize the test main function entry, just redefine it.
int main();

#endif //MEOWTEST_TESTER_H
