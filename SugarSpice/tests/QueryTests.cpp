#include <fstream>

#include <gtest/gtest.h>

#include "Fixtures.h"

#include "query.h"
#include "utils.h"

using namespace std;

TEST_F(KernelDataDirectories, FunctionalTestSearchMissionKernelsAllMess) {
  fs::path dbPath = getMissionConfigFile("mess");

  ifstream i(dbPath);
  nlohmann::json conf;
  i >> conf;

  MockRepository mocks;
  mocks.OnCallFunc(ls).Return(paths);

  nlohmann::json res = searchMissionKernels("/isis_data/", conf);

  ASSERT_EQ(res["mdis"]["ck"]["reconstructed"].size(), 4);
  ASSERT_EQ(res["mdis"]["ck"]["smithed"].size(), 4);
  ASSERT_EQ(res["mdis"]["ck"]["deps"]["sclk"].size(), 2);
  ASSERT_EQ(res["mdis"]["ck"]["deps"]["lsk"].size(), 2);
  ASSERT_EQ(res["mdis"]["ck"]["deps"]["objs"].size(), 2);
  ASSERT_EQ(res["mdis"]["spk"]["reconstructed"].size(), 2);
  ASSERT_EQ(res["mdis"]["spk"]["deps"]["lsk"].size(), 2);
  ASSERT_EQ(res["mdis"]["tspk"]["na"].size(), 1);
  ASSERT_EQ(res["mdis"]["fk"].size(), 2);
  ASSERT_EQ(res["mdis"]["ik"].size(), 2);
  ASSERT_EQ(res["mdis"]["iak"].size(), 2);
  ASSERT_EQ(res["mdis"]["pck"].size(), 2);

  ASSERT_EQ(res["mdis_att"]["ck"]["reconstructed"].size(), 4);
  ASSERT_EQ(res["mdis_att"]["ck"]["deps"]["sclk"].size(), 2);
  ASSERT_EQ(res["mdis_att"]["ck"]["deps"]["lsk"].size(), 2);
  ASSERT_EQ(res["mdis_att"]["ck"]["deps"]["objs"].size(), 0);

  ASSERT_EQ(res["mess"]["ck"]["reconstructed"].size(), 5);
  ASSERT_EQ(res["mess"]["ck"]["deps"]["sclk"].size(), 2);
  ASSERT_EQ(res["mess"]["ck"]["deps"]["lsk"].size(), 2);
  ASSERT_EQ(res["mess"]["ck"]["deps"]["objs"].size(), 0);
}


TEST_F(KernelDataDirectories, FunctionalTestSearchMissionKernelsClem1) {
  fs::path dbPath = getMissionConfigFile("clem1");

  ifstream i(dbPath);
  nlohmann::json conf;
  i >> conf;

  MockRepository mocks;
  mocks.OnCallFunc(ls).Return(paths);

  nlohmann::json res = searchMissionKernels("/isis_data/", conf);

  ASSERT_EQ(res["clem"]["ck"]["reconstructed"].size(), 4);
  ASSERT_EQ(res["clem"]["ck"]["smithed"].size(), 1);
  ASSERT_EQ(res["clem"]["ck"]["deps"]["sclk"].size(), 2);
  ASSERT_EQ(res["clem"]["ck"]["deps"]["lsk"].size(), 2);
  ASSERT_EQ(res["clem"]["ck"]["deps"]["objs"].size(), 0);
  ASSERT_EQ(res["clem"]["spk"]["reconstructed"].size(), 2);
  ASSERT_EQ(res["clem"]["spk"]["deps"]["lsk"].size(), 2);
  ASSERT_EQ(res["clem"]["fk"].size(), 1);

  ASSERT_EQ(res["UVVIS"]["ik"].size(), 1);
  ASSERT_EQ(res["UVVIS"]["iak"].size(), 2);

  ASSERT_EQ(res["UVVIS"]["iak"].size(), 2);
}
