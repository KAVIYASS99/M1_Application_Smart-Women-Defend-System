#include "unity.h"
#include <Smart-Women-Defend-System.h>

/* Modify these two lines according to the project */
#include <Smart-Women-Defend-System.h>
#define PROJECT_NAME    "Smart-Women-Defend-System"

/* Prototypes for all the test functions */
void test_buz(void);
void test_dlyms(void);
void test_GPS(void);
void test_GSM(void);
void test_LCD(void);
void test_LED(void);
void test_sms(void);
void test_uart(void);


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
  RUN_TEST(test_buz);
  RUN_TEST(test_dlyms);
  RUN_TEST(test_GPS);
  RUN_TEST(test_GSM);
  RUN_TEST(test_LCD);
  RUN_TEST(test_LED);
  RUN_TEST(test_sms);
  RUN_TEST(test_uart);

  /* Close the Unity Test Framework */
  return UNITY_END();
}

/* Write all the test functions */ 
void test_buz(void) {
  TEST_ASSERT_EQUAL(Buzzer On, buz(1));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(Buzzer Off, buz(0));
}

void test_dlyms(void) {
  TEST_ASSERT_EQUAL(5, dlyms(500));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(1, dlyms(1000));
}

void test_GPS(void) {
  TEST_ASSERT_EQUAL(Location, GPS(1));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(NA, GPS(0));
}

void test_GSM(void) {
  TEST_ASSERT_EQUAL(Send Message, GSM(1));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(NA, GSM(0));
}

/* Write all the test functions */ 
void test_LCD(void) {
  TEST_ASSERT_EQUAL(Print Message, LCD(1));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(NA, LCD(0));
}

void test_LED(void) {
  TEST_ASSERT_EQUAL(Light on, LED(1));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(Light Off, LED(0));
}

void test_sms(void) {
  TEST_ASSERT_EQUAL(Send sms, sms(1));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(NA, sms(0));
}

void test_uart(void) {
  TEST_ASSERT_EQUAL(Transmit sms, uart(1));
  
  /* Dummy fail*/
  TEST_ASSERT_EQUAL(NA, uart(0));
}
