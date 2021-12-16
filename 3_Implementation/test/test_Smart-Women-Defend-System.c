#include "unity.h"
#include <SDLC-Dec_Team_40.h>

/* Modify these two lines according to the project */
#include <SDLC-Dec_Team_40.h>
#define PROJECT_NAME    "Handy Fitness Guide"

/* Prototypes for all the test functions */
void test_tropical_sedentary(weight);
void test_tropical_moderate(weight);
void tropical_extreme(weight);
void test_temperature_sedentary(weight);
void test_temperature_moderate(weight);
void test_temperature_extreme(weight);
void test_cold_sedentary(weight);
void test_cold_moderate(weight);
void test_cold_extreme(weight);
void test_bmrmale(height,age,weight);
void test_bmrfemale(height,age,weight);
void test_BMI(weight,height);
void test_Ideal_Weight(height,gender);
void test_protein(weight);
void test_fever(temp);


/* Required by the unity test framework */
void setUp(){}
/* Required by the unity test framework */
void tearDown(){}

/* Start of the application test */
int main()
{
/* Initiate the Unity Test Framework */
  UNITY_BEGIN();

/* Run Test functions */
  RUN_TEST
  RUN_TEST(test_tropical_sedentary);
  RUN_TEST(test_tropical_moderate);
  RUN_TEST(test_tropical_extreme);
  RUN_TEST(test_temperature_sedentary);
  RUN_TEST(test_temperature_moderate);
  RUN_TEST(test_temperature_extreme);
  RUN_TEST(test_cold_sedentary);
  RUN_TEST(test_cold_moderate);
  RUN_TEST(test_cold_extreme);
  RUN_TEST(test_bmrmale);
  RUN_TEST(test_bmrfemale);
  RUN_TEST(test_BMI);
  RUN_TEST(test_Ideal_Weight);
  RUN_TEST(test_protein);
  RUN_TEST(test_fever);


  /* Close the Unity Test Framework */
  return UNITY_END();
}

/* Write all the test functions */ 
void test_tropical_sedentary(weight);
{
  TEST_ASSERT_EQUAL(You need to drink at least 6 glasses of water everyday.\nThis is equivalent to 1.5 litres [51.2 ounces] of water., tropical_sedentary(30));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(sorry.weight undetermined, tropical_sedentary(225));
}
void test_tropical_moderate(weight);
{
  TEST_ASSERT_EQUAL(You need to drink at least 8 glasses of water everyday.\nThis is equivalent to 1.9 litres [63.7 ounces] of water., tropical_moderate(40));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(sorry.weight undetermined, tropical_moderate(221));
}
void tropical_extreme(weight);
{
  TEST_ASSERT_EQUAL(You need to drink at least 11 glasses of water everyday.\nThis is equivalent to 2.6 litres [89.1 ounces] of water., tropical_extreme(50));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(sorry.weight undetermined, buz(224));
}
void test_temperature_sedentary(weight);
{
  TEST_ASSERT_EQUAL(You need to drink at least 6 glasses of water everyday.\nThis is equivalent to 1.3 litres [44 ounces] of water., temperature_sedentary(42));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(sorry.weight undetermined, temperature_sedentary(227));
}
void test_temperature_moderate(weight);
{
  TEST_ASSERT_EQUAL(You need to drink at least 11 glasses of water everyday.\nThis is equivalent to 2.6 litres [87.3 ounces] of water., temperature_moderate(61));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(sorry.weight undetermined, temperature_moderate(270));
}
void test_temperature_extreme(weight);
{
  TEST_ASSERT_EQUAL(You need to drink at least 16 glasses of water everyday.\nThis is equivalent to 3.9 litres [130.4 ounces] of water., temperature_extreme(72));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(sorry.weight undetermined, temperature_extreme(260));
}
void test_cold_sedentary(weight);
{
  TEST_ASSERT_EQUAL(You need to drink at least 10 glasses of water everyday.\nThis is equivalent to 2.4 litres [79.5 ounces] of water., cold_sedentary(65));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(sorry.weight undetermined, cold_sedentary(266));
}
void test_cold_moderate(weight);
{
  TEST_ASSERT_EQUAL(You need to drink at least 8 glasses of water everyday.\nThis is equivalent to 1.9 litres [63.9 ounces] of water., cold_moderate(45));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(sorry.weight undetermined, cold_moderate(18));
}
void test_cold_extreme(weight);
{
  TEST_ASSERT_EQUAL(You need to drink at least 15 glasses of water everyday.\nThis is equivalent to 3.6 litres [120.2 ounces] of water., cold_extreme(67));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(sorry.weight undetermined, cold_extreme(25));
}
void test_bmrmale(height,age,weight);
{
  TEST_ASSERT_EQUAL(1605, bmrmale(180,60,25));
}
void test_bmrfemale(height,age,weight);
{
  TEST_ASSERT_EQUAL(1439, bmrfemale(180,60,25));
}
void test_BMI(weight,height);
{
  TEST_ASSERT_EQUAL(20.1, BMI(65,180));
}
void test_Ideal_Weight(height,gender);
{
  TEST_ASSERT_EQUAL(36.3, Ideal_Weight(140,M));
}
void test_protein(weight);
{
  TEST_ASSERT_EQUAL(you need 55 grams of protein per day, protein(54));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(sorry,weight is undetermined, buz(200));
}
void test_fever(temp);
{
  TEST_ASSERT_EQUAL(Its Normal, protein(98.6));
}

