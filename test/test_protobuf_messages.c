#include <unity.h>
#include <stdio.h>

#include "mecanum.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"

#define BUFFER_SIZE 256

uint8_t buffer[BUFFER_SIZE];
pb_ostream_t ostream;
pb_istream_t istream;

void setUp(void) {
    // ostream -> buffer (256 bytes)
    ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));
}

void tearDown(void) {
    // clear buffer
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = 0;
    }

    // clear ostream and istream
    ostream = pb_ostream_from_buffer(NULL, 0);
    istream = pb_istream_from_buffer(NULL, 0);
}

void test_control_request_message(void) {
    size_t written;

    // ostream -> buffer (256 bytes)
    ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    ControlRequest original = ControlRequest_init_zero;
    original.speed_mmps = 45;
    original.rad = 2.3;
    original.omega = 3.1;

    bool status = pb_encode(&ostream, &ControlRequest_msg, &original);
    TEST_ASSERT_TRUE(status);

    written = ostream.bytes_written;
    istream = pb_istream_from_buffer(buffer, written);
    ControlRequest decoded = ControlRequest_init_zero;

    status = pb_decode(&istream, &ControlRequest_msg, &decoded);

    TEST_ASSERT_EQUAL_INT(original.speed_mmps, decoded.speed_mmps);
    TEST_ASSERT_EQUAL_FLOAT(original.rad, decoded.rad);
    TEST_ASSERT_EQUAL_FLOAT(original.omega, decoded.omega);

    // Test another message with different values
    original.speed_mmps = 452;
    original.rad = 2233.3;
    original.omega = 31.1;

    ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    status = pb_encode(&ostream, &ControlRequest_msg, &original);
    TEST_ASSERT_TRUE(status);

    written = ostream.bytes_written;
    istream = pb_istream_from_buffer(buffer, written);

    status = pb_decode(&istream, &ControlRequest_msg, &decoded);

    TEST_ASSERT_EQUAL_INT(decoded.speed_mmps, original.speed_mmps);
    TEST_ASSERT_EQUAL_FLOAT(decoded.rad, original.rad);
    TEST_ASSERT_EQUAL_FLOAT(decoded.omega, original.omega);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_control_request_message);

    return UNITY_END();
}
