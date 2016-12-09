/**
 * @file
 * @author  Jeremy McAnally <jeremymcanally@gmail.com>
 * @version 1.0
 *
 * @brief A tiny testing framework to make writing test programs
 *        more sane and make them easier to read.
 * 
 * @section Repo information
 *
 * http://github.com/jm/tinytest
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

/**
 * Class representing a test failure.
 */
class TinyTestFailure {
public:
  string testName;
  string suiteName;
  string message;

  TinyTestFailure(string message);
};

TinyTestFailure::TinyTestFailure(string message):testName(""), message(message) {}

/**
 * Class representing an error encountered during a test run.
 */
class TinyTestError {
public:
  string testName;
  exception err;

  TinyTestError(string name, exception error);
};

TinyTestError::TinyTestError(string name, exception error):testName(name), err(error) {}

/**
 * Class to encapsulate a test run.
 */
class TinyTestRun {
public:
  vector<TinyTestFailure> failures;
  vector<TinyTestError> errors;
  string currentSuite;
  int testCount;
  int assertionCount;

  TinyTestRun();
};

TinyTestRun * runner = new TinyTestRun();

/**
 * Function to report the end result of a run of tests.
 */
void reportResults() {
  cout << endl;
  if (!runner->failures.empty()) {
    cout << "Failures" << endl;
    cout << "----------------" << endl;
    for (int i = 0; i < runner->failures.size(); i++) {
      TinyTestFailure failure = runner->failures[i];
      cout << "- " << failure.suiteName << " -> " << failure.testName;
      
      if (failure.message != "") {
        cout << " -> " << failure.message;
      }

      cout << endl;      
    }
    
    cout << endl;
  }
  cout << "----------------" << endl;
  cout << "Results: " << runner->testCount << " tests, " << runner->assertionCount << " assertions, " << runner->failures.size() << " failures, " << runner->errors.size() << " errors" << endl;
  cout << "----------------" << endl << endl;
}

/**
 * Constructor that sets up atexit hook for autorunning tests.
 */
TinyTestRun::TinyTestRun() {
  atexit(reportResults);
}

/**
 * Start a suite of tests.  Used for grouping.
 */
void Suite(string name, function<void(void)> testSuite) {
  cout << endl << "Starting suite: " << name << endl;
  runner->currentSuite = name;
  testSuite();
  runner->currentSuite = "";
  cout << endl;
}

/**
 * Mark an individual test.
 */
void Test(string name, function<void(void)> testCode) {
  try {
    runner->testCount++;
    testCode();
  } catch (TinyTestFailure& tf) {
    tf.testName = name;
    tf.suiteName = runner->currentSuite;

    runner->failures.push_back(tf);
  } catch (std::exception& e) {
    TinyTestError error = TinyTestError(name, e);
    runner->errors.push_back(error);
  }
}

/** 
 * Make a positive assertion with optional failure message.
 */
void assert(bool expression, string message) {
  if (!expression) {
    cout << "F";
    throw TinyTestFailure(message);
  } else {
    cout << ".";
  }

  runner->assertionCount++;
}

/** 
 * Make a positive assertion with no message.
 */
void assert(bool expression) {
  assert(expression, "");
}

/** 
 * Make a negative assertion with optional failure message.
 */
void assertNot(bool expression, string message) {
  if (expression) {
    cout << "F";
    throw TinyTestFailure(message);
  } else {
    cout << ".";
  }

  runner->assertionCount++;
}

/** 
 * Make a negative assertion with no message.
 */
void assertNot(bool expression) {
  assertNot(expression, "");
}