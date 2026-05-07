#include "registration_service.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Return;
using ::testing::StrEq;

class MockEmailService : public EmailService {
 public:
  MOCK_METHOD(bool, sendEmail, (const std::string& to, const std::string& subject, const std::string& body), (override));
};

TEST(UserRegistrationTest, SendsWelcomeEmail) {
  MockEmailService mock;
  RegistrationService reg(&mock);

  EXPECT_CALL(mock, sendEmail(StrEq("adam@example.com"), StrEq("Welcome"), StrEq("Hello Adam"))).WillOnce(Return(true));

  EXPECT_TRUE(reg.registerUser("Adam", "adam@test.com"));
}

TEST(UserRegistrationTest, ReturnsFalseWhenEmailFails) {
  MockEmailService mock;
  RegistrationService reg(&mock);

  EXPECT_CALL(mock, sendEmail(StrEq("eve@test.com"), StrEq("Welcome"), StrEq("Hello Eve"))).WillOnce(Return(false));

  EXPECT_FALSE(reg.registerUser("Eve", "eve@test.com"));
}

TEST(UserRegistrationTest, SendEmailToDifferentUser) {
  MockEmailService mock;
  RegistrationService reg(&mock);

  EXPECT_CALL(mock, sendEmail(StrEq("john@test.com"), StrEq("Welcome"), StrEq("Hello John"))).WillOnce(Return(true));

  EXPECT_TRUE(reg.registerUser("John", "john@test.com"));
}