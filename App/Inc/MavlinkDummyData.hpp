#pragma once
#include <cstdint>
#include "mavlink/custom/mavlink.h"
#include "mavlink/custom/mavlink_msg_mission_telemetry.h"

constexpr mavlink_mission_telemetry_t dummy_dataset[] = {
    { .mission_time = 0, .altitude = 0.0f, .temperature = 22.0f, .pressure = 1013.0f,
      .gyro_r = 0.5f, .gyro_p = -0.3f, .gyro_y = 0.1f, .accel_r = 0.2f, .accel_p = 9.7f, .accel_y = 0.1f,
      .gps_latitude = 383500000, .gps_longitude = 333500000, 
      .packet_count = 0, .state = ASCENT, .gps_sats = 8 },

    { .mission_time = 1000, .altitude = 120.0f, .temperature = 20.5f, .pressure = 999.0f,
      .gyro_r = 1.2f, .gyro_p = 0.8f, .gyro_y = -0.4f, .accel_r = 0.3f, .accel_p = 9.5f, .accel_y = -0.2f,
      .gps_latitude = 383502000, .gps_longitude = 333501500, 
      .packet_count = 0, .state = ASCENT, .gps_sats = 9 },

    { .mission_time = 2000, .altitude = 310.0f, .temperature = 18.0f, .pressure = 978.0f,
      .gyro_r = 2.1f, .gyro_p = -1.5f, .gyro_y = 0.9f, .accel_r = 0.5f, .accel_p = 9.2f, .accel_y = 0.3f,
      .gps_latitude = 383504500, .gps_longitude = 333503200, 
      .packet_count = 0, .state = ASCENT, .gps_sats = 9 },

    { .mission_time = 3000, .altitude = 450.0f, .temperature = 15.5f, .pressure = 960.0f,
      .gyro_r = 0.1f, .gyro_p = 0.1f, .gyro_y = 0.0f, .accel_r = 0.0f, .accel_p = 9.81f, .accel_y = 0.0f,
      .gps_latitude = 383507000, .gps_longitude = 333505000, 
      .packet_count = 0, .state = APOGEE, .gps_sats = 9 },

    { .mission_time = 4000, .altitude = 380.0f, .temperature = 16.0f, .pressure = 970.0f,
      .gyro_r = -1.8f, .gyro_p = 1.2f, .gyro_y = -0.6f, .accel_r = -0.4f, .accel_p = 8.9f, .accel_y = -0.1f,
      .gps_latitude = 383508500, .gps_longitude = 333506200, 
      .packet_count = 0, .state = DESCENT, .gps_sats = 9 },

    { .mission_time = 5000, .altitude = 150.0f, .temperature = 19.0f, .pressure = 995.0f,
      .gyro_r = -2.5f, .gyro_p = 0.6f, .gyro_y = 0.3f, .accel_r = -0.6f, .accel_p = 9.0f, .accel_y = 0.2f,
      .gps_latitude = 383510000, .gps_longitude = 333507500, 
      .packet_count = 0, .state = DESCENT, .gps_sats = 9 },

    { .mission_time = 6000, .altitude = 50.0f, .temperature = 21.0f, .pressure = 1008.0f,
      .gyro_r = 3.0f, .gyro_p = -2.0f, .gyro_y = 1.5f, .accel_r = 1.2f, .accel_p = -2.5f, .accel_y = 0.4f,
      .gps_latitude = 383511000, .gps_longitude = 333508300, 
      .packet_count = 0, .state = PAYLOAD_RELEASE, .gps_sats = 8 },

    { .mission_time = 7000, .altitude = 0.0f, .temperature = 22.0f, .pressure = 1013.0f,
      .gyro_r = 0.0f, .gyro_p = 0.0f, .gyro_y = 0.0f, .accel_r = 0.0f, .accel_p = 9.81f, .accel_y = 0.0f,
      .gps_latitude = 383511500, .gps_longitude = 333508700, 
      .packet_count = 0, .state = LANDED, .gps_sats = 8 }
};